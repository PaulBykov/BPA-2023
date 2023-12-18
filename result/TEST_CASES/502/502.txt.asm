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
	L2 WORD 2
	L3 WORD 1
	L4 WORD 0

.data
	funcb WORD 0
	mainvariabl WORD 0

.code
func PROC funca : WORD
	push 2
	pop eax
	ret
func ENDP


main PROC
	movzx eax, L3
	push eax
	call func
	push eax
	pop mainvariabl
	push 0
	call _pause
	call ExitProcess
main ENDP
end main