/**********************************************************************/
/*                                                                    */
/*                         Malte System/Text                          */
/*                            1992/08/13                              */
/*                                                                    */
/*              Copyright (C) par les Chevaliers de Malte             */
/*                                                                    */
/**********************************************************************/

// Programmeur :
//
//  Sylvain Maltais
//
// DerniŠre modification :
//
//  Jeudi, le 13 mai 1993  (Adaptation de l'unit‚ au nouveau systŠme).
//
// Directive de compilation conditionnel :
//
// __PASCAL__     Indique qu'il doit ˆtre compatible au Turbo Pascal.
//

// ********************************************************
//                     INTERFACE/HEADER
// ********************************************************

#include <NUMERIC.H>
#include <TEXT.H>

#ifndef __Malte_TypeCadre__
 #define __Malte_TypeCadre__
 typedef Byte TypeCadre[8];
#endif

#ifndef __PASCAL__
 extern
#endif
  struct
        {
         LongWord Memory;
         Byte     TypeMode; // (0) Mono / (1) Color
         Byte     BitPerPixel;
         Byte     Methode;
         Boolean  Graph;
         Word     Color;
         Boolean  Blink;
         Byte     Mode;
         Byte     Line;
         Word     Coln;
         Byte     MaxLine;
         Word     MaxColn;
         Word     NumY;
         Word     MaxY;
         Boolean  EGA;
         Boolean  VGA;
         Boolean  ATFunction;
        }
        VC;

typedef struct VideoModeCfgType
        {
         Word    MaxXPixel;
         Word    MaxYPixel;
         Word    NumXPixel;
         Word    NumYPixel;
         Word    NumTextCols;
         Byte    NumTextRows;
         Word    MaxTextCols;
         Byte    MaxTextRows;
         Byte    NumPage;
         Byte    MaxPage;
         Word    HeightChar;
         Word    MaxColor;
         Word    NumColor;
         Byte    BitPerPixel;
         Boolean Blink;    // (0) False/(1) True
         Byte    TypeMode; // (0) Mono/(1) Color
         Byte    Format;   // (0) Text/(1) Graphic
         Byte    Mode;
        };

// ********************************************************
//                      IMPLEMENTATION
// ********************************************************

#include <BIOS_TXT.H>
#include <DIRECT.H>

extern struct {
               Boolean   Shade;
               Boolean   SpaceBorde;
               TypeCadre Borde;
               Word      Address;
               Word      ColnDouble;
               Byte      Page;
               Byte      Coln;
               Byte      Line;
               Byte      MaxX;
               Byte      MaxY;
               Byte      HalfMaxX;
               Byte      RX;
               Byte      RY;
               Byte      ColorNor;
               Byte      LastColor;
              }
              VD;

extern struct {
               Boolean   Shade;
               Boolean   SpaceBorde;
               TypeCadre Borde;
               Word      ColnDouble;
               Byte      Coln;
               Byte      Line;
               Byte      MaxX;
               Byte      MaxY;
               Byte      HalfMaxX;
               Byte      RX;
               Byte      RY;
               Byte      ColorNor;
               Byte      LastColor;
              }
              VB;

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    CopySmapleBorder                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifdef __PASCAL__

 void CopySampleBorder(Byte *Format)
 {
  Byte *Ptr = "ÚÄ¿³³ÀÄÙ",I;
  for(I = 0;I <= 7; I++) Format[I] = Ptr[I];
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     GetBitPerPixel                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

Byte GetBitPerPixel(Word Color)
{
 Byte I,Tmp;
 for(I = 15; I > 0;I--)
 {
  Tmp = ((Color >> I) & 1);
  if(Tmp) return(I);
 }
 return(0);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     GetDefaultColor                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

Word GetDefaultColor(void)
{
 const Tmp = VC.Mode;
 if(Tmp <= 0x03)
 {
  VC.Blink = True;
  VC.Graph = False;
  return(16);
 }
 if(Tmp < 0x08)
 {
  VC.Blink = False;
  VC.Graph = True;
  return((Tmp|1) == 0x05 ? 4 : 2);
 }
 if(Tmp == 0x07)
 {
  VC.Blink = True;
  VC.Graph = False;
  return(4);
 }
 if(VC.EGA)
 {
  if(Tmp < 0x11)
  {
   VC.Blink = False;
   VC.Graph = True;
   if((Tmp == 0x0D)||(Tmp == 0x0E)) return(16);
   if((Tmp == 0x0F)||(Tmp == 0x11)) return(2);
   if(Tmp == 0x10) return((VC.Memory == 0x10000 ? 4 : 16));
  }
  if((Tmp == 0x12)&&(VC.VGA))
  {
   VC.Blink = False;
   VC.Graph = True;
   return(16);
  }
  if(Tmp == 0x13)
  {
   VC.Blink = False;
   VC.Graph = True;
   return(256);
  }
 }
 return((VC.Graph = IsGraphic()) == 0 ? 16 : 0);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     GetVideoModeCfg                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void GetVideoModeCfg(struct VideoModeCfgType *V)
{
 (*V).Mode = VC.Mode; (*V).Format = VC.Graph; (*V).Blink = VC.Blink;
 {
  Word Tmp = BIOS_GetScanLine_();
  Tmp = (Tmp == 0 ? TextHeight() * VC.Line : Tmp);
  (*V).NumYPixel = Tmp;
  (*V).MaxYPixel = Tmp + 1;
 }
 if(VC.VGA)
 {
  if(VC.Mode < 4)
  {
   (*V).NumXPixel = VC.Coln * 9;
   (*V).MaxXPixel = (VC.Coln * 9) - 1;
  }
   else
  {
   (*V).NumXPixel = VC.Coln * 8;
   (*V).MaxXPixel = (VC.Coln * 8) - 1;
  }
 }
  else
 {
  (*V).NumXPixel = VC.Coln * 8;
  (*V).MaxXPixel = (VC.Coln * 8) - 1;
 }
 (*V).BitPerPixel = VC.BitPerPixel;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     _BarSelectHori                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _BarSelectHori(Byte X1, Byte Y, Byte X2)
{
 if(VC.Methode == 0) MEM__BarSelectHori(X1,Y,X2);
                else BIOS_BarSelectHori_(X1,Y,X2);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      _BarSpaceHori                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _BarSpaceHori(Byte X1, Byte Y, Byte X2)
{
 if(VC.Methode == 0) MEM__BarSpaceHori(X1,Y,X2);
                else BIOS_BarSpaceHori_(X1,Y,X2);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      _BarSpaceVert                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _BarSpaceVert(Byte X, Byte Y1, Byte Y2)
{
 if(VC.Methode == 0) MEM__BarSpaceVert(X,Y1,Y2);
                else BIOS_BarSpaceVert_(X,Y1,Y2);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      _BarTextHori                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _BarTextHori(Byte X1, Byte Y, Byte X2, Byte Char)
{
 if(VC.Methode == 0) MEM__BarTextHori(X1,Y,X2,Char);
                else BIOS_BarTextHori_(X1,Y,X2,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      _BarTextVert                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _BarTextVert(Byte X, Byte Y1, Byte Y2, Byte Char)
{
 if(VC.Methode == 0) MEM__BarTextVert(X,Y1,Y2,Char);
                else BIOS_BarTextVert_(X,Y1,Y2,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      _ClearLine                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _ClearLine(Byte Y, Byte Char)
{
 if(VC.Methode == 0) MEM__ClearLine(Y,Char);
                else BIOS_ClearLine_(Y,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    _ClearLineAs                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _ClearLineAs(Byte Y, Byte X2, Byte Char)
{
 if(VC.Methode == 0) MEM__ClearLineAs(Y,X2,Char);
                else BIOS_ClearLineAs_(Y,X2,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    _ClearColumns                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _ClearColumns(Byte X, Byte Char)
{
 if(VC.Methode == 0) MEM__ClearColumns(X,Char);
                else BIOS_ClearColumns_(X,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    _ClearWindow                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _ClearWindow(Byte X1,Byte Y1, Byte X2, Byte Y2)
{
 if(VC.Methode == 0) MEM__ClearWindow(X1,Y1,X2,Y2);
                else BIOS_ClearWindow_(X1,Y1,X2,Y2);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       _FillBox                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _FillBox(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Char)
{
 if(VC.Methode == 0) MEM__FillBox(X1,Y1,X2,Y2,Char);
                else BIOS_FillBox_(X1,Y1,X2,Y2,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     _PutEmptyBorder                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _PutEmptyBorder(Byte X1, Byte Y1, Byte X2, Byte Y2)
{
 if(VC.Methode == 0) MEM__PutEmptyBorder(X1,Y1,X2,Y2);
                else BIOS_PutEmptyBorder_(X1,Y1,X2,Y2);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                        _SetAttr                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _SetAttr(Byte X,Byte Y)
{
 if(VC.Methode == 0) MEM__SetAttr(X,Y);
                else BIOS_SetAttr_(X,Y);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                        _SetCube                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _SetCube(Byte X, Byte Y, Byte Char)
{
 if(VC.Methode == 0) MEM__SetCube(X,Y,Char);
                else BIOS_SetCube_(X,Y,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     _SetFillBorder                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _SetFillBorder(Byte X1, Byte Y1, Byte X2, Byte Y2)
{
 if(VC.Methode == 0) MEM__PutFillBorder(X1,Y1,X2,Y2);
                else BIOS_SetFillBorder_(X1,Y1,X2,Y2);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    _SetVideoModeText                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void _SetVideoModeText(Byte Mode)
{
 BIOS_SetVideoMode(Mode);
 MEM_InitVideo(); BIOS_InitVideo();
 VB.ColorNor = VD.ColorNor = 7;
 VB.LastColor = VD.LastColor = 15;
 VB.RX = VB.RY = 0;
 VD.RX = VD.RY = 0;
 VC.Color = 0;
 VC.TypeMode = (MEM_PortVideo() == 0x3B4 ? False : True);
 VC.Coln     = (VC.Methode == 0 ? VD.Coln : VB.Coln);
 VC.MaxColn  = (VC.Methode == 0 ? VD.MaxX : VB.MaxX);
 VC.Line     = (VC.Methode == 0 ? VD.Line : VB.Line);
 VC.MaxLine  = (VC.Methode == 0 ? VD.MaxY : VB.MaxY);
 VC.Mode     = (VC.Methode == 0 ? MEM_GetVideoMode() : BIOS_GetVideoMode());
 if(BIOS_Info_())
 {
  VC.Color = BIOS_GetNumColor();
  VC.Graph = ((VC.Blink = BIOS_GetBlink()) == 1 ? False : True);
  if((VC.Color == 0)&&(VC.Blink)) VC.Color = 4;
 }
  else
 VC.Color = GetDefaultColor();
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      _WriteText                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void _WriteText(Byte X,Byte Y, Byte *Phrase)
 {
  if(VC.Methode == 0) MEM__WriteText(X,Y,Phrase);
                 else BIOS_WriteText_(X,Y,Phrase);
 }

#else

 void _WriteText(Byte X,Byte Y, String Phrase)
 {
  if(VC.Methode == 0) MEM__WriteText(X,Y,Phrase);
                 else BIOS_WriteText_(X,Y,Phrase);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      _WriteTyping                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void _WriteTyping(Byte *Phrase)
 {
  if(VC.Methode == 0) MEM__WriteTyping(Phrase);
                 else BIOS_WriteTyping_(Phrase);
 }

#else

 void _WriteTyping(String Phrase)
 {
  if(VC.Methode == 0) MEM__WriteTyping(Phrase);
                 else BIOS_WriteTyping_(Phrase);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      BarCharHori                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BarCharHori(Byte X1, Byte Y, Byte X2, Byte Char)
{
 if(VC.Methode == 0) MEM_BarCharHori(X1,Y,X2,Char);
                else BIOS_BarCharHori(X1,Y,X2,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      BarCharVert                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BarCharVert(Byte X, Byte Y1, Byte Y2, Byte Char)
{
 if(VC.Methode == 0) MEM_BarCharVert(X,Y1,Y2,Char);
                else BIOS_BarCharVert(X,Y1,Y2,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BarSelectHori                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BarSelectHori(Byte X1, Byte Y, Byte X2, Byte Color)
{
 if(VC.Methode == 0) MEM_BarSelectHori(X1,Y,X2,Color);
                else BIOS_BarSelectHori(X1,Y,X2,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BarSelectVert                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BarSelectVert(Byte X, Byte Y1, Byte Y2, Byte Color)
{
 if(VC.Methode == 0) MEM_BarSelectVert(X,Y1,Y2,Color);
                else BIOS_BarSelectVert(X,Y1,Y2,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BarSpaceHori                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BarSpaceHori(Byte X1, Byte Y, Byte X2, Byte Color)
{
 if(VC.Methode == 0) MEM_BarSpaceHori(X1,Y,X2,Color);
                else BIOS_BarSpaceHori(X1,Y,X2,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BarSpaceVert                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BarSpaceVert(Byte X, Byte Y1, Byte Y2, Byte Color)
{
 if(VC.Methode == 0) MEM_BarSpaceVert(X,Y1,Y2,Color);
                else BIOS_BarSpaceVert(X,Y1,Y2,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BarTextHori                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BarTextHori(Byte X1, Byte Y, Byte X2, Byte Char, Byte Color)
{
 if(VC.Methode == 0) MEM_BarTextHori(X1,Y,X2,Char,Color);
                else BIOS_BarTextHori(X1,Y,X2,Char,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     BarTextVert                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void BarTextVert(Byte X, Byte Y1, Byte Y2, Byte Char, Byte Color)
{
 if(VC.Methode == 0) MEM_BarTextVert(X,Y1,Y2,Char,Color);
                else BIOS_BarTextVert(X,Y1,Y2,Char,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     CenterText                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void CenterText(Byte Y, Byte *Phr, Byte Color)
 {
  if(VC.Methode == 0) MEM_CenterText(Y,Phr,Color);
                 else BIOS_CenterText(Y,Phr,Color);
 }

#else

 void CenterText(Byte Y, String Phrase, Byte Color)
 {
  if(VC.Methode == 0) MEM_CenterText(Y,Phrase,Color);
                 else BIOS_CenterText(Y,Phrase,Color);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     ClearColumns                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void ClearColumns(Byte Columns, Byte Char, Byte Color)
{
 if(VC.Methode == 0) MEM_ClearColumns(Columns,Char,Color);
                else BIOS_ClearColumns(Columns,Char,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       ClearLine                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void ClearLine(Byte Y, Byte Char, Byte Color)
{
 if(VC.Methode == 0) MEM_ClearLine(Y,Char,Color);
                else BIOS_ClearLine(Y,Char,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     ClearLineAs                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void ClearLineAs(Byte Y, Byte X2, Byte Char, Byte Color)
{
 if(VC.Methode == 0) MEM_ClearLineAs(Y,X2,Char,Color);
                else BIOS_ClearLineAs(Y,X2,Char,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     ClearLineUncolor                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void ClearLineUncolor(Byte Line, Byte Char)
{
 if(VC.Methode == 0) MEM_ClearLineUncolor(Line,Char);
                else BIOS_ClearLineUncolor(Line,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     ClearWindow                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void ClearWindow(Byte X1,Byte Y1, Byte X2,Byte Y2,Byte Color)
{
 if(VC.Methode == 0) MEM_ClearWindow(X1,Y1,X2,Y2,Color);
                else BIOS_ClearWindow(X1,Y1,X2,Y2,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     CloseCursor                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void CloseCursor(void)
{
 if(VC.Methode == 0) IO_CloseCursor();
                else BIOS_CloseCursor();
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       FillBox                        ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void FillBox(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Char, Byte Color)
{
 if(VC.Methode == 0) MEM_FillBox(X1,Y1,X2,Y2,Char,Color);
                else BIOS_FillBox(X1,Y1,X2,Y2,Char,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       GetBlink                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

Byte GetBlink(void)
{
 return(VC.Blink);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       GetColor                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

Byte GetColor(void)
{
 return((VC.Methode == 0 ? VD.ColorNor : VB.ColorNor));
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       GetMaxX                        ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

Byte GetMaxX(void)
{
 return(VC.MaxColn);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       GetMaxY                        ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

Byte GetMaxY(void)
{
 return(VC.MaxLine);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                        GetPos                        ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void GetPos(Byte *X,Byte *Y)
{
 if(VC.Methode == 0)
 {
  *X = VD.RX;
  *Y = VD.RY;
 }
  else
 {
  *X = VB.RX;
  *Y = VB.RY;
 }
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     GetVideoMethode                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

Byte GetVideoMethode(void)
{
 return(VC.Methode);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     GetVideoMode                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

Byte GetVideoMode(void)
{
 return(VC.Mode);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                         IsEGA                        ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

Byte IsEGA(void)
{
 return(VC.EGA);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                         IsVGA                        ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

Byte IsVGA(void)
{
 return(VC.VGA);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       InitVideo                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void InitVideo(void)
{
 #ifdef __PASCAL__
  CopySampleBorder(VB.Borde);
  CopySampleBorder(VD.Borde);
 #endif
 MEM_InitVideo(); BIOS_InitVideo();
 VC.EGA = BIOS_IsEGA();
 if(VC.EGA) VC.Memory = BIOS_EGA_SizeMemory();
 {
  Word Tmp = BIOS_GetVideoCard();
  VC.VGA = (((Tmp == 0x07)||(Tmp == 0x08)) ? True : False);
 }
 VC.TypeMode = (MEM_PortVideo() == 0x3B4 ? False : True);
 VC.Mode     = (VC.Methode == 0 ? MEM_GetVideoMode() : BIOS_GetVideoMode());
 VC.Line     = (VC.Methode == 0 ? VD.Line : VB.Line);
 VC.MaxLine  = (VC.Methode == 0 ? VD.MaxY : VB.MaxY);
 VC.Coln     = (VC.Methode == 0 ? VD.Coln : VB.Coln);
 VC.MaxColn  = (VC.Methode == 0 ? VD.MaxX : VB.MaxX);
 VC.Color    = 0;
 if(BIOS_Info_())
 {
  VC.Blink = BIOS_GetBlink();
  VC.Color = BIOS_GetNumColor();
 }
  else
 VC.Color = GetDefaultColor();
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    PutBorderUncolor                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void PutBorderUncolor(Byte X1, Byte Y1, Byte X2, Byte Y2)
{
 if(VC.Methode == 0) MEM_PutBorderUncolor(X1,Y1,X2,Y2);
                else BIOS_PutBorderUncolor(X1,Y1,X2,Y2);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                         PutBox                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void PutBox(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte *Buffer)
{
 if(VC.Methode == 0) MEM_PutBox(X1,Y1,X2,Y2,Buffer);
                else BIOS_PutBox(X1,Y1,X2,Y2,Buffer);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                        PutEmpty                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void PutEmptyBorder(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Color)
{
 if(VC.Methode == 0) MEM_PutEmptyBorder(X1,Y1,X2,Y2,Color);
                else BIOS_PutEmptyBorder(X1,Y1,X2,Y2,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    PutFillBorder                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void PutFillBorder(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Color)
{
 if(VC.Methode == 0) MEM_PutFillBorder(X1,Y1,X2,Y2,Color);
                else BIOS_PutFillBorder(X1,Y1,X2,Y2,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       SaveBox                        ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SaveBox(Byte X1,Byte Y1, Byte X2,Byte Y2, Byte *Buffer)
{
 if(VC.Methode == 0) MEM_SaveBox(X1,Y1,X2,Y2,Buffer);
                else BIOS_SaveBox(X1,Y1,X2,Y2,Buffer);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      ScrollDown_                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void ScrollDown_(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Color)
{
 BIOS_ScrollDown(X1,Y1,X2,Y2,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      ScrollUp_                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void ScrollUp_(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte Color)
{
 BIOS_ScrollUp_(X1,Y1,X2,Y2,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                        SetAttr                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetAttr(Byte X,Byte Y,Byte Color)
{
 if(VC.Methode == 0) MEM_SetAttr(X,Y,Color);
                else BIOS_SetAttr(X,Y,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      SetBlink                        ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetBlink(Boolean X)
{
 X &= 1;
 MEM_SetBlink(X);
 VC.Blink = X;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     SetBorderFormat                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetBorderFormat(TypeCadre Format)
{
 if(VC.Methode == 0) MEM_SetBorderFormat(Format);
                else BIOS_SetBorderFormat(Format);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     SetBorderSpace_                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetBorderSpace_(void)
{
 TypeCadre Format = {' ',' ',' ',' ',' ',' ',' ',' '};
 SetBorderFormat(Format);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     SetBorderShade_                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetBorderShade_(void)
{
 TypeCadre Format;
 CopySampleBorder(Format);
 SetBorderFormat(Format);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     SetBorderShade                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetBorderShade(Boolean X)
{
 if(VC.Methode == 0) MEM_SetBorderShade(X);
                else BIOS_SetBorderShade(X);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     SetBorderSpace                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetBorderSpace(Boolean X)
{
 if(VC.Methode == 0) MEM_SetBorderSpace(X);
                else BIOS_SetBorderSpace(X);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                         SetChar                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetChar(Byte X,Byte Y,Byte Char)
{
 if(VC.Methode == 0) MEM_SetChar(X,Y,Char);
                else BIOS_SetChar(X,Y,Char);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                        SetColor                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetColor(Byte Color)
{
 if(VC.Methode == 0) MEM_SetColor(Color);
                else BIOS_SetColor(Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                        SetCube                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetCube(Byte X, Byte Y, Byte Char, Byte Color)
{
 if(VC.Methode == 0) MEM_SetCube(X,Y,Char,Color);
                else BIOS_SetCube(X,Y,Char,Color);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                        SetCursor                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetCursor(Byte Start, Byte End)
{
 if(VC.Methode == 0) IO_SetCursor(Start,End);
                else BIOS_SetCursor(Start,End);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      SetPaletteRGB                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetPaletteRGB(Word Registre, Byte Red, Byte Green, Byte Blue)
{
 if((VC.EGA)&&(VC.VGA == 0))
 {
  Byte TmpRed, TmpGreen, TmpBlue;
  if(Red   != 0) TmpRed   = (Red / 64); else TmpRed = 0;
  if(Green != 0) TmpGreen = (Green / 64); else TmpGreen = 0;
  if(Blue  != 0) TmpBlue  = (Blue / 64); else TmpBlue = 0;
  BIOS_SetPaletteEGA(Registre,((TmpBlue & 1) + ((TmpBlue & 2) << 2)) +
                              (((TmpGreen & 1) << 1) + ((TmpGreen & 2) << 3)) +
                              (((TmpRed & 1) << 2) + ((TmpRed & 2) << 4)));
 }
  else
 if(VC.VGA)
 {
  Byte TmpRed, TmpGreen, TmpBlue;
  if(Red   != 0) TmpRed   = (Red / 4); else TmpRed = 0;
  if(Green != 0) TmpGreen = (Green / 4); else TmpGreen = 0;
  if(Blue  != 0) TmpBlue  = (Blue / 4); else TmpBlue = 0;
  BIOS_SetPaletteVGA(Registre,TmpRed,TmpGreen,TmpBlue);
 }
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                         SetPos                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetPos(Byte X,Byte Y)
{
 if(VC.Methode == 0) MEM_SetPos(X,Y);
  else
 {
  VB.RX = X;
  VB.RY = Y;
 }
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       SetPosCursor                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetPosCursor(Byte X, Byte Y)
{
 if(VC.Methode == 0) IO_SetPosCursor(X,Y);
                else BIOS_SetPosCursor(X,Y,0);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       SetScanLine                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetScanLine(Byte Format)
{
 BIOS_SetScanLine(Format);
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     SetVideoMethode                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetVideoMethode(Byte Mode)
{
 VC.Methode = Mode;
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    SetVideoModeText                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SetVideoModeText(char Mode)
{
 if(VC.Methode == 0)
 {
  MEM_SetVideoModeText(Mode);
  VD.ColorNor   = 7;
  VD.LastColor  = 15;
  VD.RX = VD.RY = 0;
  VC.Coln       = VD.Coln;
  VC.Line       = VD.Line;
  VC.MaxColn    = VD.MaxX;
  VC.MaxLine    = VD.MaxY;
 }
  else
 {
  BIOS_SetVideoMode_(Mode);
  VB.ColorNor   = 7;
  VB.LastColor  = 15;
  VB.RX = VB.RY = 0;
  VC.Coln       = VB.Coln;
  VC.Line       = VB.Line;
  VC.MaxColn    = VB.MaxX;
  VC.MaxLine    = VB.MaxY;
  MEM_InitVideo();
  VD.RX = VD.RY = 0;
 }
 VC.TypeMode = (MEM_PortVideo() == 0x3B4 ? False : True);
 VC.Mode     = (VC.Methode == 0 ? MEM_GetVideoMode() : BIOS_GetVideoMode());
 VC.Color    = 0;
 if(BIOS_Info_())
 {
  VC.Blink = BIOS_GetBlink();
  VC.Color = BIOS_GetNumColor();
  if((VC.Color == 0)&&(VC.Blink)) VC.Color = 4;
 }
  else
 VC.Color = GetDefaultColor();
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      SwitchColor                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

void SwitchColor(void)
{
 if(VC.Methode == 0) MEM_SwitchColor();
                else BIOS_SwitchColor();
}

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                        WriteAs                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void WriteAs(Byte X,Byte Y, Byte *Phrase, Byte Color, Byte Stop)
 {
  if(VC.Methode == 0) MEM_WriteAs(X,Y,Phrase,Color,Stop);
                 else BIOS_WriteAs(X,Y,Phrase,Color,Stop);
 }

#else

 void WriteAs(Byte X,Byte Y, String Phrase, Byte Color, Byte Stop)
 {
  if(VC.Methode == 0) MEM_WriteAs(X,Y,Phrase,Color,Stop);
                 else BIOS_WriteAs(X,Y,Phrase,Color,Stop);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      WriteOnlyColor                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void WriteOnlyColor(Byte X,Byte Y, Byte *Phrase, Byte Color)
 {
  if(VC.Methode == 0) MEM_WriteOnlyColor(X,Y,Phrase,Color);
                 else BIOS_WriteOnlyColor(X,Y,Phrase,Color);
 }

#else

 void WriteOnlyColor(Byte X,Byte Y, String Phrase, Byte Color)
 {
  if(VC.Methode == 0) MEM_WriteOnlyColor(X,Y,Phrase,Color);
                 else BIOS_WriteOnlyColor(X,Y,Phrase,Color);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     WriteOnlyColorAnd                ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void WriteOnlyColorAnd(Byte X,Byte Y, Byte *Phrase,Byte Nombre, Byte Color)
 {
  if(VC.Methode == 0) MEM_WriteOnlyColorAnd(X,Y,Phrase,Nombre,Color);
                 else BIOS_WriteOnlyColorAnd(X,Y,Phrase,Nombre,Color);
 }

#else

 void WriteOnlyColorAnd(Byte X,Byte Y, String Phrase, Byte Nombre, Byte Color)
 {
  if(VC.Methode == 0) MEM_WriteOnlyColorAnd(X,Y,Phrase,Nombre,Color);
                 else BIOS_WriteOnlyColorAnd(X,Y,Phrase,Nombre,Color);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                        WriteText                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void WriteText(Byte X,Byte Y, Byte *Phrase, Byte Color)
 {
  if(VC.Methode == 0) MEM_WriteText(X,Y,Phrase,Color);
                 else BIOS_WriteText(X,Y,Phrase,Color);
 }

#else

 void WriteText(Byte X,Byte Y, String Phrase, Byte Color)
 {
  if(VC.Methode == 0) MEM_WriteText(X,Y,Phrase,Color);
                 else BIOS_WriteText(X,Y,Phrase,Color);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       WriteTypingXY                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void WriteTypingXY(Byte X, Byte Y, Byte *Phrase)
 {
  if(VC.Methode == 0) MEM_WriteTypingXY(X,Y,Phrase);
                 else BIOS_WriteTypingXY(X,Y,Phrase);
 }

#else

 void WriteTypingXY(Byte X, Byte Y, String Phrase)
 {
  if(VC.Methode == 0) MEM_WriteTypingXY(X,Y,Phrase);
                 else BIOS_WriteTypingXY(X,Y,Phrase);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    WriteTypingXYBicolor              ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void WriteTypingXYBicolor(Byte X,Byte Y, Byte *Phrase, Byte LastColor, Byte NewColor)
 {
  if(VC.Methode == 0) MEM_WriteTypingXYBicolor(X,Y,Phrase,LastColor,NewColor);
                 else BIOS_WriteTypingXYBicolor(X,Y,Phrase,LastColor,NewColor);
 }

#else

 void WriteTypingXYBicolor(Byte X,Byte Y, String Phrase, Byte LastColor, Byte NewColor)
 {
  if(VC.Methode == 0) MEM_WriteTypingXYBicolor(X,Y,Phrase,LastColor,NewColor);
                 else BIOS_WriteTypingXYBicolor(X,Y,Phrase,LastColor,NewColor);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       WriteToAs                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void WriteToAs(Byte X,Byte Y,Byte *Phrase, Word Pos, Byte Color, Byte Stop)
 {
  if(VC.Methode == 0) MEM_WriteToAs(X,Y,Phrase,Pos,Color,Stop);
                 else BIOS_WriteToAs(X,Y,Phrase,Pos,Color,Stop);
 }

#else

 void WriteToAs(Byte X,Byte Y,String Phrase, Byte Pos, Byte Color, Byte Stop)
 {
  if(VC.Methode == 0) MEM_WriteToAs(X,Y,Phrase,Pos,Color,Stop);
                 else BIOS_WriteToAs(X,Y,Phrase,Pos,Color,Stop);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      WriteUncolor                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void WriteUncolor(Byte X,Byte Y,Byte *Phrase)
 {
  if(VC.Methode == 0) MEM_WriteUncolor(X,Y,Phrase);
                 else BIOS_WriteUncolor(X,Y,Phrase);
 }

#else

 void WriteUncolor(Byte X,Byte Y,String Phrase)
 {
  if(VC.Methode == 0) MEM_WriteUncolor(X,Y,Phrase);
                 else BIOS_WriteUncolor(X,Y,Phrase);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      WriteUncolorAs                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void WriteUncolorAs(Byte X, Byte Y, Byte *Phrase, Byte Stop)
 {
  if(VC.Methode == 0) MEM_WriteUncolorAs(X,Y,Phrase,Stop);
                 else BIOS_WriteUncolorAs(X,Y,Phrase,Stop);
 }

#else

 void WriteUncolorAs(Byte X, Byte Y, String Phrase, Byte Stop)
 {
  if(VC.Methode == 0) MEM_WriteUncolorAs(X,Y,Phrase,Stop);
                 else BIOS_WriteUncolorAs(X,Y,Phrase,Stop);
 }

#endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    WriteUncolorToAs                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

#ifndef __PASCAL__

 void WriteUncolorToAs(Byte X,Byte Y,Byte *Phrase, Word Pos, Byte Stop)
 {
  if(VC.Methode == 0) MEM_WriteUncolorToAs(X,Y,Phrase,Pos,Stop);
                 else BIOS_WriteUncolorToAs(X,Y,Phrase,Pos,Stop);
 }

#else

 void WriteUncolorToAs(Byte X,Byte Y, String Phrase, Byte Pos, Byte Stop)
 {
  if(VC.Methode == 0) MEM_WriteUncolorToAs(X,Y,Phrase,Pos,Stop);
                 else BIOS_WriteUncolorToAs(X,Y,Phrase,Pos,Stop);
 }

#endif
