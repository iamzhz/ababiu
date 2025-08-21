#ifndef _CONFIG_H_
#define _CONFIG_H_

/*
0."rax"  1."r10"  2."r9"  3."r8"
4."rcx"  5."rdx"  6."rsi"  7."rdi"

9."r11" 

"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", 
"xmm5", "xmm6", "xmm7", "xmm8", "xmm9", 
"xmm10", "xmm11", "xmm12", "xmm13", "xmm14"
pass function:
    linux: rdi, rsi, rdx, rcx, r8, and r9
    windows: rcx, rdx, r8, and r9
*/
// 9(common)-16(float)
#define COMMON_REGS_NUMBER 8
#define XMM_NUMBER 16
#define RAX_NUMBER 0
#define R10_NUMBER 1
#define R9_NUMBER 2
#define R8_NUMBER 3
#define RCX_NUMBER 4
#define RDX_NUMBER 5
#define RSI_NUMBER 6
#define RDI_NUMBER 7

#define R11_NUMBER 8
#define EXCHANGE_REG_NUMBER R11_NUMBER // only for exchange, not use

#define INT_SIZE 8
#define CHAR_SIZE 1

#endif