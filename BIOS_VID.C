/**********************************************************************/
/*                                                                    */
/*                       Malte System/BIOS Video                      */
/*                            1992/10/18                              */
/*                                                                    */
/*              Copyright (C) par les Chevaliers de Malte             */
/*                                                                    */
/**********************************************************************/

//
//        *** Summary information ***
//
//  The file name        : BIOS_VID.C
//  The header file name : VIDEO\BIOS_VID.H
//  Created the          : 1992/06/30
//  Author is            : Sylvain Maltais
//

#include <VIDEO\BIOS_VID.H>

Byte BIOS_GetAttr(Byte X, Byte Y, Byte Page)
{
 Word

      Data;

 Byte

      Rtn;

 asm MOV AH,0x03;
 asm MOV BH,Page;
 asm INT 0x10;
 asm MOV Data,DX;
 asm MOV AH,0x02;
 asm MOV DL,X;
 asm MOV DH,Y;
 asm INT 0x10;
 asm MOV AH,0x08;
 asm INT 0x10;
 asm MOV Rtn,AH;
 asm MOV AH,0x02;
 asm MOV DX,Data;
 asm INT 0x10;
 return(Rtn);
}

Byte BIOS_GetChar(Byte X, Byte Y, Byte Page)
{
 Word

      Data;

 Byte

      Rtn;

 asm MOV AH,0x03;
 asm MOV BH,Page;
 asm INT 0x10;
 asm MOV Data,DX;
 asm MOV AH,0x02;
 asm MOV DL,X;
 asm MOV DH,Y;
 asm INT 0x10;
 asm MOV AH,0x08;
 asm INT 0x10;
 asm MOV Rtn,AL;
 asm MOV AH,0x02;
 asm MOV DX,Data;
 asm INT 0x10;
 return(Rtn);
}

Byte BIOS_GetColums(void)
{
 asm MOV AH,0x0F;
 asm INT 0x10;
 return(_AH);
}

Byte BIOS_GetPage(void)
{
 asm MOV AH,0x0F;
 asm INT 0x10;
 return(_BH);
}

void BIOS_GetPosCursor(Byte *X, Byte *Y, Byte Page)
{
 Word

      Data;

 asm MOV AH,0x03;
 asm MOV BH,Page;
 asm INT 0x10;
 asm MOV Data,DX;
 *X = Lo(Data);
 *Y = Hi(Data);
}

Byte BIOS_GetVideoMode(void)
{
 asm MOV AH,0x0F;
 asm INT 0x10;
 return(_AL);
}

void BIOS_PutChar(Byte X, Byte Y, Byte Page, Byte Char)
{
 asm MOV AH,0x02;
 asm MOV DL,X;
 asm MOV DH,Y;
 asm MOV BH,Page;
 asm INT 0x10;
 asm MOV AH,0x0A;
 asm MOV AL,Char;
 asm MOV BX,0x000F;
 asm MOV CX,0x0001;
 asm INT 0x10;
}

void BIOS_SetVideoMode(char Mode)
{
 asm XOR AH,AH;
 asm MOV AL,Mode;
 asm INT 0x10;
}

void BIOS_ScrollUp_(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Color)
{
 asm MOV AX,0x0601;
 asm MOV BH,Color;
 asm MOV CL,X1;
 asm MOV CH,Y1;
 asm MOV DL,X2;
 asm MOV DH,Y2;
 asm INT 0x10;
}

void BIOS_ScrollDown_(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Color)
{
 asm MOV AX,0x0701;
 asm MOV BH,Color;
 asm MOV CL,X1;
 asm MOV CH,Y1;
 asm MOV DL,X2;
 asm MOV DH,Y2;
 asm INT 0x10;
}

void BIOS_ScrollUp(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Num, Byte Color)
{
 asm MOV AH,0x06;
 asm MOV AL,Num;
 asm MOV BH,Color;
 asm MOV CL,X1;
 asm MOV CH,Y1;
 asm MOV DL,X2;
 asm MOV DH,Y2;
 asm INT 0x10;
}

void BIOS_ScrollDown(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Num, Byte Color)
{
 asm MOV AH,0x07;
 asm MOV AL,Num;
 asm MOV BH,Color;
 asm MOV CL,X1;
 asm MOV CH,Y1;
 asm MOV DL,X2;
 asm MOV DH,Y2;
 asm INT 0x10;
}