;Federico Santucci, 3AIN
	org 0h
	jp main
	org 100h
main	ld HL, 200h
	ld DE, 300h
loop	ld A, (HL)
	ld B, A
	ld A, 0h
	cp B
	jr z, else
	ld A, B
	ld (DE), A
	inc E
else	inc L
	ld A, 20h
	cp L
	jr nz, loop
	halt