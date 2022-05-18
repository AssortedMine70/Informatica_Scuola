;Federico Santucci, 3AIN
	org 0h
	jp main
	org 100h
main	ld B, 5h
	ld C, 0h
	call mul
	halt

mul	push BC
	ld A, 0h
	dec C
	jr z, retF
	inc C
loop	add A, B
	dec C
	jr nz, loop
retF	pop BC
	ret