; ----------------------------------------------------------------------------------------
; An assembly program to determine whether a string is a pangram
; To run: make
; To debug: 1. make 2. Then run lldb tests
; ----------------------------------------------------------------------------------------

%define MASK 0x07fffffe
section .text
global pangram
global pangram2
pangram:
	xor eax, eax                  ; zero out return value
	xor r8d, r8d                  ; zero out bitset
	mov edx, 0x07fffffe           ; mask value
	cmp BYTE[rdi], 0              ; empty string check
	je _done; 

_loop:
	add     rdi, 1                
	
	cmp BYTE[rdi - 1], 'a'         ; ignore the first 64 chars in the ascii table
	jl _loop                       ; continue 

	movzx   ecx, BYTE[rdi - 1]    ; move byte into lower order byte of RBX (32 bit register)
	and     cl, 0x1f              ; (c & 0x1f). c is the shift value

	bts     r8d, ecx              ; bitset with value at ecx
	cmp     BYTE[rdi], 0 	      ; check if at end of the string
	jne      _loop                ; continue if not at end of string

_done:
	and     r8d, edx               ; Performs bitmask op - (bitset & mask)
	cmp     r8d, 0x07fffffe               ; if value == mask, return
	sete al 
	ret


; notes for improvement
; bts - bitset
; You can use macros in nasm
; use movzx to zero out higher order bits that aren't used 
; Instead of branch equal, use set equal to set the lower order bit of a register

pangram2:
	xor ecx, ecx
.loop:
	movzx edx, byte [rdi] ; c = *s
	cmp edx, 0 ; if at end of string,
	je .end ; terminate loop
	
	add rdi, 1 ; s++ ; increment
	cmp edx, '@' ; if c is in first 64 chars of ascii table, 
	jl .loop ; continue
	bts ecx, edx ; set the bit in bitset using the value in edx
	jmp .loop

.end:
	xor eax, eax  ; zero out return value
	and ecx, MASK ; mask the bitset
	cmp ecx, MASK ; compare masked value with mask
	sete al ; set lowest order byte of eax register to on if equal
	ret