.586
.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib D:/LABS2/BPA-2023/BPA-lib/Debug/BPA-lib.lib

	EXTERN _printS :PROC
	EXTERN _printN :PROC
	EXTERN _pow :PROC
	EXTERN _compare :PROC
	EXTERN _pause :PROC
	ExitProcess PROTO :DWORD

.stack 4096

.const
	L1 BYTE 'D:/LABS2/BPA-2023/BPA-lib/Debug/BPA-lib.lib', 0
	L2 WORD 1
	maina WORD 10
	L3 WORD 10
	L4 WORD 12
	L5 BYTE 'Max are: ', 0
	L6 BYTE 'Min are: ', 0
	L7 WORD 0

.data
	maxres WORD 0
	minresult WORD 0
	maincos WORD 0
	mainb WORD 0
	mainlclmax WORD 0
	mainlclmin WORD 0

.code
max PROC maxa : WORD, maxb : WORD
	mov ax, maxb
	cmp ax, maxa
	jg p0
	jl p1
	je p1
p0:
	push maxb
	pop maxres
	jmp ife0
p1:
	push maxa
	pop maxres
ife0:
	push maxres
	pop eax
	ret
max ENDP

min PROC mina : WORD, minb : WORD
	movzx eax, minb
	push eax
	movzx eax, mina
	push eax
	call max
	push eax
	pop minresult
	mov ax, minresult
	cmp ax, mina
	je p2
	jg p3
	jl p3
p2:
	push minb
	pop minresult
	jmp ife1
p3:
	push mina
	pop minresult
ife1:
	push minresult
	pop eax
	ret
min ENDP


main PROC
	push L2
	pop maincos
	movzx ecx, maincos
p4:
	push maincos
	pop ebx
	push L2
	pop eax
	sub ebx, eax
	push ebx
	pop maincos
loop p4
	push L4
	pop mainb
	movzx eax, mainb
	push eax
	movzx eax, maina
	push eax
	call max
	push eax
	pop mainlclmax
	movzx eax, mainb
	push eax
	movzx eax, maina
	push eax
	call min
	push eax
	pop mainlclmin
	push offset L5
	call _printS
	push mainlclmax
	call _printN
	push offset L6
	call _printS
	push mainlclmin
	call _printN
	push 0
	call _pause
	call ExitProcess
main ENDP
end main