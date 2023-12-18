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
	L2 WORD 20
	L3 WORD 10
	mainc WORD 20
	L4 WORD 30
	L5 WORD 0

.data
	maina WORD 0
	mainb WORD 0

.code

main PROC
	push L2
	pop maina
	push L3
	pop mainb
	push mainb
	pop ebx
	push maina
	pop eax
	sub ebx, eax
	push ebx
	pop eax
	push L4
	pop ebx
	add eax, ebx
	push eax
	pop ebx
	push mainb
	pop eax
	sub ebx, eax
	push ebx
	pop eax
	push L3
	pop ebx
	add eax, ebx
	push eax
	push mainc
	call _printN
	push 0
	call _pause
	call ExitProcess
main ENDP
end main