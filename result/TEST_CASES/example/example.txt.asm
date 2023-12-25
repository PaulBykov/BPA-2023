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
	L2 SWORD 10
	maincos SWORD 12
	L3 SWORD 5
	L4 SWORD 3
	L5 SWORD 1000
	L6 SWORD 100
	L7 SWORD 2
	L8 SWORD 2
	L9 SWORD 1
	L10 BYTE 'Count to 10', 0
	L11 SWORD 10
	L12 SWORD 1
	L13 BYTE 'b is greater with value: ', 0
	L14 BYTE 'a is greater with value: ', 0
	L15 BYTE 'max of a and b are: ', 0
	mainlettera BYTE 'a', 0
	L16 BYTE 'a', 0
	L17 BYTE 'lexicographic string comparison str3 and str4:', 0
	L18 BYTE 'hello', 0
	L19 BYTE 'hello ', 0
	L20 SWORD 1
	L21 BYTE ' == ', 0
	L22 BYTE ' != ', 0
	L23 SWORD 1
	L24 SWORD 1
	L25 BYTE 'true', 0
	L26 SWORD 0

.data
	maxres SWORD 0
	maind SWORD 0
	maina SWORD 0
	mainb SWORD 0
	mainstr3 DWORD 0
	mainstr4 DWORD 0
	mainres SWORD 0
	maininfo SWORD 0

.code
max PROC maxa : SWORD, maxb : SWORD
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
	pop maina
	push L5
	pop ebx
	push L6
	pop eax
	sub ebx, eax 
	push ebx
	pop ebx
	push offset L8
	push offset L7
	call _pow
	 push eax
	add ebx, eax 
	push ebx
	pop maina
	push L9
	pop mainb
	 mov ebx, ecx
	push offset L10
	call _printS
	 mov ecx, ebx
	movzx ecx, L11
p2:
	 mov ebx, ecx
	push mainb
	call _printN
	 mov ecx, ebx
	push mainb
	pop ebx
	push L12
	pop eax
	add ebx, eax 
	push ebx
	pop mainb
loop p2
	mov ax, mainb
	cmp ax, maina
	je p3
	jg p3
	jl p4
p3:
	 mov ebx, ecx
	push offset L13
	call _printS
	 mov ecx, ebx
	jmp ife1
p4:
	 mov ebx, ecx
	push offset L14
	call _printS
	 mov ecx, ebx
ife1:
	mov ax, maina
	cmp ax, mainb
	jl p5
	jg p5
	je p6
p5:
	 mov ebx, ecx
	push offset L15
	call _printS
	 mov ecx, ebx
	 movzx eax, mainb
	push eax
	 movzx eax, maina
	push eax
	call max
	 push eax
	pop maind
	 mov ebx, ecx
	push maind
	call _printN
	 mov ecx, ebx
p6:
	 mov ebx, ecx
	push offset mainlettera
	call _printS
	 mov ecx, ebx
	 mov ebx, ecx
	push offset L17
	call _printS
	 mov ecx, ebx
	push offset L18
	pop mainstr3
	push offset L19
	pop mainstr4
	push offset mainstr4
	push offset mainstr3
	call _compare
	 push eax
	pop mainres
	 mov ebx, ecx
	push mainstr3
	call _printS
	 mov ecx, ebx
	mov ax, mainres
	cmp ax, L20
	je p7
	jg p8
	jl p8
p7:
	 mov ebx, ecx
	push offset L21
	call _printS
	 mov ecx, ebx
	jmp ife2
p8:
	 mov ebx, ecx
	push offset L22
	call _printS
	 mov ecx, ebx
ife2:
	 mov ebx, ecx
	push mainstr4
	call _printS
	 mov ecx, ebx
	push L23
	pop maininfo
	mov ax, maininfo
	cmp ax, L24
	je p9
	jg p10
	jl p10
p9:
	 mov ebx, ecx
	push offset L25
	call _printS
	 mov ecx, ebx
p10:
	push 0
	call _pause
	call ExitProcess
main ENDP
end main