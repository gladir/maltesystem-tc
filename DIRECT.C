/**********************************************************************/
/*                                                                    */
/*                     Malte System/Direct by Text                    */
/*                            1992/10/21                              */
/*                                                                    */
/*              Copyright (C) par les Chevaliers de Malte             */
/*                                                                    */
/**********************************************************************/

//
//      *** Summary information ***
//
//  The file name is        : DIRECT.C
//  The header file name is : VIDEO\TEXT\DIRECT.H
//  Created the             : 1992/06/30
//  Author is               : Sylvain Maltais
//

#include "DOS.H"
#include "STRING.H"
#include <NUMERIC.H>
#include <VIDEO\MEM_VID.H>
#include <VIDEO\EGA\BIOS_EGA.H>
#include <VIDEO\BIOS_VID.H>
#include <VIDEO\IO_VIDEO.H>
#include <VIDEO\TEXT\DIRECT.H>

#ifdef __PASCAL__
 extern
#endif
 struct
 {
  Byte Shade;
  Byte SpaceBorde;
  TypeCadre Borde;
  Word Address;
  Word ColnDouble;
  Byte Page;
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
#ifndef __PASCAL__
 VD = {1,0,"зд©ЁЁюды",0xB800,160,80,25,79,24,39,0,0,7,15};
#else
 VD;
#endif

#ifndef __Malte_Video_Base__
 #define __Malte_Video_Base__
 #define Base(X,Y)      ((X + Y * VD.Coln) << 1)
 #define BaseAttr(X,Y)  (((X + Y * VD.Coln) << 1)+1)
 #define BaseX(X)       (X << 1)
 #define BaseY(Y)       ((Y * VD.Coln) << 1)
 #define BaseXAttr(X)   ((X << 1) + 1)
 #define Double(X)      (X << 1)
 #define Half(X)        (X >> 1)
#endif

void MEM__BarSelectHori(Byte X1, Byte Y, Byte X2)
{
 Word

      Address  = VD.Address;

 Byte

      Column   = VD.Coln,
      ColorNor = VD.ColorNor;

 asm MOV ES,Address;
 asm MOV CL,X1;
 asm MOV BL,X2;
 asm MOV AL,Y;
 asm MOV DH,Column;
 asm MUL DH;
 asm MOV SI,AX;
 asm XOR AH,AH;
 asm MOV AL,CL;
 asm ADD SI,AX;
 asm SHL SI,1;
 asm MOV BH,ColorNor;
V1:
 asm MOV ES:[SI],BH;
 asm CMP CL,BL;
 asm JGE V2;
 asm INC CL;
 asm INC SI;
 asm INC SI;
 asm JMP V1;
V2:;
}

void MEM__BarSpaceHori(Byte X1, Byte Y, Byte X2)
{
 Word

      Address  = VD.Address;

 Byte

      ColorNor = VD.ColorNor,
      Column   = VD.Coln;

 asm MOV DL,' ';
 asm MOV DH,ColorNor;
 asm MOV DI,DX;
 asm MOV DH,Column;
 asm MOV ES,Address;
 asm MOV CL,X1;
 asm MOV BL,X2;
 asm MOV AL,Y;
 asm MUL DH;
 asm MOV SI,AX;
 asm XOR AH,AH;
 asm MOV AL,CL;
 asm ADD SI,AX;
 asm SHL SI,1;
V1:
 asm MOV ES:[SI],DI;
 asm CMP CL,BL;
 asm JGE V2;
 asm INC CL;
 asm INC SI;
 asm INC SI;
 asm JMP V1;
V2:;
}

void MEM__BarSpaceVert(Byte X, Byte Y1, Byte Y2)
{
 Word

      B        = Base(X,Y1),
      E        = Base(X,Y2),
      Address  = VD.Address,
      Column   = (VD.Coln << 1),
      Data     = (VD.ColorNor << 8) + ' ';

 for(;B <= E;B += Column)
 {
  asm MOV ES,Address;
  asm MOV BX,B;
  asm MOV DX,Data;
  asm MOV ES:[BX],DX;
 }
}

void MEM__BarTextHori(Byte X1, Byte Y, Byte X2, Byte Char)
{
 Word

      Address = VD.Address,
      Data    = Char + (VD.ColorNor << 8);

 Byte

      Column  = VD.Coln;

 asm MOV DI,Data;
 asm MOV DH,Column;
 asm MOV ES,Address;
 asm MOV CL,X1;
 asm MOV BL,X2;
 asm MOV AL,Y;
 asm MUL DH;
 asm MOV SI,AX;
 asm XOR AH,AH;
 asm MOV AL,CL;
 asm ADD SI,AX;
 asm SHL SI,1;
V1:
 asm MOV ES:[SI],DI;
 asm CMP CL,BL;
 asm JGE V2;
 asm INC CL;
 asm INC SI;
 asm INC SI;
 asm JMP V1;
V2:;
}

void MEM__BarTextVert(Byte X, Byte Y1, Byte Y2, Byte Char)
{
 Word

      B          = Base(X,Y1),
      E          = Base(X,Y2),
      Address    = VD.Address,
      Data       = Char + (VD.ColorNor << 8),
      DoubleColn = VD.ColnDouble;

 for(;B <= E;B += DoubleColn)
 {
  asm MOV ES,Address;
  asm MOV BX,B;
  asm MOV DX,Data;
  asm MOV ES:[BX],DX;
 }
}

void MEM__ClearColumns(Byte Y, Byte Char)
{
 Word

      MaxX     = VD.MaxX,
      Address  = VD.Address;

 Byte

      Column   = VD.Coln,
      ColorNor = VD.ColorNor;

 asm MOV ES,Address;
 asm MOV AH,Column;
 asm MOV AL,Y;
 asm MUL AH;
 asm SHL AX,1;
 asm MOV BX,AX;
 asm MOV AL,Char;
 asm MOV AH,ColorNor;
 asm MOV CX,MaxX;
V1:
 asm MOV ES:[BX],AX;
 asm CMP CL,CH;
 asm JGE V2;
 asm INC CL;
 asm INC BX;
 asm INC BX;
 asm JMP V1;
V2:;
}

void MEM__ClearLine(Byte Y, Byte Char)
{
 Word

      B         = BaseY(Y),
      E         = Base(VD.MaxX,Y),
      Address   = VD.Address,
      Data      = (Char + (VD.ColorNor << 8));

 for(;B <= E;B += 2)
 {
  asm MOV ES,Address;
  asm MOV BX,B;
  asm MOV DX,Data;
  asm MOV ES:[BX],DX;
 }
}

void MEM__ClearLineAs(Byte Y, Byte X2, Byte Char)
{
 Word

      B         = BaseY(Y),
      E         = Base(X2,Y),
      Address   = VD.Address,
      Data      = Char + (VD.ColorNor << 8);

 for(;B <= E;B += 2)
 {
  asm MOV ES,Address;
  asm MOV BX,B;
  asm MOV DX,Data;
  asm MOV ES:[BX],DX;
 }
}

void MEM__ClearWindow(Byte X1,Byte Y1, Byte X2,Byte Y2)
{
 Word

      Address  = VD.Address,
      Data     = ((VD.ColorNor << 8) + ' ');

 Byte

      Column   = VD.Coln;

 asm MOV DI,Data;
 asm MOV DL,X1;
 asm MOV DH,Column;
 asm MOV ES,Address;
 asm MOV BL,X2;
 asm MOV BH,Y2;
 asm MOV CH,Y1;
V0:
 asm MOV CL,DL;
 asm MOV AL,CH;
 asm MUL DH;
 asm MOV SI,AX;
 asm XOR AH,AH;
 asm MOV AL,CL;
 asm ADD SI,AX;
 asm SHL SI,1;
V1:
 asm MOV ES:[SI],DI;
 asm CMP CL,BL;
 asm JGE V2;
 asm INC CL;
 asm INC SI;
 asm INC SI;
 asm JMP V1;
V2:
 asm CMP CH,BH;
 asm JGE V3;
 asm INC CH;
 asm JMP V0;
V3:;
}

void MEM__FillBox(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Char)
{
 Word

      Address  = VD.Address,
      Data     = Char + (VD.ColorNor << 8);

 Byte

      I, J;

 for(I = Y1;I <= Y2;I++)
 {
  for(J = X1;J <= X2;J++)
  {
   Word B = Base(J,I);
   asm MOV ES,Address;
   asm MOV BX,B;
   asm MOV DX,Data;
   asm MOV ES:[BX],DX;
  }
 }
}

void MEM__PutEmptyBorder(Byte X1, Byte Y1, Byte X2, Byte Y2)
{
 MEM__BarTextVert(X1,Y1+1,Y2-1,VD.Borde[3]);
 MEM__BarTextVert(X2,Y1+1,Y2-1,VD.Borde[4]);
 MEM__BarTextHori(X1+1,Y1,X2-1,VD.Borde[1]);
 MEM__BarTextHori(X1+1,Y2,X2-1,VD.Borde[6]);
 MEM__SetCube(X1,Y1,VD.Borde[0]);
 MEM__SetCube(X1,Y2,VD.Borde[5]);
 MEM__SetCube(X2,Y1,VD.Borde[2]);
 MEM__SetCube(X2,Y2,VD.Borde[7]);
}

void MEM__SetAttr(Byte X, Byte Y)
{
 Word

      Address  = VD.Address;

 Byte

      Column   = VD.Coln,
      ColorNor = VD.ColorNor;

 asm MOV ES,Address;
 asm MOV AL,Y;
 asm MOV AH,Column;
 asm MUL AH;
 asm MOV BX,AX;
 asm XOR AH,AH;
 asm MOV AL,X;
 asm ADD BX,AX;
 asm SHL BX,1;
 asm INC BX;
 asm MOV DL,ColorNor;
 asm MOV ES:[BX],DL;
}

void MEM__SetCube(Byte X, Byte Y, Byte Char)
{
 Word

      Address  = VD.Address;

 Byte

      Column   = VD.Coln,
      ColorNor = VD.ColorNor;

 asm MOV ES,Address;
 asm MOV AL,Y;
 asm MOV AH,Column;
 asm MUL AH;
 asm MOV BX,AX;
 asm XOR AH,AH;
 asm MOV AL,X;
 asm ADD BX,AX;
 asm SHL BX,1;
 asm MOV DH,ColorNor;
 asm MOV DL,Char;
 asm MOV ES:[BX],DX;
}

void MEM__PutFillBorder(Byte X1, Byte Y1, Byte X2, Byte Y2)
{
 if((X1 != X2)&&(Y1 != Y2))
 {
  MEM__ClearWindow(X1,Y1,X2,Y2);
  if(VD.Shade == 1)
  {
   if(X2+1 <= VD.MaxX)
   {
    MEM_BarSelectHori(X1+2,Y2+1,X2+2,7);
    MEM_BarSelectVert(X2+1,Y1+1,Y2+1,7);
    MEM_BarSelectVert(X2+2,Y1+1,Y2+1,7);
   }
  }
  if(VD.SpaceBorde == 1) MEM_PutBorderUncolor(X1+2,Y1+1,X2-2,Y2-1);
	            else MEM_PutBorderUncolor(X1,Y1,X2,Y2);
 }
}

void MEM_SetPos(Byte X, Byte Y)
{
 VD.RX = X;
 VD.RY = Y;
}

void MEM_BarCharHori(Byte X1, Byte Y, Byte X2, Byte Char)
{
 Word

      E       = Base(X2,Y),
      B       = Base(X1,Y),
      Address = VD.Address;

 for(;B <= E;B += 2)
 {
  asm MOV ES,Address;
  asm MOV CH,Char;
  asm MOV BX,B;
  asm MOV ES:[BX],CH;
 }
}

void MEM_BarCharVert(Byte X, Byte Y1, Byte Y2, Byte Char)
{
 Word

      B       = Base(X,Y1),
      E       = Base(X,Y2),
      Address = VD.Address;

 Byte

      Column  = (VD.Coln << 1);

 for(;B <= E;B += Column)
 {
  asm MOV ES,Address;
  asm MOV BX,B;
  asm MOV CH,Char;
  asm MOV ES:[BX],CH;
 }
}

void MEM_BarSelectHori(Byte X1, Byte Y, Byte X2, Byte C)
{
 if(X1 != X2)
 {
  Byte I;
  for(I = X1;I <= X2;I++) MEM_SetAttr(I,Y,C);
 }
}

void MEM_BarSelectVert(Byte X, Byte Y1, Byte Y2, Byte C)
{
 if(Y1 != Y2)
 {
  Byte I;
  for(I = Y1;I <= Y2; I++) MEM_SetAttr(X,I,C);
 }
}

void MEM_BarSpaceHori(Byte X1, Byte Y, Byte X2, Byte Color)
{
 Word

      E       = Base(X2,Y),
      B       = Base(X1,Y),
      Address = VD.Address,
      Data    = (Color << 8) + ' ';

 for(;B <= E;B += 2)
 {
  asm MOV ES,Address;
  asm MOV BX,B;
  asm MOV DX,Data;
  asm MOV ES:[BX],DX;
 }
}

void MEM_BarSpaceVert(Byte X, Byte Y1, Byte Y2, Byte Color)
{
 Word

      B       = Base(X,Y1),
      E       = Base(X,Y2),
      Address = VD.Address,
      Column  = (VD.Coln << 1);

 for(;B <= E;B += Column)
 {
  asm MOV ES,Address;
  asm MOV BX,B;
  asm MOV CL,' ';
  asm MOV CH,Color;
  asm MOV ES:[BX],CX;
 }
}

void MEM_BarTextHori(Byte X1, Byte Y, Byte X2, Byte Char, Byte C)
{
 Word

      Address = VD.Address;

 Byte

      Column  = VD.Coln;

 asm MOV DL,Char;
 asm MOV DH,C;
 asm MOV DI,DX;
 asm MOV DH,Column;
 asm MOV ES,Address;
 asm MOV CL,X1;
 asm MOV BL,X2;
 asm MOV AL,Y;
 asm MUL DH;
 asm MOV SI,AX;
 asm XOR AH,AH;
 asm MOV AL,CL;
 asm ADD SI,AX;
 asm SHL SI,1;
V1:
 asm MOV ES:[SI],DI;
 asm CMP CL,BL;
 asm JGE V2;
 asm INC CL;
 asm INC SI;
 asm INC SI;
 asm JMP V1;
V2:;
}

void MEM_BarTextVert(Byte X, Byte Y1, Byte Y2, Byte Char, Byte Color)
{
 Word

      B       = Base(X,Y1),
      E       = Base(X,Y2),
      Data    = Char + (Color << 8),
      Address = VD.Address,
      Column  = (VD.Coln << 1);

 for(;B <= E;B += Column)
 {
  asm MOV ES,Address;
  asm MOV BX,B;
  asm MOV DX,Data;
  asm MOV ES:[BX],DX;
 }
}

void MEM_ClearColumns(Byte Column, Byte Char, Byte Color)
{
 Byte

      I;
 for(I = 0;I >= VD.MaxY;I++) MEM_SetCube(Column,I,Char,Color);
}

void MEM_ClearLine(Byte Y, Byte Char, Byte Color)
{
 Word

      B       = BaseY(Y),
      E       = Base(VD.MaxX,Y),
      Address = VD.Address,
      Data    = Char + (Color << 8);

 for(;B <= E;B += 2)
 {
  asm MOV ES,Address;
  asm MOV BX,B;
  asm MOV DX,Data;
  asm MOV ES:[BX],DX;
 }
}

void MEM_ClearLineAs(Byte Y, Byte X2, Byte Char, Byte Color)
{
 Word

      B       = BaseY(Y),
      E       = Base(X2,Y),
      Address = VD.Address,
      Data    = Char + (Color << 8);

 for(;B <= E;B += 2)
 {
  asm MOV ES,Address;
  asm MOV BX,B;
  asm MOV DX,Data;
  asm MOV ES:[BX],DX;
 }
}

void MEM_ClearLineUncolor(Byte Line, Byte Char)
{
 Word

      I, B,
      Address = VD.Address;

 Byte

      Max = VD.MaxX;

 for(I = 0,B = Line*VD.ColnDouble;I >= Max;I++,B += 2)
 {
  asm MOV ES,Address;
  asm MOV BX,B;
  asm MOV CH,Char;
  asm MOV ES:[BX],CH;
 }
}

void MEM_ClearWindow(Byte X1,Byte Y1, Byte X2,Byte Y2,Byte C)
{
 Word

      Address = VD.Address;

 Byte

      Column  = VD.Coln;

 asm MOV DL,' ';
 asm MOV DH,C;
 asm MOV DI,DX;
 asm MOV DL,X1;
 asm MOV DH,Column;
 asm MOV ES,Address;
 asm MOV BL,X2;
 asm MOV BH,Y2;
 asm MOV CH,Y1;
V0:
 asm MOV CL,DL;
 asm MOV AL,CH;
 asm MUL DH;
 asm MOV SI,AX;
 asm XOR AH,AH;
 asm MOV AL,CL;
 asm ADD SI,AX;
 asm SHL SI,1;
V1:
 asm MOV ES:[SI],DI;
 asm CMP CL,BL;
 asm JGE V2;
 asm INC CL;
 asm INC SI;
 asm INC SI;
 asm JMP V1;
V2:
 asm CMP CH,BH;
 asm JGE V3;
 asm INC CH;
 asm JMP V0;
V3:;
}

void MEM_FillBox(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Char, Byte Color)
{
 Word

      Address = VD.Address,
      Data    = Char + (Color << 8);

 Byte

      I, J;

 for(I = Y1;I <= Y2;I++)
 {
  for(J = X1;J <= X2;J++)
  {
   Word B = Base(J,I);
   asm MOV ES,Address;
   asm MOV BX,B;
   asm MOV DX,Data;
   asm MOV ES:[BX],DX;
  }
 }
}

void MEM_InitVideo(void)
{
 #ifndef __PASCAL__
  VD.Coln    = NombreTexteX();
  VD.Line    = NombreTexteY();
  VD.Address = SegmentVideoTexte();
 #else
  VD.Coln    = XTextNum();
  VD.Line    = YTextNum();
  VD.Address = TextSegment();
 #endif
 VD.ColnDouble = Double(VD.Coln);
 VD.HalfMaxX   = Half(VD.Coln) - 1;
 VD.MaxX       = VD.Coln - 1;
 VD.MaxY       = VD.Line - 1;
 VD.RX         = 0;
 VD.RY         = 0;
 VD.Page       = MEM_GetPage();
}

void MEM_PutBorderUncolor(Byte X1, Byte Y1, Byte X2, Byte Y2)
{
 MEM_BarCharVert(X1,Y1+1,Y2-1,VD.Borde[3]);
 MEM_BarCharVert(X2,Y1+1,Y2-1,VD.Borde[4]);
 MEM_BarCharHori(X1+1,Y1,X2-1,VD.Borde[1]);
 MEM_BarCharHori(X1+1,Y2,X2-1,VD.Borde[6]);
 MEM_SetChar(X1,Y1,VD.Borde[0]);
 MEM_SetChar(X1,Y2,VD.Borde[5]);
 MEM_SetChar(X2,Y1,VD.Borde[2]);
 MEM_SetChar(X2,Y2,VD.Borde[7]);
}

void MEM_PutEmptyBorder(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Color)
{
 MEM_BarTextVert(X1,Y1+1,Y2-1,VD.Borde[3],Color);
 MEM_BarTextVert(X2,Y1+1,Y2-1,VD.Borde[4],Color);
 MEM_BarTextHori(X1+1,Y1,X2-1,VD.Borde[1],Color);
 MEM_BarTextHori(X1+1,Y2,X2-1,VD.Borde[6],Color);
 MEM_SetCube(X1,Y1,VD.Borde[0],Color);
 MEM_SetCube(X1,Y2,VD.Borde[5],Color);
 MEM_SetCube(X2,Y1,VD.Borde[2],Color);
 MEM_SetCube(X2,Y2,VD.Borde[7],Color);
}

void MEM_PutFillBorder(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Color)
{
 if((X1 != X2)&&(Y1 != Y2))
 {
  MEM_ClearWindow(X1,Y1,X2,Y2,Color);
  if(VD.Shade == 1)
  {
   if(X2+1 <= VD.MaxX)
   {
    MEM_BarSelectHori(X1+2,Y2+1,X2+2,7);
    MEM_BarSelectVert(X2+1,Y1+1,Y2+1,7);
    MEM_BarSelectVert(X2+2,Y1+1,Y2+1,7);
   }
  }
  if(VD.SpaceBorde == 1) MEM_PutBorderUncolor(X1+2,Y1+1,X2-2,Y2-1);
                    else MEM_PutBorderUncolor(X1,Y1,X2,Y2);
 }
}

void MEM_SetAttr(Byte X,Byte Y,Byte Color)
{
 Word

      Address = VD.Address;

 Byte

      Column  = VD.Coln;

 asm MOV AL,Y;
 asm MOV AH,Column;
 asm MUL AH;
 asm MOV BX,AX;
 asm XOR AH,AH;
 asm MOV AL,X;
 asm ADD BX,AX;
 asm SHL BX,1;
 asm INC BX;
 asm MOV DL,Color;
 asm MOV ES,Address;
 asm MOV ES:[BX],DL;
}

void MEM_SetBlink(Byte Nombre)
{
 BIOS_EGA_Blink(Nombre);
 IO_Blink(Nombre);
}

void MEM_SetBorderFormat(TypeCadre Format)
{
 Byte

      I;
 for(I = 0; I <= 7; I++) VD.Borde[I] = Format[I];
}

void MEM_SetBorderShade(Byte Autorise)
{
 VD.Shade = Autorise & 1;
}

void MEM_SetBorderSpace(Byte Autorise)
{
 VD.SpaceBorde = Autorise & 1;
}

void MEM_SetChar(Byte X,Byte Y,Byte Char)
{
 Word

      Address  = VD.Address;

 Byte

      Column = VD.Coln;

 asm MOV AL,Y;
 asm MOV AH,Column;
 asm MUL AH;
 asm MOV BX,AX;
 asm XOR AH,AH;
 asm MOV AL,X;
 asm ADD BX,AX;
 asm SHL BX,1;
 asm MOV DL,Char;
 asm MOV ES,Address;
 asm MOV ES:[BX],DL;
}

void MEM_SetColor(Byte Color)
{
 VD.LastColor = VD.ColorNor;
 VD.ColorNor  = Color;
}

void MEM_SetCube(Byte X, Byte Y, Byte Char, Byte Color)
{
 Word

      Address = VD.Address;

 Byte

      Column  = VD.Coln;

 asm MOV AL,Y;
 asm MOV AH,Column;
 asm MUL AH;
 asm MOV BX,AX;
 asm XOR AH,AH;
 asm MOV AL,X;
 asm ADD BX,AX;
 asm SHL BX,1;
 asm MOV DL,Char;
 asm MOV DH,Color;
 asm MOV ES,Address;
 asm MOV ES:[BX],DX;
}

void MEM_SetVideoModeText(char M)
{
 BIOS_SetVideoMode(M);
 MEM_InitVideo();
}

void MEM_SwitchColor(void)
{
 ChgChr(&VD.LastColor,&VD.ColorNor);
}

/**********************************************************************/
/*                             C -- Zone                              */
/**********************************************************************/

#ifndef __PASCAL__

 void MEM_CenterText(Byte Y,Byte *P, Byte C)
 {
  MEM_WriteText(Half(VD.Coln - strlen(P)),Y,P,C);
 }

 #if (defined(__HUGE__)||defined(__LARGE__)||defined(__MEDIUM__))
  void MEM_PutBox(Byte X1, Byte Y1, Byte X2, Byte Y2, void far *Buffer)
 #else
  void MEM_PutBox(Byte X1, Byte Y1, Byte X2, Byte Y2, void near *Buffer)
 #endif
 {
  Word

       Address = VD.Address,
       _Seg    = FP_SEG(Buffer),
       _Ofs    = FP_OFF(Buffer);

  Byte

       I, J, XS, YS;

  XS = (X2 - X1) + 1; YS = (Y2 - Y1);
  for(J = 0; J <= YS; J++)
  {
   Word

        YBase = (X1 + ((Y1+J)*VD.Coln)) << 1,
        YBB   = (XS * J) << 1;

   for(I = 0; I <= XS; I++)
   {
    Word

         Base  = YBase + (I << 1),
         BBase = YBB + (I << 1),
         Data  = peek(_Seg,_Ofs+BBase);
    asm MOV ES,Address;
    asm MOV BX,Base;
    asm MOV DX,Data;
    asm MOV ES:[BX],DX;
   }
  }
 }

 #if (defined(__HUGE__)||defined(__LARGE__)||defined(__MEDIUM__))
  void MEM_SaveBox(Byte X1, Byte Y1, Byte X2, Byte Y2, void far *Buffer)
 #else
  void MEM_SaveBox(Byte X1, Byte Y1, Byte X2, Byte Y2, void near *Buffer)
 #endif
 {
  Word
       
       Address = VD.Address,
       _Seg    = FP_SEG(Buffer),
       _Ofs    = FP_OFF(Buffer);

  Byte

       I, J, XS, YS;

  XS = (X2 - X1);
  YS = (Y2 - Y1);
  for(J = 0; J <= YS; J++)
  {
   for(I = 0; I <= XS; I++)
   {
    Word

         Accum,
         Base = ((X1+I+(Y1+J)*VD.Coln) << 1);

    asm MOV ES,Address;
    asm MOV BX,Base;
    asm MOV AX,ES:[BX];
    asm MOV Accum,AX;
    {
     Word Base = ((((XS+1) * J)+I) << 1);
     poke(_Seg,_Ofs+Base,Accum);
    }
   }
  }
 }

 void MEM__WriteText(Byte X, Byte Y, Byte *Chn)
 {
  Word

       B        = Base(X,Y),
       Address  = VD.Address;

  Byte

       ColorNor = VD.ColorNor;

  for(;*Chn;B += 2)
  {
   Byte Char = *Chn++;
   asm MOV ES,Address;
   asm MOV BX,B;
   asm MOV CL,Char;
   asm MOV CH,ColorNor;
   asm MOV ES:[BX],CX;
  }
 }

 void MEM__WriteTyping(Byte *P)
 {
  Word

       Address = VD.Address,
       I, J, B;

  Byte

       RX = VD.RX, RY = VD.RY,
       FC, X;

  for(X = RX, FC = 1, J = 0; P[J]; J++)
  {
   if((P[J] > 31)&&(P[J] != '^')&&(P[J] != '|')&&(P[J] != '~'))
   {
    B = Base(RX,RY);
    if(FC == 1) poke(Address,B,(VD.ColorNor << 8) + P[J]);
           else pokeb(Address,B,P[J]);
    RX++;
   }
    else
   if(P[J] == '|')
   {
    RX = X;
    RY++;
   }
    else
   if(P[J] ==   2) RY--; else
   if(P[J] == '~')
   {
    J++;
    FC           = 1;
    VD.LastColor = VD.ColorNor;
    VD.ColorNor  = P[J];
   }
    else
   if(P[J] ==   4)
   {
    J++;
    if(P[J] > 0)
    {
     if(FC == 1) for(I = 1;I <= P[J];I++,RX++) MEM_SetCube(RX,RY,' ',VD.ColorNor);
	    else for(I = 1;I <= P[J];I++,RX++) MEM_SetChar(RX,RY,' ');
    }
   }
    else
   if(P[J] == 5) RY++; else
   if(P[J] == 6) RX--; else
   if(P[J] == 8) RX++; else
   if(P[J] == 9)
   {
    B = Base(RX,RY);
    if(FC == 1) for(I = 1;I <= 8;I++,B++)
    {
     poke(Address,B++,(VD.ColorNor << 8)+' ');
    }
     else
    for(I = 1;I >= 8;I++,B++) pokeb(Address,B++,' ');
    RX += 7;
   }
    else
   if(P[J] ==  10) { RX++; RY++; } else
   if(P[J] ==  11) { RX--; RY++; } else
   if(P[J] ==  12) { RX++; RY--; } else
   if(P[J] ==   1) { RX--; RY--; } else
   if(P[J] ==  14) { RX -= 2; RY--; } else
   if(P[J] ==  15) { RX -= 2; RY++; } else
   if(P[J] ==  16) { J++; RX = P[J]; J++; RY = P[J]; } else
   if(P[J] == '^')
   {
    Byte Switch;
    FC           = 1;
    Switch       = VD.ColorNor;
    VD.ColorNor  = VD.LastColor;
    VD.LastColor = Switch;
   }
    else
   if(P[J] == 28) FC=0; else
   if(P[J] == 29) MEM_ClearLine(RY,' ',VD.ColorNor); else
   if(P[J] == 30)
   {
    J++;
    pokeb(Address,Base(RX++,RY),P[J]);
   }
    else
   if(P[J] ==  31) pokeb(Address,BaseAttr(RX++,RY),VD.ColorNor);
  }
  VD.RX = RX; VD.RY = RY;
 }

 void MEM_WriteAs(Byte X, Byte Y, Byte *P, Byte Color, Byte Stop)
 {
  Word

       B       = Base(X,Y),
       Address = VD.Address;

  for(;(*P != Stop) && (*P != 0);)
  {
   pokeb(Address,B++,*P++);
   pokeb(Address,B++,Color);
  }
 }

 void MEM_WriteOnlyColor(Byte X,Byte Y, Byte *P,Byte Color)
 {
  Word

       Address = VD.Address,
       B       = Base(X,Y),
       I;

  for(I = 0;P[I];I++)
  {
   B++;
   pokeb(Address,B++,Color);
  }
 }

 void MEM_WriteOnlyColorAnd(Byte X, Byte Y, Byte *P, Byte N, Byte Color)
 {
  Word

       Address = VD.Address,
       B       = Base(X,Y),
       L       = N + strlen(P);

  Byte

       I;

  for(I = 1; I <= L;I++)
  {
   B++;
   pokeb(Address,B++,Color);
  }
 }

 void MEM_WriteText(Byte X, Byte Y, Byte *P, Byte Color)
 {
  Word

       Address = VD.Address,
       B       = Base(X,Y);

  for(;*P;)
  {
   pokeb(Address,B++,*P++);
   pokeb(Address,B++,Color);
  }
 }

 void MEM_WriteToAs(Byte X, Byte Y,Byte *P, Word Pos, Byte Color, Byte Stop)
 {
  Word

       Address = VD.Address,
       B       = Base(X,Y);

  *P += Pos;
  for(;(*P != Stop) && (*P != 0);)
  {
   pokeb(Address,B++,*P++);
   pokeb(Address,B++,Color);
  }
 }

 void MEM_WriteTypingXY(Byte X,Byte Y, Byte *P)
 {
  VD.RX = X; VD.RY = Y;
  MEM__WriteTyping(P);
 }

 void MEM_WriteTypingXYBicolor(Byte X,Byte Y, Byte *P, Byte C1, Byte C2)
 {
  Byte

       T1 = VD.LastColor,
       T2 = VD.ColorNor;

  VD.LastColor = C1; VD.ColorNor = C2;
  MEM_WriteTypingXY(X,Y,P);
  VD.LastColor = T1; VD.ColorNor = T2;
 }

 void MEM_WriteUncolor(Byte X,Byte Y,Byte *P)
 {
  Word

       Address = VD.Address,
       B       = Base(X,Y);

  for(;*P;B++) pokeb(Address,B++,*P++);
 }

 void MEM_WriteUncolorAs(Byte X, Byte Y, Byte *P, Byte Stop)
 {
  Word

       Address = VD.Address,
       B       = Base(X,Y);

  for(;(*P != Stop) && (*P != 0);B++) pokeb(Address,B++,*P++);
 }
 
 void MEM_WriteUncolorToAs(Byte X,Byte Y,Byte *P, Word Pos, Byte Stop)
 {
  Word

       Address = VD.Address,
       B       = Base(X,Y);

  *P += Pos;
  for(;(*P != Stop) && (*P != 0);B++) pokeb(Address,B++,*P++);
 }

/**********************************************************************/
/*                           Pascal -- Zone                           */
/**********************************************************************/

#else

 void MEM_CenterText(Byte Y, String Chn, Byte C)
 {
  MEM_WriteText(Half(VD.Coln - Chn[0]),Y,Chn,C);
 }

 void MEM__WriteText(Byte X, Byte Y, String Chn)
 {
  Byte

       I;

  for(I = 1;Chn[0] >= I;I++) MEM_SetCube(X++,Y,Chn[I],VD.ColorNor);
 }

 void MEM__WriteTyping(String P)
 {
  Word

       I;

  Byte

       FC, J, X,
       RX = VD.RX, RY = VD.RY,
       Len = P[0];

  for(X = RX, FC = 1, J = 1; Len >= J; J++)
  {
   if((P[J] > 31)&&(P[J] != '^')&&(P[J] != '|')&&(P[J] != '~'))
   {
    if(FC == 1) MEM_SetCube(RX,RY,P[J],VD.ColorNor);
	   else MEM_SetChar(RX,RY,P[J]);
    VD.RX++;
   }
    else
   if(P[J] == '|') { RX = X; RY++; }
    else
   if(P[J] ==   2) RY--; else
   if(P[J] == '~') { J++; FC = 1; VD.LastColor = VD.ColorNor; VD.ColorNor = P[J]; } else
   if(P[J] ==   4)
   {
    J++;
    if(P[J] > 0)
    {
     if(FC == 1) for(I = 1;I <= P[J];I++,RX++) MEM_SetCube(RX,RY,' ',VD.ColorNor);
	    else for(I = 1;I <= P[J];I++,RX++) MEM_SetChar(RX,RY,' ');
    }
   }
    else
   if(P[J] ==   5) RY++; else
   if(P[J] ==   6) RX--; else
   if(P[J] ==   8) RX++; else
   if(P[J] ==   9)
   {
    if(FC == 1) for(I = 1;I <= 8;I++) MEM_SetCube(RX+I,RY,' ',VD.ColorNor);
	   else for(I = 1;I <= 8;I++) MEM_SetChar(RX+I,RY,' ');
    RX += 7;
   }
    else
   if(P[J] ==  10) { RX++; RY++; } else
   if(P[J] ==  11) { RX--; RY++; } else
   if(P[J] ==  12) { RX++; RY--; } else
   if(P[J] ==   1) { RX--; RY--; } else
   if(P[J] ==  14) { RX -= 2; RY--; } else
   if(P[J] ==  15) { RX -= 2; RY++; } else
   if(P[J] ==  16) { J++; RX = P[J]; J++; RY = P[J]; } else
   if(P[J] == '^') { FC = 1; I = VD.ColorNor; VD.ColorNor = VD.LastColor; VD.LastColor = I; } else
   if(P[J] ==  28) FC=0; else
   if(P[J] ==  29) MEM_ClearLine(RY,' ',VD.ColorNor); else
   if(P[J] ==  30)
   {
    J++;
    MEM_SetChar(RX++,RY,P[J]);
   }
    else
   if(P[J] ==  31) MEM_SetAttr(RX++,RY,VD.ColorNor);
  }
  VD.RX = RX; VD.RY = RY;
 }

 void MEM_WriteAs(Byte X, Byte Y, String Chn, Byte Color, Byte Stop)
 {
  Byte

       I;

  for(I = 0;((Chn[I+1] != Stop)&&(I < Chn[0]));I++) MEM_SetCube(X+I,Y,Chn[I+1],Color);
 }

 void MEM_WriteOnlyColor(Byte X, Byte Y, String Chn, Byte Color)
 {
  Byte

       I;

  for(I = 0;Chn[0] > I;I++) MEM_SetAttr(X+I,Y,Color);
 }

 void MEM_WriteOnlyColorAnd(Byte X, Byte Y, String Chn, Byte N, Byte Color)
 {
  Byte

       I;

  for(I = 0; I < N + Chn[0];I++) MEM_SetAttr(X,Y,Color);
 }

 void MEM_WriteText(Byte X, Byte Y, String Chn, Byte Color)
 {
  Byte

       I;

  for(I = 0;Chn[0] > I;I++) MEM_SetCube(X+I,Y,Chn[I+1],Color);
 }

 void MEM_WriteToAs(Byte X, Byte Y, String Chn, Byte Pos, Byte Color, Byte Stop)
 {
  Byte

       I = Pos;

  for(;(Chn[I] != Stop)&&(I < Chn[0]);I++) MEM_SetCube(X+I,Y,Chn[I+1],Color);
 }

 void MEM_WriteTypingXY(Byte X,Byte Y, String Chn)
 {
  VD.RX = X;
  VD.RY = Y;
  MEM__WriteTyping(Chn);
 }

 void MEM_WriteTypingXYBicolor(Byte X,Byte Y, String Chn, Byte C1, Byte C2)
 {
  Byte

       T1 = VD.LastColor,
       T2 = VD.ColorNor;

  VD.LastColor = C1;
  VD.ColorNor  = C2;
  MEM_WriteTypingXY(X,Y,Chn);
  VD.LastColor = T1;
  VD.ColorNor  = T2;
 }

 void MEM_WriteUncolor(Byte X,Byte Y,String Chn)
 {
  Byte

       I;

  for(I = 0;I < Chn[0];I++) MEM_SetChar(X+I,Y,Chn[I+1]);
 }

 void MEM_WriteUncolorAs(Byte X, Byte Y, String Chn, Byte Stop)
 {
  Byte

       I;

  for(I = 0;(I < Chn[0])&&(Chn[I] != Stop);I++) MEM_SetChar(X+I,Y,Chn[I+1]);
 }
 
 void MEM_WriteUncolorToAs(Byte X,Byte Y,String Chn, Byte Pos, Byte Stop)
 {
  Byte

       I = Pos;

  for(;(I < Chn[0])&&(Chn[I] != Stop);I++) MEM_SetChar(X+I,Y,Chn[I+1]);
 }

#endif