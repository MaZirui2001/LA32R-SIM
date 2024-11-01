#ifndef __COMMON_H__
#define __COMMON_H__

#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <arch.h>
#include <config.h>
#include <utils.h>


#define MAP(c, f) c(f)
#define concat(a, b) a ## b

#define BITS(a, m, n) (((a) >> (n)) & ((1 << ((m) - (n) + 1)) - 1))

#define SBITS(a, m, n) \
    ((((a) >> (n)) & ((1 << ((m) - (n) + 1)) - 1)) | \
    (((a) >> (m)) & 1 ? ((unsigned)(~0) << (m - n + 1)) : 0))

enum {SIM_RUNNING, SIM_STOP, SIM_END, SIM_ABORT};

typedef uint32_t paddr_t;
typedef uint32_t word_t;
typedef std::unordered_map<uint32_t, uint32_t> pmem_t;



#endif