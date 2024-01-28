#ifndef __DIFFTEST_H__
#define __DIFFTEST_H__

void init_difftest(char *ref_so_file, long img_size);
void difftest_sync(uint64_t n);
void difftest_step(uint64_t n);
void difftest_intr(int irq);
void difftest_ref_init();

#endif