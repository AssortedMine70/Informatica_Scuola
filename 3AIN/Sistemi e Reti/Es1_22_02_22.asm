;Federico Santucci, 3AIN
	org 0h
	jp main
	org 100h
main	ld HL, 200h
	ld A, 20h
loop	ld B, (HL)
	inc B
	ld (HL), B
	inc L
	cp L
	jr nz, loop
	halt