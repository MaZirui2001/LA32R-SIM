#include <debug.h>
#include <proc.h>
#include <fs.h>

#define MAX_NR_PROC 4

char *hello1 = "hello, mazirui";

PCB *current = NULL;
static PCB pcb[MAX_NR_PROC] __attribute__((used)) = {};
static PCB pcb_boot = {};


void switch_boot_pcb() {
  current = &pcb_boot;
}

void idle_process(void *arg) {
  while (1) {
    printf("idle process\n");
    yield();
  }
}

void hello_kernel_fun(void *arg) {
  int j = 1;
  while (1) {
    // Log("Hello World from Nanos-lite with arg '%s' for the %dth time!", (uintptr_t)arg, j);
    printf("Hello World from Operating System with arg '%s' for the %dth time!\n", (uintptr_t)arg, j);
    j++;
    yield();
    uint64_t num = 300000;
    while(num--);
  }
}

void init_proc() {
  Log("Initializing processes...");
  char *argv[] = {NULL};
  kernel_ctx_load(&pcb_boot, idle_process, NULL);
  kernel_ctx_load(&pcb[0], hello_kernel_fun, (void*)hello1);
  user_ctx_load(&pcb[1], "/bin/file-test\0", argv, NULL);
  switch_boot_pcb();

  //load program here
  // user_naive_load("/bin/menu");
}

Context* schedule(Context *prev) {
    current->cp = prev;
    current = (current == &pcb[0]) ? &pcb[1] : &pcb[0];
    return current->cp;
}

int execve(const char *filename, char *const argv[], char *const envp[]) {
    // check if the file exists
    int fd = fs_open(filename, 0, 0);
    if(fd == -1) {
        return -2;
    }
    fs_close(fd);
    // load the file
    user_ctx_load(current, filename, argv, envp);
    current = &pcb_boot;
    yield();
    return 0;
}