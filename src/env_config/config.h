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

#define XMM0_NUMBER 9
#define XMM1_NUMBER 10
#define XMM2_NUMBER 11
#define XMM3_NUMBER 12
#define XMM4_NUMBER 13
#define XMM5_NUMBER 14
#define XMM6_NUMBER 15
#define XMM7_NUMBER 16
#define XMM8_NUMBER 17
#define XMM9_NUMBER 18
#define XMM10_NUMBER 19
#define XMM11_NUMBER 20
#define XMM12_NUMBER 21
#define XMM13_NUMBER 22
#define XMM14_NUMBER 23
#define XMM15_NUMBER 24

#define INT_SIZE 8
#define CHAR_SIZE 1
#define FLOAT_SIZE 8

#endif