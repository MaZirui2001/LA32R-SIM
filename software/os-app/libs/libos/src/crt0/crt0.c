#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[], char *envp[]);
extern char **environ;
void call_main(uintptr_t *args) {
  int argc = args[0];
  char **argv = (char**)args + 1;
  char **envp = (char**)argv + argc + 1;
  environ = envp;
  exit(main(argc, argv, envp));
  assert(0);
}
