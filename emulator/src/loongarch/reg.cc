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
    {0x0, 0x0}, {0x1, 0x1}, {0x2, 0x2}, {0x4, 0x3},
    {0x5, 0x4}, {0x6, 0x5}, {0x7, 0x6}, {0xc, 0x7},
    {0x10, 0x8}, {0x11, 0x9}, {0x12, 0xa}, {0x13, 0xb},
    {0x18, 0xc}, {0x19, 0xd}, {0x1a, 0xe}, {0x1b, 0xf},
    {0x20, 0x10}, {0x30, 0x11}, {0x31, 0x12}, {0x32, 0x13},
    {0x33, 0x14}, {0x40, 0x15}, {0x41, 0x16}, {0x42, 0x17},
    {0x44, 0x18}, {0x60, 0x19}, {0x88, 0x1a}, {0x98, 0x1b},
    {0x180, 0x1c}, {0x181, 0x1d}
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


const char* preg_name[128] = {
    "p0",  "p1",  "p2",  "p3",  "p4",  "p5",  "p6",  "p7",
    "p8",  "p9",  "p10", "p11", "p12", "p13", "p14", "p15",
    "p16", "p17", "p18", "p19", "p20", "p21", "p22", "p23",
    "p24", "p25", "p26", "p27", "p28", "p29", "p30", "p31",
    "p32", "p33", "p34", "p35", "p36", "p37", "p38", "p39",
    "p40", "p41", "p42", "p43", "p44", "p45", "p46", "p47",
    "p48", "p49", "p50", "p51", "p52", "p53", "p54", "p55",
    "p56", "p57", "p58", "p59", "p60", "p61", "p62", "p63",
    "p64", "p65", "p66", "p67", "p68", "p69", "p70", "p71",
    "p72", "p73", "p74", "p75", "p76", "p77", "p78", "p79",
    "p80", "p81", "p82", "p83", "p84", "p85", "p86", "p87",
    "p88", "p89", "p90", "p91", "p92", "p93", "p94", "p95",
    "p96", "p97", "p98", "p99", "p100", "p101", "p102", "p103",
    "p104", "p105", "p106", "p107", "p108", "p109", "p110", "p111",
    "p112", "p113", "p114", "p115", "p116", "p117", "p118", "p119",
    "p120", "p121", "p122", "p123", "p124", "p125", "p126", "p127"
};
