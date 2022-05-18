;Federico Santucci, 3AIN
	org 0h
	jp main
	org 100h
main	ld SP, FFh
	ld IX, 200h
	ld B, 5h
	call comp
	halt

comp	push AF
loop	ld C, (IX+0h)
	ld A, ffh
	sub C
	ld (IX+0h), A
	dec B
	cp 0h
	inc IX
	jr nz, loop
	pop AF
	ret