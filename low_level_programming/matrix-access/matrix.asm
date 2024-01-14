section .text
global index
global index_optimized
global index_lea
	; rdi: matrix
	; esi: rows
	; edx: cols
	; ecx: rindex
	; r8d: cindex

; My initial solution
index:
	; find the correct row
	imul ecx, 4     ; multiply by the width of an int
	imul ecx, edx   ; multiply by width of each row
	
	; find the correct column
	imul r8d, 4     ; get column offset
	add  ecx, r8d   ; increment offset by column offset

	; The offset should be pointing at the row and column here
	add  rdi, rcx   ; move pointer in rdi by offset
	mov  rax, [rdi] ; dereference rdi and move value into the return value
	ret

; Optimized solution after watching the video
index_optimized:
	imul ecx, edx   ; multiply by width of each row
	add  ecx, r8d   ; increment offset by column offset
	mov  eax, [rdi + 4 * rcx] ; dereference rdi and move value into the return value
	ret


index_lea:
    imul edx, ecx               ; rindex * cols
    lea rcx, [rdi + rdx * 4]    ; matrix + rindex * cols * 4
    lea rdi, [r8d * 4]          ; cindex * 4
    add rcx, rdi                
    mov eax, [rcx]
    ret