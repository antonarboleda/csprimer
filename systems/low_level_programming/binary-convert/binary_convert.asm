section .text
global binary_convert
global binary_convert_optimized
binary_convert:
	xor eax, eax ; zero out return value

.loop:
	movzx edx, byte [rdi] ; c = *s
	cmp edx, 0 ; end of string?
	je .done ; return
	
	add rdi, 1 ; *s++

	shl eax, 1 ; result << 1
	cmp edx, '1' ; is c == '1'?
	jne .loop ; not equal? continue
	bts eax, 0 ; set lowest order bit
	jmp .loop
.done:
	ret

; After watching the solution video
binary_convert_optimized:
	xor eax, eax ; zero out return value

.loop:
	movzx edx, byte [rdi] ; c = *s
	cmp edx, 0 ; if at end of string
	je .done ; return
	
	add rdi, 1 ; increment rdi

	shl eax, 1 ; left shift accumulator once
	and edx, 1 ; if c is equal to '1' 
	add eax, edx 
	jmp .loop
.done:
	ret
