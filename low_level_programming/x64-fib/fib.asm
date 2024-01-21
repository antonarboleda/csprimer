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
	mov ebp, edi ; save value of n to rbp
	mov eax, edi ; result = n
	cmp edi, 1 ; n <= 1?
	jle .done

	sub ebp, 1 ; n - 1
	mov edi, ebp ; move into 1st arg
	call fib ; fib(n - 1)
	mov ebx, eax ; save result
	sub ebp, 1 ; todo use lea 
	mov edi, ebp ; move rbp into first arg
	call fib ; fib(n - 2)
	add eax, ebx ; result = fib(n - 1) + fib(n - 2)
.done:
	pop rbx
	pop rbp
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
