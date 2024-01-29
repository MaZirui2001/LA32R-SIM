#ifndef __PRIV_H__
#define __PRIV_H__
#include <stdint.h>
uint32_t do_exception(uint32_t ecode, uint32_t vaddr);
uint32_t do_ertn();
#endif