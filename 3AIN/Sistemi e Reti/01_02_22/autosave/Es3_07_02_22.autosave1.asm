	;Federico Santucci, 3AIN
	org 0h
	jp 100h
	org 100h
main:	ld B, 0h
	ld HL, 200h
L1:	ld A, L
	cp 0FFh
	jr z, L2
	ld A, (HL)
	cp 0FFh
	inc HL
	jr nz, L1
	inc B
	jr L1
L2:	ld HL, 300h
	ld (HL), B
	halt