default rel
; Calculates the volume of a cone using this formula
; Volume = π * r^2 * (h / 3)
; calling conventsion. xmm0 - radius. xmm1 - height

; can also use rodata instead of .data section
section .data
	pi: dd 3.14159265358979
	three: dd 3.0 

section .text
global volume
volume:
	movss xmm2, [pi] ; load pi
	movss xmm3, [three] ; load three
	
	mulss xmm0, xmm0 ; r^2
	mulss xmm0, xmm2 ; multiply by pi

	divss xmm1, xmm3 ; divide height by 3
	mulss xmm0, xmm1 ; (π * r^2) * (h / 3)
 	ret
