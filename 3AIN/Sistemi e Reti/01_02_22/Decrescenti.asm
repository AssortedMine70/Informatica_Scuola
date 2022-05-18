;Federico Santucci, 3AIN
	ld HL,300h
	ld A,FFh
L1	ld (HL),A
	dec A
	inc HL
	jp NZ,L1
	halt