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
	L2 SWORD 1539
	L3 SWORD 921
	maincos SWORD 2462
	L4 SWORD 5
	L5 SWORD 3
	L6 SWORD 12
	L7 SWORD 0
	L8 BYTE 'Output of values c and a:', 0
	L9 BYTE 'max of a and b are: ', 0
	L10 BYTE 'd', 0
	L11 BYTE 'Hello world', 0
	L12 BYTE 'Output of string str1 and str2:', 0
	L13 BYTE 'lexicographic string comparison str3 and str4:', 0
	L14 BYTE 'hello', 0
	L15 BYTE 'hello ', 0
	L16 SWORD 1
	L17 SWORD 1
	L18 BYTE 'are equels', 0
	L19 BYTE 'are not the same', 0
	L20 SWORD 0

.data
	maxres SWORD 0
	maina SWORD 0
	mainb SWORD 0
	mainc SWORD 0
	maind SWORD 0
	mainres SWORD 0
	mainstr1 DWORD 0
	mainstr2 DWORD 0
	mainstr3 DWORD 0
	mainstr4 DWORD 0
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
	pop ebx
	push L3
	pop eax
	add ebx, eax 
	push ebx
	pop maina
	push L6
	pop mainc
	movzx ecx, mainc
p2:
	 mov ebx, ecx
	push mainc
	call _printN
	 mov ecx, ebx
loop p2
	push L7
	pop mainb
	 mov ebx, ecx
	push offset L8
	call _printS
	 mov ecx, ebx
	 mov ebx, ecx
	push mainc
	call _printN
	 mov ecx, ebx
	 mov ebx, ecx
	push maina
	call _printN
	 mov ecx, ebx
	mov ax, maina
	cmp ax, mainb
	jl p3
	jg p3
	je p4
p3:
	 mov ebx, ecx
	push offset L9
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
p4:
	push offset L10
	pop mainstr1
	push offset L11
	pop mainstr2
	 mov ebx, ecx
	push offset L12
	call _printS
	 mov ecx, ebx
	 mov ebx, ecx
	push mainstr1
	call _printS
	 mov ecx, ebx
	 mov ebx, ecx
	push mainstr2
	call _printS
	 mov ecx, ebx
	 mov ebx, ecx
	push offset L13
	call _printS
	 mov ecx, ebx
	push offset L14
	pop mainstr3
	push offset L15
	pop mainstr4
	push offset mainstr4
	push offset mainstr3
	call _compare
	 push eax
	pop mainres
	push L16
	pop maininfo
	mov ax, mainres
	cmp ax, L17
	je p5
	jg p6
	jl p6
p5:
	 mov ebx, ecx
	push offset L18
	call _printS
	 mov ecx, ebx
	jmp ife1
p6:
	 mov ebx, ecx
	push offset L19
	call _printS
	 mov ecx, ebx
ife1:
	push 0
	call _pause
	call ExitProcess
main ENDP
end main