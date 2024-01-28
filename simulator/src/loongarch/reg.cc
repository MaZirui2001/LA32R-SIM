#include <common.h>
const char* reg_name[32] = {
    "$r0", "$r1", "$r2", "$r3", "$r4", "$r5", "$r6", "$r7",
    "$r8", "$r9", "$r10", "$r11", "$r12", "$r13", "$r14", "$r15",
    "$r16", "$r17", "$r18", "$r19", "$r20", "$r21", "$r22", "$r23",
    "$r24", "$r25", "$r26", "$r27", "$r28", "$r29", "$r30", "$r31" 
};
std::unordered_map<unsigned int, const char*> csr_name = {
    {0x0, "crmd"},      {0x1, "prmd"},      {0x2, "euen"},          {0x4, "ecfg"}, 
    {0x5, "estat"},     {0x6, "era"},       {0x7, "badv"},          {0xc, "eentry"},
    {0x10, "tlbidx"},   {0x11, "tlbehi"},   {0x12, "tlblo0"},       {0x13, "tlblo1"},
    {0x18, "asid"},     {0x19, "pgdl"},     {0x1a, "pgdh"},         {0x1b, "pgd"},
    {0x20, "cpuid"},    {0x30, "save0"},    {0x31, "save1"},        {0x32, "save2"},
    {0x33, "save3"},    {0x40, "tid"},      {0x41, "tcfg"},         {0x42, "tval"}, 
    {0x44, "ticlr"},    {0x60, "llbctl"},   {0x88, "tlbrentry"},    {0x98, "ctag"},
    {0x180, "dmw0"},    {0x181, "dmw1"}
};
std::unordered_map<unsigned int, unsigned int> csr_map = {
    {CSR_NAME::CRMD, CSR_IDX::CRMD}, {CSR_NAME::PRMD, CSR_IDX::PRMD}, {CSR_NAME::EUEN, CSR_IDX::EUEN}, {CSR_NAME::ECFG, CSR_IDX::ECFG},
    {CSR_NAME::ESTAT, CSR_IDX::ESTAT}, {CSR_NAME::ERA, CSR_IDX::ERA}, {CSR_NAME::BADV, CSR_IDX::BADV}, {CSR_NAME::EENTRY, CSR_IDX::EENTRY},
    {CSR_NAME::TLBIDX, CSR_IDX::TLBIDX}, {CSR_NAME::TLBEHI, CSR_IDX::TLBEHI}, {CSR_NAME::TLBLO0, CSR_IDX::TLBLO0}, {CSR_NAME::TLBLO1, CSR_IDX::TLBLO1},
    {CSR_NAME::ASID, CSR_IDX::ASID}, {CSR_NAME::PGDL, CSR_IDX::PGDL}, {CSR_NAME::PGDH, CSR_IDX::PGDH}, {CSR_NAME::PGD, CSR_IDX::PGD},
    {CSR_NAME::CPUID, CSR_IDX::CPUID}, {CSR_NAME::SAVE0, CSR_IDX::SAVE0}, {CSR_NAME::SAVE1, CSR_IDX::SAVE1}, {CSR_NAME::SAVE2, CSR_IDX::SAVE2},
    {CSR_NAME::SAVE3, CSR_IDX::SAVE3}, {CSR_NAME::TID, CSR_IDX::TID}, {CSR_NAME::TCFG, CSR_IDX::TCFG}, {CSR_NAME::TVAL, CSR_IDX::TVAL},
    {CSR_NAME::TICLR, CSR_IDX::TICLR}, {CSR_NAME::LLBCTL, CSR_IDX::LLBCTL}, {CSR_NAME::TLBRENTRY, CSR_IDX::TLBRENTRY}, {CSR_NAME::CTAG, CSR_IDX::CTAG},
    {CSR_NAME::DMW0, CSR_IDX::DMW0}, {CSR_NAME::DMW1, CSR_IDX::DMW1}
};

std::unordered_map<uint32_t, uint32_t> csr_mask {
    {0x0, 0x1ff},       {0x1, 0x7},         {0x2, 0x1},             {0x4, 0x1bff},
    {0x5, 0x3},         {0x6, 0xffffffff},  {0x7, 0xffffffff},      {0xc, 0xffffffc0},
    {0x10, 0xbf00001f}, {0x11, 0xffffe000}, {0x12, 0xfffff7f},      {0x13, 0xfffff7f},
    {0x18, 0x3ff},      {0x19, 0xfffff000}, {0x1a, 0xfffff000},     {0x1b, 0x0},
    {0x20, 0x0},        {0x30, 0xffffffff}, {0x31, 0xffffffff},     {0x32, 0xffffffff}, 
    {0x33, 0xffffffff}, {0x40, 0xffffffff}, {0x41, 0x3fffffff},     {0x42, 0x0},
    {0x44, 0x0},        {0x60, 0x4},        {0x88, 0xffffffc0},     {0x98, 0xffffffff},
    {0x180, 0xee000039}, {0x181, 0xee000039}
};