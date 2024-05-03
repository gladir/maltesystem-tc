/**********************************************************************/
/*                                                                    */
/*                    Malte System/BIOS Keyboard                      */
/*                            1992/10/18                              */
/*                                                                    */
/*              Copyright (C) par les Chevaliers de Malte             */
/*                                                                    */
/**********************************************************************/

//
//        *** Summary information ***
//
//  The file name is        : BIOS_KEY.C
//  The header file name is : KEYBOARD\BIOS_KEY.H
//  Created the             : 1992/07/08
//  Author is               : Sylvian Maltais
//

#include <KEYBOARD\BIOS_KEY.H>

Word BIOS_NextKey(void)
{
 asm MOV AH,0x01;
 asm INT 0x16;
 return(_AX);
}

Word BIOS_ReadKey(void)
{
 asm XOR AH,AH;
 asm INT 0x16;
 return(_AX);
}

Byte BIOS_KeyFlags(void)
{
 asm MOV AH,0x02;
 asm INT 0x16;
 return(_AL);
}

Byte BIOS_GetModeInsert(void)
{
 asm MOV AH,0x02;
 asm INT 0x16;
 return((_AL >> 7) & 1);
}