;Federico Santucci, 3AIN
	org 0h
	jp main
	org 100h
main	ld HL, 200h
	ld DE, 0h
	ld B, fh
	call min
	ld sp, 302h
	push DE
	halt

min	push BC
	push HL
	ld A, (HL)
loop	dec B
	jr z, endFun
	inc HL
	ld C, (HL)
	cp C
	jr C, else
	ld A, C
	ld D, H ; separated ld of
	ld E, L ; 16bit register
else	jr loop
endFun	pop HL
	pop BC
	ret