#include <dlfcn.h>
#include <common.h>
#include <paddr.h>
#include <cpu.h>

enum { DIFFTEST_TO_DUT, DIFFTEST_TO_REF };
// // the size of registers that should be checked in difftest, 32 gpr, 1 pc, 4 csr
#define REG_SIZE (sizeof(uint64_t) * (32 + 1))

// init fuction pointer with NULL, they will be assign when init
void (*difftest_regcpy)(void *dut, bool direction) = NULL;
void (*difftest_memcpy)(paddr_t addr, void *buf, size_t n, bool direction) = NULL;
void (*difftest_exec)(uint64_t n) = NULL;
// void (*difftest_raise_intr)(uint64_t NO) = NULL;

// // should skip difftest 
// static bool is_skip_ref = false;
// // the num of instruction that should be skipped
// static int skip_dut_nr_inst = 0;

extern uint8_t pmem[];
static uint8_t ref_pmem[CONFIG_PMEM_SIZE];


void init_difftest(char *ref_so_file, long img_size) {
  // ref_so_file is the nemu lib
    assert(ref_so_file != NULL);
    // std::cout << "ref_so_file: " << ref_so_file << std::endl;
    void *handle;
    Log("open dl: %s", ref_so_file);
  // open nemu lib, and link the difftest functions, they are implemented in nemu dir
    handle = dlopen(ref_so_file, RTLD_LAZY);
    assert(handle);

    difftest_memcpy = (void (*)(paddr_t, void *, size_t, bool))dlsym(handle, "difftest_memcpy");
    assert(difftest_memcpy);

    difftest_regcpy = (void (*)(void *, bool))dlsym(handle, "difftest_regcpy");
    assert(difftest_regcpy);

    difftest_exec = (void (*)(uint64_t))dlsym(handle, "difftest_exec");
    assert(difftest_exec);

    Log("Differential testing: %s", ANSI_FMT("ON", ANSI_FG_GREEN));

    // copy the memory, the registers, the pc to nemu, so our cpu and nemu can run with the same initial state
    difftest_memcpy(CONFIG_PMEM_BASE, addr_convert(CONFIG_PMEM_BASE), CONFIG_PMEM_SIZE, DIFFTEST_TO_REF);
    cpu.pc = CONFIG_PMEM_BASE;
    difftest_regcpy(&cpu, DIFFTEST_TO_REF);
}

// copy our registers to nemu
void difftest_sync(){
    difftest_regcpy(&cpu, DIFFTEST_TO_REF);
}

// check the registers with nemu
bool difftest_checkregs(CPU_State *ref_r) {
    // check pc
    if (cpu.pc != ref_r->pc) {
        printf(ANSI_BG_RED "NPC pc = " FMT_WORD ", is different from NEMU pc = " FMT_WORD ANSI_NONE "\n", cpu.pc, ref_r->pc) ; 
        return false;
    }
  // check gpr
    for (int i = 0; i < 32; i++){
        if (cpu.reg[i] != ref_r->reg[i]) {
            printf(ANSI_BG_RED "NPC is different before executing instruction at pc = " FMT_WORD ANSI_NONE
            "\n gpr [%d] right = " FMT_WORD ", wrong = " FMT_WORD "\n",
            cpu.pc, i, ref_r->reg[i], cpu.reg[i]); 
            return false;
        }
    }



//   const char *csr_names[] = {"mepc", "mstatus", "mcause", "mtvec"};
//   // check csr
//   for (int i = 0; i < 4; i++){
//     if (((word_t *)&sim_cpu.csr)[i] != ((word_t *)&ref_r->csr)[i]) {
//       printf(ANSI_BG_RED "NPC is different before executing instruction at pc = " FMT_WORD
//         "\n csr.%s right = " FMT_WORD ", wrong = " FMT_WORD ", diff = " FMT_WORD ANSI_NONE "\n",
//         sim_cpu.pc, csr_names[i], ((word_t *)&ref_r->csr)[i], ((word_t *)&sim_cpu.csr)[i], ((word_t *)&ref_r->csr)[i] ^ ((word_t *)&sim_cpu.csr)[i]); 
//       return false;
//     }
//   }
  return true;
}

// check mem
bool difftest_checkmem(uint8_t *ref_m) {
    for (int i = 0; i < CONFIG_PMEM_SIZE; i++){
        if (ref_m[i] != pmem[i]) {
            printf(ANSI_BG_RED "memory of NPC is different before executing instruction at pc = " FMT_WORD
                ", mem[%x] right = " FMT_WORD ", wrong = " FMT_WORD "\n",
                cpu.pc, i, ref_m[i], pmem[i]); 
            return false;
        }
    }
    return true;
}

static void checkregs(CPU_State *ref, paddr_t pc) {
  if (!difftest_checkregs(ref)) {
    cpu.state = SIM_ABORT;
    cpu.halt_pc = pc;
    // isa_reg_display();
  }
}

static void checkmem(uint8_t *ref_m, paddr_t pc) {
    if (!difftest_checkmem(ref_m)) {
        cpu.state = SIM_ABORT;
        cpu.halt_pc = pc;
    }
}

void difftest_step(uint64_t n) {
    CPU_State ref_r;
    difftest_exec(n);
    difftest_regcpy(&ref_r, DIFFTEST_TO_DUT);
  // difftest_memcpy(CONFIG_MBASE, ref_pmem, CONFIG_MSIZE, DIFFTEST_TO_DUT);
    checkregs(&ref_r, cpu.pc);
  // checkmem(ref_pmem, sim_cpu.pc);
}