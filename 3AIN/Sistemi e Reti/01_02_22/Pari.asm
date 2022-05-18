;Federico Santucci, 3AIN
	ld HL, 200h
	ld A, 02h
L1	ld (HL), A
	inc HL
	inc A
	inc A
	cp 24h
	jp NZ, L1
	halt