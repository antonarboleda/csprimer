; ----------------------------------------------------------------------------------------
; Takes an input value N and returns the value of the sum of all numbers 0 to N
; Notes after watching solution video
;    - use eax and edi because using ints so we only need the lower 32 bits
;    - Rather than moving a 0 into a register, it is faster to xor the register with
;      itself
;    - Use underscores to scope locally
;    - If you get better at reading, everything is more readable! Readability is 
;      is subjective, so if you can't read it it's probably because a person 
;      isn't able to comprehend that code!
;    - Dividing by a power of 2 is equal to N >= power. i.e. N / 2 == n >>= 1
; ----------------------------------------------------------------------------------------

section .text
global sum_to_n
sum_to_n: 
    mov     rax,   0                  ; set return value to 0 
	cmp     rdi,   0                  ; is n equal to zero?  
	je      done                      ; if so, return early
accumulate:
 	add     rax,   rdi                ; add n to result
	dec     rdi                       ; decrement rdi by 1
	jnz     accumulate                ; if rdi is not equal to zero, continue
done: 
	ret

global sum_to_n_optimized
sum_to_n_optimized: 
    xor     eax,   eax                ; set return value to 0 
	cmp     edi,   0                  ; is n equal to zero?  
	je      _done                     ; if so, return early
_loop:
 	add     eax,   edi                ; add n to result
	dec     edi                       ; decrement edi by 1
	jnz     _loop                      ; if edi is not equal to zero, continue
_done: 
	ret

global sum_to_n_constant_time
sum_to_n_constant_time:
	inc     eax                       ; increment result by 1
	add     eax, edi                  ; add n to eax
	imul    eax, edi                  ; multiply edi into return val
	shr     eax, 1                    ; divide by 2 which is just a right shift by 1, 
	ret     


