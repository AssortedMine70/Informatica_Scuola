;Federico Santucci, 3AIN
	org 0h
	jp main
	org 100h
main	ld SP, ffh
	ld HL, ffh
	ld B, 10h
	call sSort
	halt

min	push BC
	push HL
	ld DE, 0h
	ld A, (HL)
loop1	dec B
	jr z, endFun
	inc HL
	ld C, (HL)
	cp C
	jr C, else
	ld A, C
	ld D, H ; separated ld of
	ld E, L ; 16bit register
else	jr loop1
endFun	pop HL
	pop BC
	ret

swap	push AF
	push BC
	ld A, (DE)
	ld B, (HL)
	ld C, A
	ld A, B
	ld B, C
	ld (DE), A
	ld (HL), B
	pop BC
	pop AF
	ret

sSort	push HL
loop2	dec B
	jr z, endSub
	inc HL
	call min
	call swap
	jr loop2
endSub	pop HL
	ret