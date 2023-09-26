#ifndef __COMMON_H__
#define __COMMON_H__

#include <bits/stdc++.h>
#include <arch.h>
#include <config.h>
#include <utils.h>

#define BITS(a, m, n) (((a) >> (n)) & ((1 << ((m) - (n) + 1)) - 1))

#define SBITS(a, m, n) \
    ((((a) >> (n)) & ((1 << ((m) - (n) + 1)) - 1)) | \
    (((a) >> (m)) & 1 ? (~0 << (m - n + 1)) : 0))

enum {SIM_RUNNING, SIM_STOP, SIM_END, SIM_ABORT};
#endif