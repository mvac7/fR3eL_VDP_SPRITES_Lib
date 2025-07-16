/* =============================================================================
Example01.c
Version: 1.0 (14/06/2025)
Architecture: MSX
Format: MSX ROM 8k
Programming language: C and Z80 assembler
Compiler: SDCC 4.4 or newer

Description:
Simple example of the VDP_SPRITE_MSXBIOS Library (fR3eL Project)
============================================================================= */
#include "VDP_TMS9918A.h"
#include "VDP_SPRITES.h"

#define  HALT __asm halt __endasm   //wait for the next interrupt

void WAIT(unsigned int frames);


// SpriteSet Pattern Data - Size=16x16 - Mode=Mode1 Monocolor
// Sprite range: 0 to 3
// Size=128
const char Fruits_SSET[]={
//sprite0
0x0F,0x1F,0x3D,0x3F,0x7B,0x7C,0xBF,0xBF,
0x9F,0xEF,0x6F,0x1F,0x0F,0x05,0x05,0x1D,
0xC0,0xE0,0x60,0xC0,0x40,0x80,0x80,0x84,
0x86,0xDE,0xC0,0xC0,0x80,0x00,0x00,0xC0,
//sprite1
0x03,0x07,0x4F,0xCF,0x4D,0x4F,0x2C,0x1E,
0x3F,0x3F,0x3F,0x3F,0x1F,0x02,0x02,0x06,
0xC0,0xE2,0xE6,0xE2,0xA2,0xF4,0x38,0x7C,
0xFE,0xFE,0xFE,0xFC,0xF8,0x40,0x40,0x60,
//sprite2
0x05,0x07,0x1A,0x2E,0x6F,0x5B,0x5C,0x5B,
0x5F,0x58,0x6F,0x2D,0x16,0x02,0x02,0x06,
0x40,0xC0,0xB8,0xD4,0xD4,0x6A,0xEA,0x6A,
0xEA,0x6A,0xD4,0xD4,0xF8,0x40,0x40,0x60,
//sprite3
0x05,0x1E,0x3F,0x6F,0x57,0x6E,0x3F,0x00,
0x07,0x05,0x07,0x04,0x06,0x03,0x02,0x06,
0x60,0xF8,0xF4,0xEA,0x76,0xBE,0x7C,0x00,
0xE0,0x60,0xE0,0x20,0x60,0xC0,0x40,0x60};


void main(void) 
{
	COLOR(15,4,5);
 	SCREEN(GRAPHIC1);			// Set Screen 1
	SetSpritesSize(SPRITES16x16);
	SetSpritesZoom(1);
	
	// Copy a Sprite patterns to VRAM
	CopyToVRAM((unsigned int) Fruits_SSET,SPR_PAT,128);
	
	PUTSPRITE(0,16,100,GREEN,1);		//Put Sprite 1 on plane 0 at coordinates (16,100) (Pear)
	PUTSPRITE(1,48,100,LIGHT_YELLOW,2);	//Put Sprite 2 on plane 1 at coordinates (48,100) (Onion)
	
	//Put Sprite 3 on plane 2 (Mushroom)
	SetSpritePattern(2,3);			//assings pattern 3 to Sprite plane 2
	SetSpriteColor(2,GREY);			//set color 14 
	SetSpritePosition(2,80,132);	//Place the Sprite 2 plane at coordinates (80,132)
	
	//Put Sprite 0 on plane 3 (Cucumber)
	SetSpritePattern(3,0);			//assigns pattern 0 to Sprite plane 3
	SetSpriteColor(3,LIGHT_GREEN);	//set color 3
	SetSpritePosition(3,112,132);	//Place the Sprite 3 plane at coordinates (112,132)
	
	WAIT(120);
	
	SetSpriteVisible(1,0);	//hidde sprite plane 1 (Onion)
	
	WAIT(120);
	
	SetEarlyClock(0,1);		//enable EarlyClock in sprite plane 0 (Pear)
	
	WAIT(120);
	
	SetEarlyClock(0,0);		//disable EarlyClock in sprite plane 0
	
__asm call 0x009F __endasm;		// execute BIOS CHGET - One character input (waiting)
}


void WAIT(unsigned int frames)
{
	unsigned int i;
	for(i=0;i<frames;i++) HALT;
}