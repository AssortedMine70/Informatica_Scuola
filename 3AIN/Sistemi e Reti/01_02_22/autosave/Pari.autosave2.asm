	ld HL, 200h
	ld A, 02h
L1	ld (HL), A
	inc HL
	inc A
	inc A
	
	jp L1, NZ
	halt