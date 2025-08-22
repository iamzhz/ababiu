section .text
global pow
; rdi ** rsi
pow:
push rbp
mov rbp, rsp
mov rax, 1
L0:
cmp rsi, 0
jz L1
imul rax, rdi
sub rsi, 1
jmp L0
L1:
leave
ret
