section .text
global pow
pow:
push rbp
mov rbp, rsp
push rdx
push rcx
mov rdx, rdi
mov rcx, rsi
mov rax, 1
L0:
cmp rcx, 0
jz L1
imul rax, rdx
sub rcx, 1
jmp L0
L1:
pop rcx
pop rdx
leave
ret
