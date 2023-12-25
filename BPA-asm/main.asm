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
	L2 SWORD 1
	L3 SWORD 1
	L4 SWORD 10
	L5 SWORD 12
	L6 BYTE 'Max are: ', 0
	L7 BYTE 'Min are: ', 0
	L8 SWORD 0

.data
	maxres SWORD 0
	minresult SWORD 0
	maincos SWORD 0
	mainb SWORD 0
	maina SWORD 0
	mainlclmax SWORD 0
	mainlclmin SWORD 0

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

min PROC mina : SWORD, minb : SWORD
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
	push L3
	pop eax
	sub ebx, eax 
	push ebx
	pop maincos
loop p4
	push L4
	pop maina
	push L5
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
	 mov ebx, ecx
	push offset L6
	call _printS
	 mov ecx, ebx
	 mov ebx, ecx
	push mainlclmax
	call _printN
	 mov ecx, ebx
	 mov ebx, ecx
	push offset L7			
	call _printS
	 mov ecx, ebx
	 mov ebx, ecx
	push mainlclmin
	call _printN
	 mov ecx, ebx
	push 0
	call _pause
	call ExitProcess
main ENDP
end main