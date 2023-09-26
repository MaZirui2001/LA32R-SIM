#include <debug.h>
#include "syscall.h"
#include <sys/time.h>
#include <mem.h>
#include <fs.h>
#include <proc.h>

void syscall_handle(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  switch (a[0]) {
    case SYS_exit: {
      printf("exit success!\n"); 
      execve("/bin/menu\0", NULL, NULL);
      halt(c->GPRx); 
      break;
    }
    case SYS_yield: {
      yield(); 
      break;
    }
    case SYS_write: {
      c->GPRx = fs_write(a[1], (void *)a[2], a[3]); 
      break;
    }
    case SYS_open: {
      c->GPRx = fs_open((char *)a[1], a[2], a[3]); 
      break;
    }
    case SYS_read: {
      c->GPRx = fs_read(a[1], (void *)a[2], a[3]); 
      break;
    }
    case SYS_lseek: {
      c->GPRx = fs_lseek(a[1], a[2], a[3]); 
      break;
    }
    case SYS_close: {
      c->GPRx = fs_close(a[1]); 
      break;
    }
    case SYS_gettimeofday: {
      size_t time = io_read(DEV_TIMER_UPTIME).us;
      ((struct timeval *)a[1])->tv_sec = time / 1000000;
      ((struct timeval *)a[1])->tv_usec = time % 1000000;
      c->GPRx = 0;
      break;
    }
    case SYS_execve: {
      c->GPRx = execve((const char *) a[1], (char **) a[2], (char **) a[3]);
      break;
    }
    case SYS_brk: {
      c->GPRx = mm_brk(a[1]); 
      break;
    }
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}
