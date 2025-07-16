# How to use the VDP_SPRITES_MSXBIOS Library

| Attention! |
| :---       |
| The following document has been written using an English translator.<br/>You can participate in the improvement of this document, transmitting your corrections or suggestions in the issues of this project or the main fR3eL project.<br/>Thanks for understanding. |

<br/>

## Index

- [1 Description](#1-Description)
- [2 Requirements](#2-Requirements)
- [3 Functions](#3-Functions)
	- [3.1 SetSpritePattern](#31-SetSpritePattern)
	- [3.2 SetSpriteColor](#32-SetSpriteColor)
	- [3.3 SetSpritePosition](#33-SetSpritePosition)
	- [3.4 SetSpriteVisible](#34-SetSpriteVisible)
	- [3.5 SetEarlyClock](#35-SetEarlyClock)
	- [3.6 UnsetEarlyClock](#36-UnsetEarlyClock)
- [4 Code Example](#4-Code-Example)
- [5 References](#5-References)

<br/>

---

## 1 Description

Open Source library with functions to directly access to sprites of the TMS9918A.

Provides a set of specific functions to handle Sprites such as positioning, color, pattern assignment, visibility and EarlyClock.

It is complemented with the [VDP_TMS9918A_MSXBIOS Library](https://github.com/mvac7/SDCC_VDP_TMS9918A_MSXROM_Lib), necessary for the initialization of the screen and sprites mode.

You can combine the use of this library's functions with the PUTSPRITE function included in the VDP_TMS9918A library, which allows for a more agile way of initializing a Sprite.

This library is designed for use only with the VDP TMS9918A.
It can be used in Graphic 3 mode (Screen 4) on the V9938 or higher, but will not display correctly, as the color mapping and EarlyClock functions will not work because they must write to a separate color table. 
This functionality has not been added to this library to keep its size small.

It uses MSX BIOS functions, so it is designed to develop applications in ROM or MSXBASIC environments, using the Small Device C Compiler [(SDCC)](http://sdcc.sourceforge.net/) cross compiler.

These libraries are part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

This project is open source under the [MIT license](../LICENSE).
You can add part or all of this code in your application development or include it in other libraries/engines.

<br/>

---

## 2 Requirements

- [Small Device C Compiler (SDCC) v4.4](http://sdcc.sourceforge.net/)
- [Hex2bin v2.5](http://hex2bin.sourceforge.net/)
- fR3eL [VDP_TMS9918A_MSXBIOS](https://github.com/mvac7/SDCC_VDP_TMS9918A_MSXROM_Lib) Library

<br/>

---


## 3 Functions


### 3.1 SetSpritePattern

<table>
<tr><td colspan=3><b>SetSpritePattern</b></td></tr>
<tr><td colspan=3>Assign a pattern to a sprite plane</td></tr>
<tr><td><b>Function</b></td><td colspan=2>SetSpritePattern(char plane, char pattern)</td></tr>
<tr><th rowspan=2>Input</th><td>char</td><td>sprite plane (0-31)</td></tr>
<tr><td>char</td><td>pattern</td></tr>
<tr><th>Output</th><td colspan=2>---</td></tr>
</table>

#### Example:

```c
	SetSpritePattern(4, 2);
	SetSpritePattern(7, numPat);
```

<br/>

### 3.2 SetSpriteColor

<table>
<tr><td colspan=3><b>SetSpriteColor</b></td></tr>
<tr><td colspan=3>Assign a color to a sprite plane</td></tr>
<tr><td><b>Function</b></td><td colspan=2>SetSpriteColor(char plane, char color)</td></tr>
<tr><th rowspan=2>Input</th><td>char</td><td>sprite plane (0-31)</td></tr>
<tr><td>char</td><td>color (0-15)</td></tr>
<tr><th>Output</th><td colspan=2>---</td></tr>
</table>

#### Example:

```c
	SetSpriteColor(4, 6);
	SetSpriteColor(7, DARK_RED); //Color label requires include in VDP_TMS9918A_MSXBIOS.h
```

<br/>

### 3.3 SetSpritePosition

<table>
<tr><td colspan=3><b>SetSpritePosition</b></td></tr>
<tr><td colspan=3>Assigns the position coordinates of a sprite plane</td></tr>
<tr><td><b>Function</b></td><td colspan=2>SetSpritePosition(char plane, char x, char y)</td></tr>
<tr><th rowspan=3>Input</th><td>char</td><td>sprite plane (0-31)</td></tr>
<tr><td>char</td><td>x</td></tr>
<tr><td>char</td><td>y</td></tr>
<tr><th>Output</th><td colspan=2>---</td></tr>
</table>

#### Example:

```c
	SetSpritePosition(4, 100, 80);
	SetSpritePosition(7, spr_Xpos, spr_Ypos);
```

<br/>

### 3.4 SetSpriteVisible

<table>
<tr><td colspan=3><b>SetSpriteVisible</b></td></tr>
<tr><td colspan=3>Hides or shows a sprite plane</td></tr>
<tr><td><b>Function</b></td><td colspan=2>SetSpriteVisible(char plane, char state)</td></tr>
<tr><th rowspan=2>Input</th><td>char</td><td>sprite plane (0-31)</td></tr>
<tr><td>char or boolean/switcher</td><td>visible state:<br/>0/false/OFF = hidden; 1/true/ON = visible</td></tr>
<tr><th>Output</th><td colspan=2>---</td></tr>
</table>

| Note: |
| :---  |
| To be able to use `boolean` or `switcher` types, you need to include [newTypes.h](https://github.com/mvac7/SDCC_MSX_fR3eL/blob/main/include/newTypes.h) in your source code. |


#### Example:

```c
	SetSpriteVisible(4,0);		//hidden
	SetSpriteVisible(7,false);	//hidden
	SetSpriteVisible(8,ON);		//visible
```

<br/>

### 3.5 SetEarlyClock

<table>
<tr><td colspan=3><b>SetEarlyClock</b></td></tr>
<tr><td colspan=3>Enable or Disable the EarlyClock of a sprite plane.<br/>Move 32 points to the left the X position of the Sprite.</td></tr>
<tr><td><b>Function</b></td><td colspan=2>SetEarlyClock(char plane, char state)</td></tr>
<tr><th rowspan=2>Input</th><td>char</td><td>sprite plane (0-31)</td></tr>
<tr><td>char or boolean/switcher</td><td>EC state:<br/>0/false/OFF = disable<br/>1/true/ON = enable</td></tr>
<tr><th>Output</th><td colspan=2>---</td></tr>
</table>

#### Example:

```c
	SetEarlyClock(4,1);		//Enable EC on Sprite Plane 4
	SetEarlyClock(5,0);		//Disable EC on Sprite Plane 5
	SetEarlyClock(6,ON);	//Enable EC on Sprite Plane 6
	SetEarlyClock(7,false);	//Disable EC on Sprite Plane 7
```

<br/>


---

## 4 Code Example

In the following source code you can see a simple example of using the library. 

You can find more extensive examples in the git project sources.

<br/>

### Example01.c

In this source code you will find a simple example of how to use this library.

Requires the following items:
- Startup file for MSX 8/16K ROM [crt0_MSX816kROM4000](https://github.com/mvac7/SDCC_startup_MSX816kROM4000)
- [VDP_TMS9918A_MSXBIOS Library](https://github.com/mvac7/SDCC_VDP_TMS9918A_MSXROM_Lib)
- [VDP_SPRITES_MSXBIOS Library](https://github.com/mvac7/SDCC_VDP_SPRITES_MSXROM_Lib)

<br/>

And you need the following applications to compile and generate the final ROM:
- [Small Device C Compiler (SDCC) v4.4](http://sdcc.sourceforge.net/)
- [Hex2bin v2.5](http://hex2bin.sourceforge.net/)

<br/>

This example performs the following actions:
1. Initializes the screen to Graphic1 mode (Screen 1) with 16x16 sprites in 2x zoom mode.
1. Copies the graphics of four sprites to the sprite pattern area in VRAM.
1. Displays two sprites using the PUTSPRITE instruction (included in the VDP_TMS9918A_MSXBIOS library).
1. Displays two sprites using the SetSpritePattern, SetSpriteColor, and SetSpritePosition functions (VDP_SPRITES_MSXBIOS library).
1. Hides the sprite on plane 1 using the SetSpriteVisible function.
1. Enable the Early Clock on plane 0 (shifts 32 pixels to the left) using the SetEarlyClock function.
1. Disable the Early Clock on plane 0.

<br/>

![Example screenshot](../examples/data/EXAMPLE1_01.png)

<br/>

#### Source Code:

```c
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
#include "VDP_TMS9918A_MSXBIOS.h"
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
```

<br/>

#### For compile:

To obtain a binary with the ROM of the example program, execute the following steps in a Windows command line (CMD):

1. Compile with SDCC

```
sdcc -mz80 --code-loc 0x4020 --data-loc 0xC000 --use-stdout --no-std-crt0 crt0_MSX816kROM4000.rel VDP_TMS9918A_MSXBIOS.rel VDP_SPRITES_MSXBIOS.rel Example01.c
```

<br/>

2. If the compiler has not displayed an error then convert the .ihx file to binary with hex2bin

```
hex2bin -e bin -l 2000 Example01.ihx
```

<br/>

3. Rename the binary to .ROM

```
rename Example01.bin EXAMPLE1.ROM
```

<br/>

---

## 5 References

- Texas Instruments [TMS9918A application manual](http://map.grauw.nl/resources/video/texasinstruments_tms9918.pdf) `PDF`
- Texas Instruments [VDP Programmer’s Guide](http://map.grauw.nl/resources/video/ti-vdp-programmers-guide.pdf) `PDF`
- Texas Instruments [TMS9918A VDP](http://bifi.msxnet.org/msxnet/tech/tms9918a.txt) by Sean Young `TXT`
- The MSX Red Book · [2 Video Display Processor](https://github.com/gseidler/The-MSX-Red-Book/blob/master/the_msx_red_book.md#chapter_2) `HTML`
- YAMAHA [9938 Technical Data Book](http://map.grauw.nl/resources/video/v9938/v9938.xhtml) `HTML`

<br/>

---

![Creative Commons License](https://i.creativecommons.org/l/by-nc/4.0/88x31.png) 
<br/>This document is licensed under a [Creative Commons Attribution-NonCommercial 4.0 International License](http://creativecommons.org/licenses/by-nc/4.0/).
