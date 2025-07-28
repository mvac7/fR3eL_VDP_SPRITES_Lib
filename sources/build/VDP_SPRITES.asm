;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler 
; Version 4.4.0 #14620 (MINGW64)
;--------------------------------------------------------
	.module VDP_SPRITES
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _SPRITEYBUFF
	.globl _SetSpritePattern
	.globl _SetSpriteColor
	.globl _SetSpritePosition
	.globl _SetSpriteVisible
	.globl _SetEarlyClock
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_SPRITEYBUFF::
	.ds 32
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;src\VDP_SPRITES.c:51: void SetSpritePattern(char plane, char pattern) __naked
;	---------------------------------
; Function SetSpritePattern
; ---------------------------------
_SetSpritePattern::
;src\VDP_SPRITES.c:68: __endasm;
	ld	C,L
	call	GetSPRattrVADDR
	inc	HL
	inc	HL
	ld	E,C
	call	GetSpritePattern
	jp	WriteByteToVRAM
;src\VDP_SPRITES.c:69: }
;src\VDP_SPRITES.c:81: void SetSpriteColor(char plane, char color) __naked
;	---------------------------------
; Function SetSpriteColor
; ---------------------------------
_SetSpriteColor::
;src\VDP_SPRITES.c:104: __endasm;
	ld	C,L
	call	GetSPRattrVADDR
	inc	HL
	inc	HL
	inc	HL
	call	ReadByteFromVRAM
	bit	7,A
	ld	A,C
	jp	Z,WriteByteToVRAM
	or	#128
	jp	WriteByteToVRAM
;src\VDP_SPRITES.c:105: }
;src\VDP_SPRITES.c:118: void SetSpritePosition(char plane, char x, char y)
;	---------------------------------
; Function SetSpritePosition
; ---------------------------------
_SetSpritePosition::
;src\VDP_SPRITES.c:144: __endasm;
	push	IX
	ld	IX,#0
	add	IX,SP
	ld	C,L
	call	GetSPRattrVADDR
	ld	A,4(ix)
	call	WriteByteToVRAM
	ld	A,C
	inc	HL
	call	WriteByteToVRAM
	pop	IX
;src\VDP_SPRITES.c:145: }
	pop	hl
	inc	sp
	jp	(hl)
;src\VDP_SPRITES.c:159: void SetSpriteVisible(char plane, char state)
;	---------------------------------
; Function SetSpriteVisible
; ---------------------------------
_SetSpriteVisible::
;src\VDP_SPRITES.c:194: __endasm;
	ld	C,L
	ld	IY,#_SPRITEYBUFF
	ld	D,#0
	ld	E,A
	add	IY,DE
	call	GetSPRattrVADDR
	ld	A,C
	or	A
	jr	Z,SPRITE_hide
	ld	A,(IY)
	jp	WriteByteToVRAM
SPRITE_hide:
	call	ReadByteFromVRAM
	cp	#0xD1 ; concealment of the sprite outside the limits of the screen in TMS9918A modes
	ret	Z
	ld	(IY),A
	ld	A,#0xD1 ; concealment of the sprite outside the limits of the screen in TMS9918A modes
	jp	WriteByteToVRAM
;src\VDP_SPRITES.c:195: }
	ret
;src\VDP_SPRITES.c:210: void SetEarlyClock(char plane, char state) __naked
;	---------------------------------
; Function SetEarlyClock
; ---------------------------------
_SetEarlyClock::
;src\VDP_SPRITES.c:241: __endasm;
	LD	C,L
	call	GetSPRattrVADDR
	inc	HL
	inc	HL
	inc	HL
	call	ReadByteFromVRAM
	bit	0,C
	jr	Z,SPRITE_disable
	or	#128
	jr	SPRITE_EC_WRVRAM
SPRITE_disable:
	and	#127
SPRITE_EC_WRVRAM:
	jp	WriteByteToVRAM
;src\VDP_SPRITES.c:242: }
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
