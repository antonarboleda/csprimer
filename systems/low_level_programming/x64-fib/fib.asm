section .text
 ; align the stack on every call - watch the video. Stack should be a multiple 
 ; of 16.
 ;
 ; int fib (int n) {
 ;	int result;
 ; 	if (n <= 1) {
 ;		return n; 
 ;	} else { 
 ;		result = fib(n - 1) + fib(n - 2);
 ;	}
 ; 	return result;
 ; } 
 ; 

global fib
global P 
global rfact

fib:
	push rbp ; save rbp to stack
	push rbx ; save rbx to stack
	mov rbp, rdi ; save value of n to rbp
	mov eax, edi ; base case: if (n <= 1) return n; 
	cmp edi, 1
	jle .done

	sub ebp, 1 ; n - 1
	mov edi, ebp ; move n - 1  into 1st arg
	call fib ; fib(n - 1)
	mov ebx, eax ; save  result
	sub ebp, 1 ;
	mov edi, ebp ; move rbp into first arg
	call fib ; fib(n - 2)
	add eax, ebx ; result = fib(n - 1) + fib(n - 2)
.done:
	pop rbx
	pop rbp
	ret

fib_v2:
	mov eax, edi ; base case: if (n <= 1) return n; 
	cmp edi, 1
	jle .end

	push rdi ; save n to stack
	sub edi, 1 ; fib(n - 1) 
	call fib ; 
	pop rdi ; pop n from stack back into rdi

	push rax ; push fib(n - 1) to stack as eax will be clobbered
	sub edi, 2 ; n - 2
	call fib ; fib(n - 2)
	pop rcx ; pop return value of fib(n-1) to rcx and ...
	add eax, ecx ; ... add to return value of fib(n-2)
.end:
	ret
	
; practice in order to solve fibonacci
rfact:
	push rbx
	mov rbx, rdi
	mov eax, 1
    cmp rdi, 1
	jle .l35
	sub rdi, 1
	call rfact 
	imul rax, rbx 
.l35:
	pop rbx
	ret
