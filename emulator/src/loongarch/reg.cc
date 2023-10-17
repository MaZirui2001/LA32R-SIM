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

const char* preg_name[64] = {
    "p0",  "p1",  "p2",  "p3",  "p4",  "p5",  "p6",  "p7",
    "p8",  "p9",  "p10", "p11", "p12", "p13", "p14", "p15",
    "p16", "p17", "p18", "p19", "p20", "p21", "p22", "p23",
    "p24", "p25", "p26", "p27", "p28", "p29", "p30", "p31",
    "p32", "p33", "p34", "p35", "p36", "p37", "p38", "p39",
    "p40", "p41", "p42", "p43", "p44", "p45", "p46", "p47",
    "p48", "p49", "p50", "p51", "p52", "p53", "p54", "p55",
    "p56", "p57", "p58", "p59", "p60", "p61", "p62", "p63"
};
