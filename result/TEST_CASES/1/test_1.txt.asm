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
	L2 WORD 12
	L3 WORD 1539
	L4 WORD 921
	L5 WORD 1
	L6 BYTE 'Output of values c and a:', 0
	L7 BYTE 'max of a and b are: ', 0
	L8 BYTE 'd', 0
	L9 BYTE 'Hello world', 0
	L10 BYTE 'Output of string str1 and str2:', 0
	L11 BYTE 'lexicographic string comparison str3 and str4:', 0
	L12 BYTE 'hello', 0
	L13 BYTE 'hello ', 0
	L14 WORD 1
	L15 BYTE 'are equels', 0
	L16 BYTE 'are not the same', 0
	L17 WORD 0

.data
	maxres WORD 0
	maina WORD 0
	mainb WORD 0
	mainc WORD 0
	maind WORD 0
	mainres WORD 0
	mainstr1 DWORD 0
	mainstr2 DWORD 0
	mainstr3 DWORD 0
	mainstr4 DWORD 0
	maininfo WORD 0

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


main PROC
	push L2
	pop mainc
	push L3
	pop eax
	push L4
	pop ebx
	add eax, ebx
	push eax
	pop maina
	movzx ecx, mainc
p2:
	push mainc
	pop ebx
	push L5
	pop eax
	sub ebx, eax
	push ebx
	pop mainc
loop p2
	push offset L6
	call _printS
	push mainc
	call _printN
	push maina
	call _printN
	mov ax, maina
	cmp ax, mainb
	jl p3
	jg p3
	je p4
p3:
	push offset L7
	call _printS
	movzx eax, mainb
	push eax
	movzx eax, maina
	push eax
	call max
	push eax
	pop maind
	push maind
	call _printN
p4:
	push offset L8
	pop mainstr1
	push offset L9
	pop mainstr2
	push offset L10
	call _printS
	push mainstr1
	call _printS
	push mainstr2
	call _printS
	push offset L11
	call _printS
	push offset L12
	pop mainstr3
	push offset L13
	pop mainstr4
	push mainstr4
	push mainstr3
	call _compare
	push eax
	pop mainres
	push L14
	pop maininfo
	mov ax, mainres
	cmp ax, L5
	je p5
	jg p6
	jl p6
p5:
	push offset L15
	call _printS
	jmp ife1
p6:
	push offset L16
	call _printS
ife1:
	push 0
	call _pause
	call ExitProcess
main ENDP
end main