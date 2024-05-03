/**********************************************************************/
/*                                                                    */
/*                      Malte System/Direct Cursor                    */
/*                             1992/10/18                             */
/*                                                                    */
/*             Copyright (C) par les Chevaliers de Malte              */
/*                                                                    */
/**********************************************************************/

//
//        *** Summary information ***
//
//  The file name is        : CDIRECT.C
//  The header file name is : VIDEO\CURSOR\DIRECT.H
//  Created the             : 1992/08/18
//  Author is               : Sylvain Maltais
//

#include <VIDEO\CURSOR\DIRECT.H>

extern

 struct {
         Byte Shade;
         Byte SpaceBorde;
         Byte Borde[8];
         Word Address;
         Word ColnDouble;
         Byte Coln;
         Byte Line;
         Byte MaxX;
         Byte MaxY;
         Byte HalfMaxX;
         Byte RX;
         Byte RY;
         Byte ColorNor;
         Byte LastColor;
        }
              VD;

void IO_CloseCursor(void)
{
 asm XOR AX,AX;
 asm MOV ES,AX;
 asm MOV DX,ES:[0x0463];
 asm MOV AX,0x200A;
 asm OUT DX,AX;
 asm INC AL;
 asm OUT DX,AX;
}

void IO_SetCursor(Byte Start, Byte End)
{
 asm XOR AX,AX;
 asm MOV ES,AX;
 asm MOV DX,ES:[0x0463];
 asm MOV AL,0x0A;
 asm MOV AH,Start;
 asm OUT DX,AX;
 asm INC AL;
 asm MOV AH,End;
 asm OUT DX,AX;
}

void IO_SetPosCursor(Byte X, Byte Y)
{
 Byte Coln = VD.Coln;
 asm XOR AX,AX;
 asm MOV ES,AX;
 asm MOV AL,Y;
 asm MOV AH,Coln;
 asm MUL AH;
 asm XOR DH,DH;
 asm MOV DL,X;
 asm ADD AX,DX;
 asm MOV DX,ES:[0x0463];
 asm MOV BX,AX;
 asm MOV AL,0x0E;
 asm OUT DX,AX;
 asm INC AL;
 asm MOV AH,BL;
 asm OUT DX,AX;
}

void IO_SetPosCursorHome(void)
{
 asm XOR AX,AX;
 asm MOV ES,AX;
 asm MOV DX,ES:[0x0463];
 asm MOV AL,0x0E;
 asm OUT DX,AX;
 asm INC AL;
 asm OUT DX,AX;
}