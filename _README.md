# VDP SPRITES MSX SDCC Library (fR3eL Project)

```
Author: mvac7 [mvac7303b@gmail.com]
Architecture: MSX
Format: C Object (SDCC .rel)
Programming language: C and Z80 assembler
```



## Sorry!: This text is pending correction of the English translation. <<<<<<<<




## Description

Open Source library with functions to directly access to Sprites of the TMS9918A.

Provides a set of functions for displaying Sprites, both fully (PUTSPRITE) and specific (positioning, color, pattern, visibility and EarlyClock).

Contains the PUTSPRITE function similar to that of MSX BASIC.

It is complemented with the [VDP TMS9918A MSX Library](https://github.com/mvac7/SDCC_TMS9918A_Lib), necessary for the initialization of the screen (screen and sprites mode).

It does not use the MSX BIOS, so it is suitable for creating applications for MSX-DOS and ROM format.
  
Use them for developing MSX applications using [Small Device C Compiler (SDCC)](http://sdcc.sourceforge.net/) cross compiler.

In the source code (\examples), you can find applications for testing and learning purposes.

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Enjoy it!




## History of versions

- v1.0 (04/05/2019) <<current version>>



## Requirements

* Small Device C Compiler (SDCC) v3.9 http://sdcc.sourceforge.net/
* Hex2bin v2.5 http://hex2bin.sourceforge.net/ 
* [VDP TMS9918A MSX SDCC Library](https://github.com/mvac7/SDCC_TMS9918A_Lib)



## Acknowledgments
  
I want to give a special thanks to all those who freely share their knowledge with the MSX developer community.

* Avelino Herrera > [WEB](http://msx.atlantes.org/index_es.html)
* Nerlaska > [Blog](http://albertodehoyonebot.blogspot.com.es)
* Marq/Lieves!Tuore > [Marq](http://www.kameli.net/marq/) [Lieves!Tuore](http://www.kameli.net/lt/)
* [Fubukimaru](https://github.com/Fubukimaru) > [Blog](http://www.gamerachan.org/fubu/)
* Andrear > [Blog](http://andrear.altervista.org/home/msxsoftware.php)
* Ramones > [MSXblog](https://www.msxblog.es/tutoriales-de-programacion-en-ensamblador-ramones/) - [MSXbanzai](http://msxbanzai.tni.nl/dev/faq.html)
* Sapphire/Z80ST > [WEB](http://z80st.auic.es/)
* Fernando García > [youTube](https://www.youtube.com/user/bitvision)
* Eric Boez > [gitHub](https://github.com/ericb59)
* MSX Assembly Page > [WEB](http://map.grauw.nl/resources/msxbios.php)
* Portar MSX Tech Doc > [WEB](https://problemkaputt.de/portar.htm)
* MSX Resource Center > [WEB](http://www.msx.org/)
* Karoshi MSX Community (RIP 2007-2020)
* BlueMSX emulator >> [WEB](http://www.bluemsx.com/)
* OpenMSX emulator >> [WEB](http://openmsx.sourceforge.net/)
* Meisei emulator >> ?



## Notes about operation

This library provides functions to facilitate the use of Sprites of the TMS9918A 
and is supported by the library VDP_TMS9918A_Lib, necessary for the 
initialization of the graphic modes and for the writing / reading of the VRAM.

It is designed for the creation of applications for MSX-DOS (.COM). It can be 
used for the development of ROMs, but I recommend the use of libraries based on 
the BIOS (VDP_TMS9918A_MSXROM_Lib and VDP_SPRITES_MSXROM_Lib), since they are 
lighter, thereby gaining more space for our software.

It is not useful for graphic mode G3 (screen 4), V9938 or higher, since it does 
not write in the color table of the sprites when a color is assigned or for the 
Early Clock. I have projected a specific library for this purpose.



## Functions

* void **PUTSPRITE**(char plane, char x, char y, char color, char pattern) - Displays the sprite pattern.
* void **SetSpritePattern**(char plane, char pattern) - Assign a pattern to a sprite plane.
* void **SetSpriteColor**(char plane, char color) - Assign a color to a sprite plane.
* void **SetSpritePosition**(char plane, char x, char y) - Assigns the position coordinates of a sprite plane.
* void **SetSpriteVisible**(char plane, boolean state) - Hides or shows a sprite plane.
* void **SetEarlyClock**(char plane) - Apply the Early Clock of a sprite plane. Move 32 points to the left the X position of the sprite.
* void **UnsetEarlyClock**(char plane) - Disables the Early Clock. Restore the position of a sprite plane.
