/**********************************************************************/
/*                                                                    */
/*                     Malte System/BIOS Cursor                       */
/*                            1992/07/02                              */
/*                                                                    */
/*              Copyright (C) par les Chevaliers de Malte             */
/*                                                                    */
/**********************************************************************/

//
//          *** Summary information ***
//
//  The file name is        : CBIOS.C
//  The header file name is : VIDEO\CURSOR\BIOS.H
//  Created the             : 1992/07/02
//  Author is               : Sylvain Maltais
//

#include <VIDEO\CURSOR\BIOS.H>

void BIOS_CloseCursor(void)
{
 BIOS_SetCursor(0x20,0x20);
}

void BIOS_SetCursor(Byte Start, Byte End)
{
 asm MOV AH,0x01;
 asm MOV CH,Start;
 asm MOV CL,End;
 asm INT 0x10;
}

void BIOS_SetPosCursor(Byte X, Byte Y, Byte Page)
{
 asm MOV AH,0x02;
 asm MOV BH,Page;
 asm MOV DH,Y;
 asm MOV DL,X;
 asm INT 0x10;
}
