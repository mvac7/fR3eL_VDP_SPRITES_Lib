/* =============================================================================   
# VDP_SPRITE MSX SDCC Library (fR3eL Project)

- Version: 1.2 (11/07/2025)
- Author: mvac7/303bcn
- Architecture: MSX
- Format: SDCC Relocatable object file (.rel)
- Programming language: C and Z80 assembler
- Compiler: SDCC 4.4 or newer 

## Description:
Open Source library with functions to directly access to sprites of the 
TMS9918A.

It's complemented with the VDP TMS9918A MSX SDCC Library (fR3eL Project).
 https://github.com/mvac7/SDCC_TMS9918A_Lib


## History of versions (dd/mm/yyyyy):
- v1.2 (11/07/2025) 
	- Update to SDCC (4.1.12) Z80 calling conventions
	- Move PUTSPRITE function to VDP_TMS9918A library
	- Merge UnsetEarlyClock functionality into SetEarlyClock
	- Maintain the EarlyClock value in the SetSpriteColor function
- v1.1 (2/2/2017)
- v1.0 ?
============================================================================= */ 

#include "../include/VDP_SPRITES.h"
#include "../include/msxSystemVariables.h"



#define YHIDDEN  0xD1   ; concealment of the sprite outside the limits of the screen in TMS9918A modes



char SPRITEYBUFF[32];



/* =============================================================================
SetSpritePattern
Description: 
		Assign a pattern to a sprite plane.
Input:	[char] sprite plane (0-31) 
		[char] pattern
Output:	-
============================================================================= */
void SetSpritePattern(char plane, char pattern) __naked
{
plane;		//A
pattern;	//L
__asm

	ld   C,L
	
	call _GetSPRattrVADDR	//Input: A -->plane; Output: HL -->VRAM addr
	inc  HL
	inc  HL

	ld   E,C
	call GetSpritePattern	//Input: E -->Sprite pattern; Output: A -->pattern position
	jp   WriteByteToVRAM

__endasm;
}



/* =============================================================================
SetSpriteColor
Description: 
		Assign a color to a sprite plane.
Input:	[char] sprite plane (0-31) 
		[char] color (0-15)
Output:	-
============================================================================= */
void SetSpriteColor(char plane, char color) __naked
{
plane;	//A
color;	//L
__asm
	ld   C,L
	
	call _GetSPRattrVADDR	//Input: A -->plane; Output: HL -->VRAM addr

	inc  HL
	inc  HL
	inc  HL

	call ReadByteFromVRAM	//Read VRAM
	bit  7,A
	ld   A,C
	jp   Z,WriteByteToVRAM	//write to VRAM (OAM) without EarlyClock
	or   #128				//turn EarlyClock bit ON
	jp   WriteByteToVRAM	//write to VRAM (OAM)

__endasm;
}



/* =============================================================================
SetSpritePosition
Description: 
		Assigns the position coordinates of a sprite plane.
Input:	[char] sprite plane (0-31) 
		[char] x 
		[char] y
Output:	-
============================================================================= */
void SetSpritePosition(char plane, char x, char y)
{
plane;	//A
x;		//L
y;		//Stack
__asm
	push IX
	ld   IX,#0
	add  IX,SP

	ld   C,L
	
	call _GetSPRattrVADDR	//Input: A -->plane; Output: HL -->VRAM addr

	ld   A,4(ix)	//y
	call WriteByteToVRAM

	ld   A,C		//x
	call _FastVPOKE

	pop  IX
__endasm;
}



/* =============================================================================
SetSpriteVisible
Description: 
		Hides or shows a sprite plane.
Input:	[char] sprite plane (0-31) 
		[char] or [boolean]/[switcher] visible state: 
														0/false/OFF = hidden
														1/true/ON = visible
Output:	-
============================================================================= */
void SetSpriteVisible(char plane, char state)
{
plane;	//A
state;	//L
__asm

	ld   C,L        

	ld   IY,#_SPRITEYBUFF
	ld   D,#0
	ld   E,A
	add  IY,DE

	call _GetSPRattrVADDR	//Input: A -->plane; Output: HL -->VRAM addr

	ld   A,C				//state
	or   A					//0 = off
	jr   Z,SPRITE_hide

//makes the sprite visible
	ld   A,(IY)				//restore Y value  
	jp   WriteByteToVRAM	//write to VRAM (OAM)


//hide the sprite
SPRITE_hide:
	call ReadByteFromVRAM	//read a byte from VRAM. Input:HL=VRAMaddr; Output:A
	cp   #YHIDDEN
	ret  Z					//if sprite hidden then Dont overwrite 

	ld   (IY),A				//save the Y coordinate
	ld   A,#YHIDDEN
	jp   WriteByteToVRAM	//write the hiding position
  
__endasm;
}



/* =============================================================================
SetEarlyClock
Description: 
		Enable or Disable Early Clock of a sprite plane. 
		EC: Move 32 points to the left the X position of the sprite.
Input:	[char] sprite plane (0-31)
		[char] or [boolean]/[switcher] EC state: 
									0/false/OFF = disable
									1/true/ON = enable
Output:	-
============================================================================= */
void SetEarlyClock(char plane, char state) __naked
{
plane;	//A
state;	//L
__asm

	LD   C,L	//<--- state
	
	call _GetSPRattrVADDR	//Input: A -->plane; Output: HL -->VRAM addr

	inc  HL
	inc  HL
	inc  HL					//set the address to the color position
	push HL

	call ReadByteFromVRAM	//read a byte from VRAM. Input:HL=VRAMaddr; Output:A
  
	bit  0,C				//IF state enable?
	jr   Z,SPRITE_disable
	
	or   #128				//enable EC
	jr   SPRITE_EC_WRVRAM

SPRITE_disable:
	and  #127				//disable EC
 
SPRITE_EC_WRVRAM: 
	pop  HL
	jp   WriteByteToVRAM

__endasm;
}
