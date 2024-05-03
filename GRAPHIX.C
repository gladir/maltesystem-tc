/**************************************************************/
/*                                                            */
/*                    Malte System/Graphix                    */
/*                         1992/10/18                         */
/*                                                            */
/*         Copyright (C) par les Chevaliers de Malte          */
/*                                                            */
/**************************************************************/

//
//       *** Summary information ***
//
//  The file name is        : GRAPHIX.C
//  The header file name is : No file
//  Created the             : 1992/08/18
//  Author is               : Sylvain Maltais
//

typedef unsigned char Byte;

Byte IsGraphic(void)
{
 Byte Accum;
 asm MOV AH,0x0D;
 asm XOR BH,BH;
 asm XOR CX,CX;
 asm XOR DX,DX;
 asm INT 0x10;
 asm MOV Accum,AL;
 asm MOV AX,0x0C01;
 asm INT 0x10;
 asm MOV AH,0x0D;
 asm INT 0x10;
 asm MOV BL,AL;
 asm MOV AH,0x0C;
 asm MOV AL,Accum;
 asm INT 0x10;
 return(_BL);
}