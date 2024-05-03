/*******************************************************************/
/*                                                                 */
/*                         Malte System/Menu                       */
/*                            1992/10/19                           */
/*                                                                 */
/*             Copyright (C) par les Chevaliers de Malte           */
/*                                                                 */
/*******************************************************************/

//
//         *** Summary information ***
//
//  The file name is       : MNU.C
//  The headerfile name is : VIDEO\MNU.H
//  Created the            : 1992/07/10
//  Author is              : Sylvain Maltais
//

/*******************************************************************/
/*                            INTERFACE                            */
/*******************************************************************/

#include <VIDEO\MNU.H>

Byte MnuMin = 'Ã';
Byte MnuMax = '´';
Byte X1Hlp  = 10;
Byte YHlp   = 24;
Byte X2Hlp  = 78;

/*******************************************************************/
/*                        IMPLEMENTATION                           */
/*******************************************************************/

#include "ALLOC.H"
#include "STRING.H"
#include <KEYBOARD.H>
#include <MOUSE.H>
#include <VIDEO\TEXT\TEXT.H>

extern struct {
               Byte      Shade;
               Byte      SpaceBorde;
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
               Byte      Shade;
               Byte      SpaceBorde;
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
 extern struct
        {
         LongWord Memory;
         Byte     TypeMode; // (0) Mono / (1) Color
         Byte     BitPerPixel;
         Byte     Methode;
         Byte     Graph;
         Word     Color;
         Byte     Blink;
         Byte     Mode;
         Byte     Line;
         Word     Coln;
         Byte     MaxLine;
         Word     MaxColn;
         Word     NumY;
         Word     MaxY;
         Byte     EGA;
         Byte     VGA;
         Byte     ATFunction;
        }
        VC;

extern Word XMouse;
extern Word YMouse;
extern Word ButtonMouse;

#define XMerge -1

void LineHelp(Byte *Hlp)
{
 #ifndef __NotHelp__
  WriteUncolor(X1Hlp,YHlp,Hlp);
  BarCharHori(X1Hlp+strlen(Hlp),YHlp,X2Hlp,' ');
 #endif
}

void PutLineMnu(Byte X, Byte Y, Byte Len, Byte *S, Byte CC, Byte CN)
{
 if(S[0] == 0)
 {
  SetChar(X,Y,MnuMin);
  BarCharHori(X+1,Y,X+Len-1,'Ä');
  SetChar(X+Len,Y,MnuMax);
 }
  else
 WriteTypingXYBicolor(X+2,Y,S,CC,CN);
}

void WriteOldLine(Byte X, Byte Y, Byte Len, Byte *Str, Byte CN, Byte CC)
{
 BarSelectHori(X,Y,X+Len,CN);
 WriteTypingXYBicolor(X+1,Y,Str,CC,CN);
}

void WriteNewLine(Byte X, Byte Y, Byte Len, Byte *Hlp, Byte Color)
{
 LineHelp(Hlp);
 BarSelectHori(X,Y,X+Len,Color);
}

void LineHome(Byte X, Byte Y, Byte Len, Byte Pos, Byte *Str[], Byte *Hlp[], Byte CN, Byte CC, Byte CS)
{
 if(Pos != 0)
 {
  WriteOldLine(X,Y+Pos,Len,Str[Pos],CN,CC);
  WriteNewLine(X,Y,Len,Hlp[0],CS);
 }
}

Word FirstMnu(Byte X, Byte Y, Byte *Tl, Byte *S[], Byte *Hlp[], Byte CN, Byte CC, Byte CS, int *AP)
{
 Byte P,PL,True;
 Word K;
 int  I;
 CloseCursor();
 for(P = 0,PL = strlen(Tl);S[P] != NULL;P++)
 {
  Word Len = strlen(S[P]);
  PL = (Len > PL ? Len : PL);
 }
 P--;
 WriteOnlyColorAnd(X,Y++,Tl,2,CS);
 PutFillBorder(X,Y,X+PL+XMerge,Y+P+2,CN);
 for(I = 0;S[I] != NULL;I++) PutLineMnu(X,Y+I+1,PL+XMerge,S[I],CC,CN);
 WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
 do
  {
   True = 0;
   K = ReadKey();
   if(K == kbHome)
   {
    True = 1;
    LineHome(X+1,Y+1,PL+XMerge-1,*AP,S,Hlp,CN,CC,CS);
    *AP = 0;
   }
   if(K == kbUp)
   {
    True = 1;
    if(P != 0)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = Min(*AP,P);
     *AP = (S[*AP][0] == 0 ? *AP-1 : *AP);
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
   if(K == kbDown)
   {
    True = 1;
    if(P != 0)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = Max(*AP,P);
     *AP = (S[*AP][0] == 0 ? *AP+1 : *AP);
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
   if(K == kbEnd)
   {
    True = 1;
    if(*AP != P)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = P;
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
  }
 while(True == 1);
 return(K);
}

Word FirstMnuMouse(Byte X, Byte Y, Byte *Tl, Byte *S[], Byte *Hlp[], Byte CN, Byte CC, Byte CS, int *AP)
{
 Byte P,PL; Word K; int I; unsigned True;
 CloseCursor();
 for(P = 0,PL = strlen(Tl);S[P] != NULL;P++)
 {
  Word Len = strlen(S[P]);
  PL = (Len > PL ? Len : PL);
 }
 P--;
 WriteOnlyColorAnd(X,Y++,Tl,2,CS);
 PutFillBorder(X,Y,X+PL+XMerge,Y+P+2,CN);
 for(I = 0;S[I] != NULL;I++) PutLineMnu(X,Y+I+1,PL+XMerge,S[I],CC,CN);
 WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
 do
  {
   ShowPtr();
   while(!KeyPressed())
   {
    GetButPos(&ButtonMouse,&XMouse,&YMouse);
    if(ButtonMouse > 0)
    {
     Byte YMs = (YMouse / 8);
     if((YMs > Y)&&(YMs < Y + P + 2))
     {
      Byte XMs = (XMouse / 8);
      if((XMs > X)&&(XMs < X + PL + XMerge))
      {
       if((*AP != YMs-Y-1)&&(S[YMs-Y-1][0] != 0))
       {
        HidePtr();
        WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
        *AP = YMs - Y - 1;
        WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
        ShowPtr();
        ReleaseKeyMouse();
        HidePtr();
        return(kbEnter);
       }
      }
     }
     ReleaseKeyMouse();
     HidePtr();
     return(0xFFFF-ButtonMouse);
    }
   }
   HidePtr();
   True = 0; K = ReadKey();
   if(K == kbHome)
   {
    True = 1;
    LineHome(X+1,Y+1,PL+XMerge-1,*AP,S,Hlp,CN,CC,CS);
    *AP = 0;
   }
   if(K == kbUp)
   {
    True = 1;
    if(P != 0)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = Min(*AP,P);
     *AP = (S[*AP][0] == 0 ? *AP-1 : *AP);
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
   if(K == kbDown)
   {
    True = 1;
    if(P != 0)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = Max(*AP,P);
     *AP = (S[*AP][0] == 0 ? *AP+1 : *AP);
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
   if(K == kbEnd)
   {
    True = 1;
    if(*AP != P)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = P;
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
  }
 while(True == 1);
 return(K);
}

Word FirstMnuMouse_(Byte X, Byte Y, Byte *Tl, Byte *S[], Byte *Hlp[], Byte CN, Byte CC, Byte CS, int *AP)
{
 #if (defined(__HUGE__)||defined(__LARGE__)||defined(__MEDIUM__))
  Byte far *Buffer;
 #else
  Byte near *Buffer;
 #endif
 Byte P,PL,Y1 = Y,True;
 Word K;
 int  I;
 CloseCursor();
 for(P = 0,PL = strlen(Tl);S[P] != NULL;P++)
 {
  Word Len = strlen(S[P]);
  PL = (Len > PL ? Len : PL);
 }
 P--;
 *Buffer = NULL;
 {
  Word Size = SizeBox(X,Y,X+PL+XMerge,Y+P+5);
  #if (defined(__HUGE__)||defined(__LARGE__)||defined(__MEDIUM__))
   if(farcoreleft() > Size) return(1);
   Buffer = farmalloc(Size);
  #else
   if(coreleft() > Size) return(1);
   Buffer = malloc(Size);
  #endif
 }
 SaveBox(X,Y1,X+PL+XMerge+2,Y1+P+4,Buffer);
 WriteOnlyColorAnd(X,Y++,Tl,2,CS);
 PutFillBorder(X,Y,X+PL+XMerge,Y+P+2,CN);
 for(I = 0;S[I] != NULL;I++) PutLineMnu(X,Y+I+1,PL+XMerge,S[I],CC,CN);
 WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
 do
  {
   ShowPtr();
   while(!KeyPressed())
   {
    GetButPos(&ButtonMouse,&XMouse,&YMouse);
    if(ButtonMouse > 0)
    {
     Byte YMs = (YMouse / 8);
     if((YMs > Y)&&(YMs < Y + P + 2))
     {
      Byte XMs = (XMouse / 8);
      if((XMs > X)&&(XMs < X + PL + XMerge))
      {
       if((*AP != YMs-Y-1)&&(S[YMs-Y-1][0] != 0))
       {
        HidePtr();
        WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
        *AP = YMs - Y - 1;
        WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
        ShowPtr();
        ReleaseKeyMouse();
        HidePtr();
        PutBox(X,Y1,X+PL+XMerge+2,Y1+P+4,Buffer);
        farfree(Buffer);
        return(kbEnter);
       }
      }
     }
     ReleaseKeyMouse();
     HidePtr();
     PutBox(X,Y1,X+PL+XMerge+2,Y1+P+4,Buffer);
     farfree(Buffer);
     return(0xFFFF-ButtonMouse);
    }
   }
   True = 0;
   HidePtr();
   K = ReadKey();
   if(K == kbHome)
   {
    True = 1; LineHome(X+1,Y+1,PL+XMerge-1,*AP,S,Hlp,CN,CC,CS); *AP = 0;
   }
   if(K == kbUp)
   {
    True = 1;
    if(P != 0)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = Min(*AP,P); *AP = (S[*AP][0] == 0 ? *AP-1 : *AP);
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
   if(K == kbDown)
   {
    True = 1;
    if(P != 0)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = Max(*AP,P); *AP = (S[*AP][0] == 0 ? *AP+1 : *AP);
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
   if(K == kbEnd)
   {
    True = 1;
    if(*AP != P)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = P;
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
  }
 while(True == 1);
 PutBox(X,Y1,X+PL+XMerge+2,Y1+P+4,Buffer);
 #if (defined(__HUGE__)||defined(__LARGE__)||defined(__MEDIUM__))
  farfree(Buffer);
 #else
  free(Buffer);
 #endif
 return(K);
}

Word StageMnuMouse(Byte X, Byte Y, Byte *S[], Byte *Hlp[], Byte CN, Byte CC, Byte CS, int *AP)
{
 Byte P,PL,True;
 Word K;
 int  I;
 CloseCursor();
 for(P = 0,PL = 0;S[P] != NULL;P++)
 {
  PL = (strlen(S[P]) > PL ? strlen(S[P]) : PL);
 }
 P--;
 PutFillBorder(X,Y,X+PL+XMerge,Y+P+2,CN);
 for(I = 0;S[I] != NULL;I++) PutLineMnu(X,Y+I+1,PL+XMerge,S[I],CC,CN);
 WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
 do
  {
   ShowPtr();
   while(!KeyPressed())
   {
    GetButPos(&ButtonMouse,&XMouse,&YMouse);
    if(ButtonMouse > 0)
    {
     Byte YMs = (YMouse / 8);
     if((YMs > Y)&&(YMs < Y + P + 2))
     {
      Byte XMs = (XMouse / 8);
      if((XMs > X)&&(XMs < X + PL + XMerge))
      {
       if((*AP != YMs-Y-1)&&(S[YMs-Y-1][0] != 0))
       {
        HidePtr();
        WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
        *AP = YMs - Y - 1;
        WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
        ShowPtr();
        ReleaseKeyMouse();
        HidePtr();
        return(kbEnter);
       }
      }
     }
     ReleaseKeyMouse();
     HidePtr();
     return(0xFFFF-ButtonMouse);
    }
   }
   True = 0;
   HidePtr();
   K = ReadKey();
   if(K == kbHome)
   {
    True = 1; LineHome(X+1,Y+1,PL+XMerge-1,*AP,S,Hlp,CN,CC,CS); *AP = 0;
   }
   if(K == kbUp)
   {
    True = 1;
    if(P != 0)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = Min(*AP,P); *AP = (S[*AP][0] == 0 ? *AP-1 : *AP);
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
   if(K == kbDown)
   {
    True = 1;
    if(P != 0)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = Max(*AP,P); *AP = (S[*AP][0] == 0 ? *AP+1 : *AP);
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
   if(K == kbEnd)
   {
    True = 1;
    if(*AP != P)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = P;
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
  }
 while(True == 1);
 return(K);
}

void PutMainMnu(Byte X1, Byte Y, Byte X2, Byte *Titre, Byte *Menu, Byte ColTit, Byte ColNor, Byte ColChx)
{
 Byte XS = (X2-X1); X2 = (X2 == 0xFF ? GetMaxX() : X2);
 BarSpaceHori(X1,Y,X2,ColTit);
 WriteUncolor(X1+((XS+strlen(Titre)) << 1),Y,Titre);
 BarSpaceHori(X1,Y+1,X2,ColNor);
 WriteTypingXYBicolor(X1+2,Y+1,Menu,ColChx,ColNor);
}

void SetMnuFormat(Byte Min, Byte Max)
{
 MnuMin = Min; MnuMax = Max;
}

Word StageMnu(Byte X, Byte Y, Byte *S[], Byte *Hlp[], Byte CN, Byte CC, Byte CS, int *AP)
{
 Byte P,PL; Word K; int I; unsigned True;
 CloseCursor();
 for(P = 0,PL = 0;S[P] != NULL;P++)
 {
  Word Len = strlen(S[P]); PL = (Len > PL ? Len : PL);
 }
 P--;
 PutFillBorder(X,Y,X+PL+XMerge,Y+P+2,CN);
 for(I = 0;S[I] != NULL;I++) PutLineMnu(X,Y+I+1,PL+XMerge,S[I],CC,CN);
 WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
 do
  {
   True = 0;
   K = ReadKey();
   if(K == kbHome)
   {
    True = 1; LineHome(X+1,Y+1,PL+XMerge-1,*AP,S,Hlp,CN,CC,CS); *AP = 0;
   }
   if(K == kbUp)
   {
    True = 1;
    if(P != 0)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = Min(*AP,P); *AP = (S[*AP][0] == 0 ? *AP-1 : *AP);
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
   if(K == kbDown)
   {
    True = 1;
    if(P != 0)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = Max(*AP,P); *AP = (S[*AP][0] == 0 ? *AP+1 : *AP);
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
   if(K == kbEnd)
   {
    True = 1;
    if(*AP != P)
    {
     WriteOldLine(X+1,Y+1+*AP,PL+XMerge-1,S[*AP],CN,CC);
     *AP = P;
     WriteNewLine(X+1,Y+1+*AP,PL+XMerge-1,Hlp[*AP],CS);
    }
   }
  }
 while(True == 1);
 return(K);
}

void GetMenuMousePos(Word *X, Word *Y)
{
 *X = XMouse; *Y = YMouse;
}

void StageMnuPos(Byte *S[], Byte *XS, Byte *YS)
{
 Word P,PL,X,Y;
 for(P = 0,PL = 0;S[P] != NULL;P++)
 {
  PL = (strlen(S[P]) > PL ? strlen(S[P]) : PL);
 }
 if((VB.Shade|VD.Shade) == 1) { X = 2; Y = 1; }
	                 else { X = 0; Y = 0; }
 *XS = X + PL + XMerge; *YS = Y + P + 1;
}

void FirstMnuPos(Byte *Tl, Byte *S[], Byte *XS, Byte *YS)
{
 Word P, PL, X, Y;
 for(P = 0,PL = strlen(Tl);S[P] != NULL;P++)
 {
  PL = (strlen(S[P]) > PL ? strlen(S[P]) : PL);
 }
 if((VD.Shade|VB.Shade) == 1) { X = 2; Y = 1; }
   	                 else { X = 0; Y = 0; }
 *XS = X + PL + XMerge; *YS = Y + P + 2;
}

void SetPosHelp(Byte X1, Byte Y, Byte X2)
{
 X1Hlp = X1;
 YHlp  = Y;
 X2Hlp = X2;
}