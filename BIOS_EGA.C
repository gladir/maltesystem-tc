/**********************************************************************/
/*                                                                    */
/*                      Malte System/BIOS by EGA                      */
/*                            1992/10/18                              */
/*                                                                    */
/*              Copyright (C) par les Chevaliers de Malte             */
/*                                                                    */
/**********************************************************************/

//
//       *** Summary information ***
//
//  The file name is        : BIOS_EGA.C
//  The header file name is : VIDEO\EGA\BIOS_EGA.H
//  Created the             : 1992/06/30
//  Author is               : Sylvain Maltais
//

#include "DOS.H"
#include <VIDEO\EGA\BIOS_EGA.H>

void BIOS_EGA_Blink(Byte Autorise)
{
 asm MOV AX,0x1003;
 asm MOV BL,Autorise;
 asm INT 0x10;
}

LongWord BIOS_EGA_SizeMemory(void)
{
 Byte Base;
 asm MOV AH,0x12;
 asm MOV BL,0x10;
 asm INT 0x10;
 asm MOV Base,BL;
 return(((Base == 0x10) ? 0 : ((Base+1)*0x10000)));
}

Byte BIOS_IsEGA(void)
{
 Byte Base;
 asm MOV AH,0x12;
 asm MOV BL,0x10;
 asm INT 0x10;
 asm MOV Base,BL;
 return((Base == 0x10) ? 0 : 1);
}

void BIOS_SetPaletteEGA(Byte Registre, Byte Color)
{
 asm MOV AX,0x1000;
 asm MOV BL,Color;
 asm MOV BH,Registre;
 asm INT 0x10;
}

void BIOS_SetMatrix8x8(Byte Table)
{
 asm MOV AX,0x1112;
 asm MOV BL,Table;
 asm INT 0x10;
}

void BIOS_SetMatrix8x14(Byte Table)
{
 asm MOV AX,1111;
 asm MOV BL,Table;
 asm INT 0x10;
}

void BIOS_SetScanLine(Byte Format)
{
 asm MOV AH,0x12;
 asm MOV BL,0x30;
 asm MOV AL,Format;
 asm INT 0x10;
}

void BIOS_PutStringCoding(Byte X, Byte Y, Word Num, Word Segment, Word Offset, Byte Page)
{
 asm MOV DL,X;
 asm MOV DH,Y;
 asm MOV CX,Num;
 asm MOV BH,Page;
 asm MOV ES,Segment;
 asm MOV BP,Offset;
 asm MOV AX,0x1302;
 asm INT 0x10;
}