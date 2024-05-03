/******************************************************************/
/*                                                                */
/*                     Malte System/BIOS Text                     */
/*                          1992/06/30                            */
/*                                                                */
/*            Copyright (C) par les Chevaliers de Malte           */
/*                                                                */
/******************************************************************/

// Programmeur :
//
//  Sylvain Maltais
//
// DerniŠre modification :
//
//  Jeudi, le 13 mai 1993  (Adaptation de l'unit‚ au nouveau systŠme).
//                         (UpDate : WriteTyping).
//
// Directive de compilation conditionnel :
//
// __PASCAL__     Indique qu'il doit ˆtre compatible au Turbo Pascal.
//

// ********************************************************
//                     INTERFACE/HEADER
// ********************************************************

#include <NUMERIC.H>
#include <BIOSTEXT.H>

#ifdef __PASCAL__
 extern
#endif
 struct {
         Boolean   Shade;
         Boolean   SpaceBorde;
         TypeCadre Borde;
         Word      ColnDouble;
         Byte      Page;
         Byte      Coln,Line;
         Byte      MaxX,MaxY;
         Byte      HalfMaxX;
         Byte      RX,RY;
         Byte      ColorNor;
         Byte      LastColor;
        }
#ifndef __PASCAL__
 VB =  {
        True,
	False,
	"ÚÄ¿³³ÀÄÙ",
	160,
	80,25,
	79,24,
	39,
	0,0,
	7,
	15
       };
#else
 VB;
#endif

// ********************************************************
//                      IMPLEMENTATION
// ********************************************************

#include "STRING.H"

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BIOS_SetCube                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SetCube(Byte X, Byte Y, Byte Char, Byte Color)
{
 asm MOV AH,2;
 asm XOR BH,BH;
 asm MOV DL,X;
 asm MOV DH,Y;
 asm INT 0x10;
 asm MOV AH,9;
 asm MOV AL,Char;
 asm MOV BL,Color;
 asm MOV CX,1;
 asm INT 0x10;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    BIOS_SetBorderShade               ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SetBorderShade(Boolean X)
{
 VB.Shade = X & 1;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    BIOS_SetBorderSpace               ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SetBorderSpace(Boolean X)
{
 VB.SpaceBorde = X & 1;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      BIOS_SetColor                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SetColor(Byte Color)
{
 VB.LastColor = VB.ColorNor;
 VB.ColorNor  = Color;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BIOS_SwitchColor                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SwitchColor(void)
{
 ChgChr(&VB.LastColor,&VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      BIOS_SaveBox                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SaveBox(Byte X1,Byte Y1, Byte X2,Byte Y2, Byte *Buffer)
{
 Byte I,J,XS,YS;
 X2 = (X2 == EOL ? VB.MaxX : X2);
 XS = (X2 - X1); YS = (Y2 - Y1);
 for(J = 0; J <= YS; J++)
 {
  for(I = 0; I <= XS; I++)
  {
   Word B = ((((XS+1) * J) + I) << 1);
   Buffer[B]   = BIOS_GetChar(X1+I,Y1+J,0);
   Buffer[B+1] = BIOS_GetAttr(X1+I,Y1+J,0);
  }
 }
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       BIOS_PutBox                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_PutBox(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte *Buffer)
{
 Byte I,J,XS,YS;
 X2 = (X2 == EOL ? VB.MaxX : X2);
 XS = (X2 - X1); YS = (Y2 - Y1);
 for(J = 0; J <= YS; J++)
 {
  for(I = 0; I <= XS; I++)
  {
   Word B = ((((XS+1)*J)+I) << 1);
   BIOS_SetCube(X1+I,Y1+J,Buffer[B],Buffer[B+1]);
  }
 }
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       BIOS_SetAttr                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SetAttr(Byte X,Byte Y,Byte C)
{
 BIOS_SetCube(X,Y,BIOS_GetChar(X,Y,0),C);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      BIOS_SetAttr_                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SetAttr_(Byte X,Byte Y)
{
 BIOS_SetCube(X,Y,BIOS_GetChar(X,Y,0),VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BIOS_BarTextHori                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarTextHori(Byte X1, Byte Y, Byte X2, Byte Char, Byte Color)
{
 Byte MaxX = VB.MaxX;
 asm MOV AL,X1;
 asm MOV AH,X2;
 asm CMP AH,AL;
 asm JNL V1;
 asm XCHG AL,AH;
V1:
 asm CMP AH,0xFF;
 asm JNE V2;
 asm MOV AH,MaxX;
V2:
 asm XCHG AL,AH;
 asm SUB AL,AH;
 asm INC AL;
 asm XOR AH,AH;
 asm MOV CX,AX;
 asm MOV AH,2;
 asm XOR BH,BH;
 asm MOV DL,X1;
 asm MOV DH,Y;
 asm INT 0x10;
 asm MOV AH,9;
 asm MOV AL,Char;
 asm MOV BL,Color;
 asm INT 0x10;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    BIOS_BarTextHori_                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarTextHori_(Byte X1, Byte Y, Byte X2, Byte Char)
{
 BIOS_BarTextHori(X1,Y,X2,Char,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_BarSpaceHori                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarSpaceHori(Byte X1, Byte Y, Byte X2, Byte Color)
{
 BIOS_BarTextHori(X1,Y,X2,' ',Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_BarSpaceHori_                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarSpaceHori_(Byte X1, Byte Y, Byte X2)
{
 BIOS_BarTextHori(X1,Y,X2,32,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_BarCharHori                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarCharHori(Byte X1, Byte Y, Byte X2, Byte Char)
{
 Word X;
 X2 = (X2 == EOL ? VB.MaxX : X2);
 X = (X2 - X1) + 1;
 asm MOV AH,2;
 asm XOR BH,BH;
 asm MOV DL,X1;
 asm MOV DH,Y;
 asm INT 0x10;
 asm MOV AH,0xA;
 asm MOV AL,Char;
 asm MOV BL,15;
 asm MOV CX,X;
 asm INT 0x10;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_BarTextVert                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarTextVert(Byte X, Byte Y1, Byte Y2, Byte Char, Byte Color)
{
 Byte I;
 for(I = Y1;I <= Y2;I++) BIOS_SetCube(X,I,Char,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_BarTextVert_                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarTextVert_(Byte X, Byte Y1, Byte Y2, Byte Char)
{
 BIOS_BarTextVert(X,Y1,Y2,Char,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_BarSpaceVert                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarSpaceVert(Byte X, Byte Y1, Byte Y2, Byte Color)
{
 BIOS_BarTextVert(X,Y1,Y2,32,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                  BIOS_BarSpaceVert_                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarSpaceVert_(Byte X, Byte Y1, Byte Y2)
{
 BIOS_BarTextVert(X,Y1,Y2,32,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_BarCharVert                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarCharVert(Byte X, Byte Y1, Byte Y2, Byte Char)
{
 Byte I;
 for(I = Y1;I <= Y2;I++) BIOS_PutChar(X,I,0,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    BIOS_ClearLine                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_ClearLine(Byte Y, Byte Char, Byte Color)
{
 BIOS_ClearLineAs(Y,VB.MaxX,Char,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    BIOS_ClearLine_                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_ClearLine_(Byte Y, Byte Char)
{
 BIOS_ClearLine(Y,Char,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_ClearLineAs                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_ClearLineAs(Byte Y, Byte X2, Byte Char, Byte Color)
{
 asm MOV AH,2;
 asm XOR BH,BH;
 asm XOR DL,DL;
 asm MOV DH,Y;
 asm INT 0x10;
 asm MOV AH,9;
 asm MOV AL,Char;
 asm MOV BL,Color;
 asm MOV CL,X2;
 asm XOR CH,CH;
 asm INT 0x10;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_ClearLineAs_                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_ClearLineAs_(Byte Y, Byte X2, Byte Char)
{
 BIOS_ClearLineAs(Y,X2,Char,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_BarSelectHori                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarSelectHori(Byte X1, Byte Y, Byte X2, Byte Color)
{
 X2 = (X2 == EOL ? VB.MaxX : X2);
 if(X1 != X2)
 {
  Byte I;
  for(I = X1;I <= X2;I++) BIOS_SetAttr(I,Y,Color);
 }
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                  BIOS_BarSelectHori_                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarSelectHori_(Byte X1, Byte Y, Byte X2)
{
 BIOS_BarSelectHori(X1,Y,X2,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                  BIOS_BarSelectVert                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_BarSelectVert(Byte X, Byte Y1, Byte Y2, Byte Color)
{
 if(Y1 != Y2)
 {
  Byte I;
  for(I = Y1;I <= Y2; I++) BIOS_SetAttr(X,I,Color);
 }
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_ClearWindow                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_ClearWindow(Byte X1, Byte Y1, Byte X2,Byte Y2, Byte Color)
{
 X2 = (X2 == EOL ? VB.MaxX : X2);
 asm MOV AX,0x0600;
 asm MOV BH,Color;
 asm MOV CL,X1;
 asm MOV CH,Y1;
 asm MOV DL,X2;
 asm MOV DH,Y2;
 asm INT 0x10;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_ClearWindow_                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_ClearWindow_(Byte X1,Byte Y1, Byte X2,Byte Y2)
{
 BIOS_ClearWindow(X1,Y1,X2,Y2,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      BIOS_FillBox                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_FillBox(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Char, Byte Color)
{
 Byte I;
 for(I = Y1;I <= Y2;I++) BIOS_BarTextHori(X1,I,X2,Char,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BIOS_FillBox_                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_FillBox_(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Char)
{
 BIOS_FillBox(X1,Y1,X2,Y2,Char,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BIOS_SetChar                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SetChar(Byte X,Byte Y, Byte Char)
{
 BIOS_PutChar(X,Y,0,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BIOS_SetCube_                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SetCube_(Byte X, Byte Y, Byte Char)
{
 BIOS_SetCube(X,Y,Char,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    BIOS_WriteTypingXY                ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_WriteTypingXY(Byte X,Byte Y, Byte *P)
{
 VB.RX = X; VB.RY = Y;
 BIOS_WriteTyping_(P);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                  BIOS_WriteTypingXYBicolor           ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_WriteTypingXYBicolor(Byte X,Byte Y, Byte *P, Byte C1, Byte C2)
{
 Byte T1 = VB.LastColor, T2 = VB.ColorNor;
 VB.LastColor = C1;
 VB.ColorNor  = C2;
 BIOS_WriteTypingXY(X,Y,P);
 VB.LastColor = T1;
 VB.ColorNor  = T2;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                  BIOS_PutEmptyBorder                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_PutEmptyBorder(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Color)
{
 X2 = (X2 == EOL ? VB.MaxX : X2);
 BIOS_BarTextVert(X1,Y1+1,Y2-1,VB.Borde[3],Color);
 BIOS_BarTextVert(X2,Y1+1,Y2-1,VB.Borde[4],Color);
 BIOS_BarTextHori(X1+1,Y1,X2-1,VB.Borde[1],Color);
 BIOS_BarTextHori(X1+1,Y2,X2-1,VB.Borde[6],Color);
 BIOS_SetCube(X1,Y1,VB.Borde[0],Color);
 BIOS_SetCube(X1,Y2,VB.Borde[5],Color);
 BIOS_SetCube(X2,Y1,VB.Borde[2],Color);
 BIOS_SetCube(X2,Y2,VB.Borde[7],Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                  BIOS_PutEmptyBorder_                ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_PutEmptyBorder_(Byte X1, Byte Y1, Byte X2, Byte Y2)
{
 BIOS_PutEmptyBorder(X1,Y1,X2,Y2,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                 BIOS_PutBorderUncolor                ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_PutBorderUncolor(Byte X1, Byte Y1, Byte X2, Byte Y2)
{
 X2 = (X2 == EOL ? VB.MaxX : X2);
 BIOS_BarCharVert(X1,Y1+1,Y2-1,VB.Borde[3]);
 BIOS_BarCharVert(X2,Y1+1,Y2-1,VB.Borde[4]);
 BIOS_BarCharHori(X1+1,Y1,X2-1,VB.Borde[1]);
 BIOS_BarCharHori(X1+1,Y2,X2-1,VB.Borde[6]);
 BIOS_SetChar(X1,Y1,VB.Borde[0]);
 BIOS_SetChar(X1,Y2,VB.Borde[5]);
 BIOS_SetChar(X2,Y1,VB.Borde[2]);
 BIOS_SetChar(X2,Y2,VB.Borde[7]);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_PutFillBorder                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_PutFillBorder(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Color)
{
 if((X1 != X2)&&(Y1 != Y2))
 {
  X2 = (X2 == EOL ? VB.MaxX : X2);
  BIOS_ClearWindow(X1,Y1,X2,Y2,Color);
  if(VB.Shade)
  {
   if(X2+1 <= VB.MaxX)
   {
    BIOS_BarSelectHori(X1+2,Y2+1,X2+2,7);
    BIOS_BarSelectVert(X2+1,Y1+1,Y2+1,7);
    BIOS_BarSelectVert(X2+2,Y1+1,Y2+1,7);
   }
  }
  {
   Byte TX1,TY1,TX2,TY2;
   if(VB.SpaceBorde)
   {
    TX1 = X1+2;
    TY1 = Y1+1;
    TX2 = X2-2;
    TY2 = Y2-1;
   }
    else
   {
    TX1 = X1;
    TY1 = Y1;
    TX2 = X2;
    TY2 = Y2;
   }
   BIOS_PutBorderUncolor(TX1,TY1,TX2,TY2);
  }
 }
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_SetFillBorder_                ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SetFillBorder_(Byte X1, Byte Y1, Byte X2, Byte Y2)
{
 BIOS_PutFillBorder(X1,Y1,X2,Y2,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_ClearColumns                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_ClearColumns(Byte Column, Byte Char, Byte Color)
{
 Byte I;
 for(I = 0;I >= VB.MaxY;I++) BIOS_SetCube(Column,I,Char,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_ClearColumns_                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_ClearColumns_(Byte Column, Byte Char)
{
 BIOS_ClearColumns(Column,Char,VB.ColorNor);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                  BIOS_ClearLineUncolor               ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_ClearLineUncolor(Byte Y, Byte Char)
{
 Word MaxX = VB.MaxX;
 asm MOV DL,Y;
 asm XOR DH,DH;
 asm XOR BH,BH;
 asm MOV AH,2;
 asm INT 0x10;
 asm MOV AH,0xA;
 asm MOV AL,Char;
 asm MOV BL,15;
 asm MOV CX,MaxX;
 asm INT 0x10;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      BIOS_GetLine                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

Byte BIOS_GetLine(void)
{
 Byte Tmp = BIOS_VGA_PS2_Get_Line();
 return(Tmp == 0 ? 25 : Tmp);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BIOS_InitVideo                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_InitVideo(void)
{
 VB.Coln       = BIOS_GetColums();
 VB.Line       = BIOS_GetLine();
 VB.ColnDouble = VB.Coln << 1;
 VB.HalfMaxX   = (VB.Coln >> 1) - 1;
 VB.MaxX       = VB.Coln - 1;
 VB.MaxY       = VB.Line - 1;
 VB.RX         = 0;
 VB.RY         = 0;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BIOS_SetVideoMode_               ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SetVideoMode_(char Mode)
{
 BIOS_SetVideoMode(Mode);
 BIOS_InitVideo();
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_SetBorderFormat               ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BIOS_SetBorderFormat(TypeCadre Format)
{
 Byte I;
 for(I = 0; I <= 7; I++) VB.Borde[I] = Format[I];
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_WriteTyping_                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void BIOS_WriteTyping_(Byte *P)
 {
  Word J;
  Byte FC,X;
  for(X = VB.RX, FC = True, J = 0;P[J];J++)
  {
   if((P[J] > 31)&&(P[J] != '^')&&(P[J] != '|')&&(P[J] != '~'))
   {
    if(FC) BIOS_SetCube_(VB.RX,VB.RY,P[J]);
      else BIOS_SetChar(VB.RX,VB.RY,P[J]);
    VB.RX++;
   }
    else
   switch (P[J])
   {
    case '|' : VB.RX = X;
               VB.RY++;
               break;
    case   2 : VB.RY--;
               break;
    case '~' : J++;
               FC = True;
	       VB.LastColor = VB.ColorNor;
	       VB.ColorNor = P[J];
               break;
    case   4 : J++;
               if(P[J] > 0)
               {
                Word Data  = (VB.RY << 8) + VB.RX,
                     Count = P[J];
                Byte Base  = VB.ColorNor;
                asm MOV DX,Data;
                asm MOV AH,2;
                asm XOR BH,BH;
                asm INT 0x10;
                asm MOV AH,FC;
                asm ADD AH,9;
                asm MOV AL,' ';
                asm MOV BL,Base;
                asm MOV CX,Count;
                asm INT 0x10;
                VB.RX += P[J];
               }
               break;
    case   5 : VB.RY++;
               break;
    case   6 : VB.RX--;
               break;
    case   8 : VB.RX++;
               break;
    case   9 : {
                Word Data = (VB.RY << 8) + VB.RX;
                Byte Base = VB.ColorNor;
                asm MOV DX,Data;
                asm MOV AH,2;
                asm XOR BH,BH;
                asm INT 0x10;
                asm MOV AX,0x900 + ' ';
                asm ADD AH,FC;
                asm MOV BL,Base;
                asm MOV CX,8;
                asm INT 0x10;
                VB.RX += 7;
               }
               break;
    case  10 : VB.RX++;
               VB.RY++;
               break;
    case  11 : VB.RX--;
               VB.RY++;
               break;
    case  12 : VB.RX++;
               VB.RY--;
               break;
    case   1 : VB.RX--;
               VB.RY--;
               break;
    case  14 : VB.RX -= 2;
               VB.RY--;
               break;
    case  15 : VB.RX -= 2;
               VB.RY++;
               break;
    case  16 : J++;
               VB.RX = P[J++];
	       VB.RY = P[J];
               break;
    case '^' : {
                Byte Tmp     = VB.ColorNor;
                VB.ColorNor  = VB.LastColor;
                VB.LastColor = Tmp;
                FC           = True;
               }
               break;
    case  28 : FC = False;
               break;
    case  29 : BIOS_ClearLine_(VB.RY,32);
               break;
    case  30 : J++;
               BIOS_SetChar(VB.RX++,VB.RY,P[J]);
               break;
    case  31 : BIOS_SetAttr_(VB.RX++,VB.RY);
               break;
   }
  }
 }

#else

 void BIOS_WriteTyping_(String P)
 {
  Byte FC,X,J;
  for(X = VB.RX, FC = True, J = 1;P[0] >= J;J++)
  {
   if((P[J] > 31)&&(P[J] != '^')&&(P[J] != '|')&&(P[J] != '~'))
   {
    if(FC) BIOS_SetCube_(VB.RX,VB.RY,P[J]);
      else BIOS_SetChar(VB.RX,VB.RY,P[J]);
    VB.RX++;
    if(VB.RX >= VB.Coln)
    {
     VB.RX = 0;
     VB.RY++;
    }
    continue;
   }
   switch (P[J])
   {
    case '|' : VB.RX = X;
               VB.RY++;
               break;
    case '~' : J++;
               FC = True;
	       VB.LastColor = VB.ColorNor;
	       VB.ColorNor = P[J];
               break;
    case   2 : VB.RY--;
               break;
    case   4 : J++;
               if(P[J] > 0)
               {
                Word Count = P[J], Data = VB.RX + (VB.RY << 8);
                Byte Color = VB.ColorNor;
                asm MOV DX,Data;
                asm XOR BH,BH;
                asm MOV AH,2;
                asm INT 0x10;
                asm MOV AH,FC;
                asm ADD AH,9;
                asm MOV AL,' ';
                asm MOV BL,Color;
                asm MOV CX,Count;
                asm INT 0x10;
                VB.RX += P[J];
               }
               break;
    case   5 : VB.RY++;
               break;
    case   6 : VB.RX--;
               break;
    case   8 : VB.RX++;
               break;
    case   9 : {
                Byte RX = VB.RX, RY = VB.RY, Color = VB.ColorNor;
                asm MOV DL,RX;
                asm MOV DH,RY;
                asm XOR BH,BH;
                asm MOV AH,2;
                asm INT 0x10;
                asm MOV AH,FC;
                asm ADD AH,9;
                asm MOV AL,32;
                asm MOV BL,Color;
                asm MOV CX,8;
                asm INT 0x10;
                VB.RX += 7;
               }
               break;
    case  10 : VB.RX++;
               VB.RY++;
               break;
    case  11 : VB.RX--;
               VB.RY++;
               break;
    case  12 : VB.RX++;
               VB.RY--;
               break;
    case   1 : VB.RX--;
               VB.RY--;
               break;
    case  14 : VB.RX -= 2;
               VB.RY--;
               break;
    case  15 : VB.RX -= 2;
               VB.RY++;
               break;
    case  16 : J++;
               VB.RX = P[J++];
	       VB.RY = P[J];
               break;
    case '^' : {
                Byte Tmp = VB.ColorNor;
		FC           = True;
		VB.ColorNor  = VB.LastColor;
		VB.LastColor = Tmp;
               }
               break;
    case  28 : FC = False;
               break;
    case  29 : BIOS_ClearLine_(VB.RY,32);
               break;
    case  30 : J++;
               BIOS_SetChar(VB.RX++,VB.RY,P[J]);
               break;
    case  31 : BIOS_SetAttr_(VB.RX++,VB.RY);
               break;
   }
 End:;
  }
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_WriteTypingLn                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void BIOS_WriteTypingLn(Byte *P)
 {
  BIOS_WriteTyping_(P);
  BIOS_WriteTyping_("|");
 }

#else

 void BIOS_WriteTypingLn(String Chn)
 {
  BIOS_WriteTyping_(Chn);
  VB.RY++; VB.RX = 0;
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BIOS_CenterText                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void BIOS_CenterText(Byte Y,Byte *P, Byte C)
 {
  BIOS_WriteText((VB.Coln - strlen(P)) >> 1,Y,P,C);
 }

#else

 void BIOS_CenterText(Byte Y,Byte *P, Byte C)
 {
  BIOS_WriteText((VB.Coln - P[0]) >> 1,Y,P,C);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BIOS_WriteText                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void BIOS_WriteText(Byte X,Byte Y, Byte *P,Byte Color)
 {
  for(;*P;) BIOS_SetCube(X++,Y,*P++,Color);
 }

#else

 void BIOS_WriteText(Byte X, Byte Y, String Chn, Byte Color)
 {
  Byte I;
  for(I = 0;Chn[0] > I;I++) BIOS_SetCube(X+I,Y,Chn[I+1],Color);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BIOS_WriteText_                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void BIOS_WriteText_(Byte X,Byte Y, Byte *P)
 {
  for(;*P;) BIOS_SetCube(X++,Y,*P++,VB.ColorNor);
 }

#else

 void BIOS_WriteText_(Byte X,Byte Y, String Chn)
 {
  Byte I;
  for(I = 0;Chn[0] > I;I++) BIOS_SetCube(X+I,Y,Chn[I+1],VB.ColorNor);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    BIOS_WriteOnlyColor               ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void BIOS_WriteOnlyColor(Byte X,Byte Y, Byte *P,Byte C)
 {
  Word I;
  for(I=1;P[I];I++) BIOS_SetCube(X++,Y,BIOS_GetChar(X,Y,0),C);
 }

#else

 void BIOS_WriteOnlyColor(Byte X,Byte Y,String Chn,Byte C)
 {
  Byte I;
  for(I = 0;Chn[0] > I;I++) BIOS_SetCube(X+I,Y,BIOS_GetChar(X,Y,0),C);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                  BIOS_WriteOnlyColorAnd              ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void BIOS_WriteOnlyColorAnd(Byte X,Byte Y, Byte *P, Byte N, Byte Color)
 {
  Word I, Len = N + strlen(P);
  for(I = 1;I <= Len;I++) BIOS_SetCube(X++,Y,BIOS_GetChar(X,Y,0),Color);
 }

#else

 void BIOS_WriteOnlyColorAnd(Byte X,Byte Y,String Chn,Byte N, Byte Color)
 {
  Byte I, Tmp = N + Chn[0];
  for(I = 0;I < Tmp;I++) BIOS_SetCube(X+I,Y,BIOS_GetChar(X,Y,0),Color);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BIOS_WriteUnColor                ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void BIOS_WriteUncolor(Byte X,Byte Y,Byte *P)
 {
  Word I;
  for(I = 0;P[I];I++) BIOS_PutChar(X++,Y,0,P[I]);
 }

#else

 void BIOS_WriteUncolor(Byte X,Byte Y,String Chn)
 {
  Byte I;
  for(I = 0;I < Chn[0];I++) BIOS_PutChar(X+I,Y,0,Chn[I+1]);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    BIOS_WriteUncolorAs               ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void BIOS_WriteUncolorAs(Byte X, Byte Y, Byte *P, Byte Stop)
 {
  for(;(*P != Stop) && (*P != 0);) BIOS_PutChar(X++,Y,0,*P++);
 }

#else

 void BIOS_WriteUncolorAs(Byte X, Byte Y,String Chn, Byte Stop)
 {
  Byte I;
  for(I = 0;(Chn[I+1] != Stop)&&(Chn[0] > I);I++) BIOS_PutChar(X+I,Y,0,Chn[I+1]);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                        BIOS_WriteAs                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void BIOS_WriteAs(Byte X,Byte Y,Byte *P, Byte Color, Byte Stop)
 {
  for(;(*P != Stop) && (*P != 0);) BIOS_SetCube(X++,Y,*P++,Color);
 }

#else

 void BIOS_WriteAs(Byte X,Byte Y,String Chn, Byte Color, Byte Stop)
 {
  Byte I;
  for(I = 0;(Chn[I+1] != Stop)&&(Chn[0] > I);I++) BIOS_SetCube(X+I,Y,Chn[I+1],Color);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      BIOS_WriteToAs                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void BIOS_WriteToAs(Byte X,Byte Y,Byte *P, Word Pos,Byte C,Byte Stop)
 {
  for(*P += Pos;(*P != Stop) && (*P != 0);) BIOS_SetCube(X++,Y,*P++,C);
 }

#else

 void BIOS_WriteToAs(Byte X,Byte Y,String Chn, Byte Pos, Byte C,Byte Stop)
 {
  Byte I;
  for(I = Pos;(Chn[I+1] != Stop)&&(Chn[0] > I);I++) BIOS_SetCube(X+I,Y,Chn[I+1],C);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   BIOS_WriteUncolorToAs              ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void BIOS_WriteUncolorToAs(Byte X,Byte Y, Byte *P, Word Pos, Byte Stop)
 {
  for(*P += Pos;(*P != Stop) && (*P != 0);) BIOS_PutChar(X++,Y,0,*P++);
 }

#else

 void BIOS_WriteUncolorToAs(Byte X,Byte Y, String Chn, Byte Pos, Byte Stop)
 {
  Byte I;
  for(I = Pos;(Chn[I+1] != Stop)&&(Chn[0] > I);I++) BIOS_PutChar(X+I,Y,0,Chn[I+1]);
 }

#endif