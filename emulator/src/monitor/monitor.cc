#include <common.h>
#include <cpu.h>
#include <difftest.h>
#include <statistic.h>


extern pmem_t pmem;

static const uint32_t img [] = {
  0x1c00000c,  // pcaddu12i $t0,0
  0x29804180,  // st.w $zero,$t0,16
  0x28804184,  // ld.w $a0,$t0,16
  0x80000000,  // break 0 (used as nemu_trap)
  0xdeadbeef,  // some data
};

static uint64_t load_img(char* img_file){
    if(img_file == NULL){
        // memcpy(pmem, img, sizeof(img));
        for(int i = 0; i < sizeof(img) / sizeof(uint32_t); i++){
            pmem[i+0x7000000] = img[i];
            //std::cout << std::hex << pmem[i+0x7000000] << std::endl;
        }
        Log("No image file specified, using built-in image");
        return 0;
    }
    FILE* fp = fopen(img_file, "rb");
    if(!fp){
        printf("Can't open %s\n", img_file);
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    uint64_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if(size > CONFIG_PMEM_SIZE){
        printf("Image too large\n");
        exit(1);
    }
    // int ret = fread(pmem, size, 1, fp);
    // assert(ret == 1);
    for(int i = 0; i < size / sizeof(uint32_t); i++){
        uint32_t data;
        int ret = fread(&data, sizeof(uint32_t), 1, fp);
        pmem[i+0x7000000] = data;
    }
    fclose(fp);
    return size;
}

extern void init_device();
void init_monitor(int argc, char *argv[]) {
    uint64_t size = load_img(argc >= 3 ? argv[1] : NULL);
    init_statistic(argc >= 3 ? argv[1] : "default");
#ifdef DIFFTEST
    // uint64_t size = load_img(argc >= 3 ? argv[1] : NULL);
    init_difftest(argc >= 3 ? argv[2] : argv[1], (long)size);
    difftest_ref_init();
#endif
#ifdef DEVICE
    init_device();
#endif
    
}