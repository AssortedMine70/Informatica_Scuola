;Federico Santucci, 3AIN
	org 0h
	jp main
	org 100h
main	ld SP, FFh
	ld IX, 200h
	ld B, 5h
	ld IY, 300h
	call min
	halt

min	push AF
	ld A, (IX+0h)
	ld (IY+0h), A
loop	ld A, (IY+0h)
	cp (IX+0h)
	jr c, else
	jr z, else
	ld A, (IX+0h)
	ld (IY+0h), A
else	dec B
	ld A, B
	cp 0h
	inc IX
	jr nz, loop
	pop AF
	ret