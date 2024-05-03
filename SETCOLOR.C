#ifndef __Malte_Video_SetColor__
 #define __Malte_Video_SetColor__

 extern unsigned char DataHex[16];

 #include <STRING.H>
 #include <STDLIB.H>
 #include <TRANSLTR.H>
 #include <MOUSE\MOUSE.H>
 #include <VIDEO\TEXT_MEM.H>
 #include <VIDEO\BIOS_TXT.H>
 #include <VIDEO\TEXT.H>
 #include <VIDEO\KEYVIDEO.C>
 #include <VIDEO\LEVEL.H>
 #include <KEYBOARD\BIOS_KEY.H>
 #include <KEYBOARD\KEY_CST.H>

 #define LenBox                                                 3
 #define NumBox                                                16
 #define LenKey                                                10

 #define X1Box                                                  3
 #define Y1Box                                                  3
 #define YMin                                                   1
 #define XMax          X1Box + (LenBox * NumBox) + 2 + LenKey + 3
 #define YMax                                  Y1Box + NumBox + 1
 #define X1Key                      X1Box + (LenBox * NumBox) + 2
 #define X2Key             X1Box + (LenBox * NumBox) + 2 + LenKey
 #define YKey                                            YMin + 2

 extern unsigned char VID;

 unsigned char *MC;
 unsigned char *BR;

 unsigned char GetXZoneSetColor(unsigned char X)
 {
  return(X + XMax);
 }

 unsigned char GetYZoneSetColor(unsigned char Y)
 {
  return(Y + YMax);
 }

 void GetZoneSetColor(unsigned char X, unsigned char Y, unsigned char *XM, unsigned char *YM)
 {
  *XM = X + XMax;
  *YM = Y + YMax;
 }

 void PutSetColor(unsigned char X, unsigned char Y, unsigned char *Correct, unsigned char *Defaut, unsigned char *Oct, unsigned char *Dec, unsigned char *Hex, unsigned char *Annule, unsigned char *Info, unsigned char *Aide)
 {
  unsigned char I,J,Color,TX,TY,VY;
  unsigned char Chn[15],N15[3];
  VY = Y + (YMax - 1);
  if(VID == 0)
  {
   MEM__PutFillBorder(X,Y+YMin,X+XMax,Y+YMax);
   PutVideoKeyText(X+X1Key,Y+YKey,X+X2Key,Correct);    // Correct     //
   PutVideoKeyText(X+X1Key,Y+YKey+2,X+X2Key,Defaut);   // Defaut      //
   PutVideoKeyText(X+X1Key,Y+YKey+4,X+X2Key,Oct);      // Octal       //
   PutVideoKeyText(X+X1Key,Y+YKey+6,X+X2Key,Hex);      // Hexad‚cimal //
   PutVideoKeyText(X+X1Key,Y+YKey+8,X+X2Key,Annule);   // Annuler     //
   PutVideoKeyText(X+X1Key,Y+YKey+10,X+X2Key,Info);    // Information //
   PutVideoKeyText(X+X1Key,Y+YKey+12,X+X2Key,Aide);    // Aide        //
   Y += Y1Box;
   for(I = 0; I < NumBox; I++)
   {
    TY    = I + Y;
    _Dec15Chn(I,Chn);
    MEM__WriteText(X + (3 - strlen(Chn)),TY,Chn);
    MEM__WriteText(X + X1Box + (3 - strlen(Chn)) + (I * LenBox),VY,Chn);
    for(J = 0; J < NumBox; J++)
    {
     Color = J + (I << 4);
     Dec255Chn(Color,Chn);
     MEM_WriteText((J * LenBox) + X + X1Box,TY,Chn,Color);
    }
   }
  }
   else
  {
   BIOS_SetFillBorder_(X,Y+YMin,X+XMax,Y+YMax);
   PutVideoKeyText(X+X1Key,Y+YKey,X+X2Key,Correct);    // Correct     //
   PutVideoKeyText(X+X1Key,Y+YKey+2,X+X2Key,Defaut);   // Defaut      //
   PutVideoKeyText(X+X1Key,Y+YKey+4,X+X2Key,Oct);      // Octal       //
   PutVideoKeyText(X+X1Key,Y+YKey+6,X+X2Key,Hex);      // Hexad‚cimal //
   PutVideoKeyText(X+X1Key,Y+YKey+8,X+X2Key,Annule);   // Annuler     //
   PutVideoKeyText(X+X1Key,Y+YKey+10,X+X2Key,Info);    // Information //
   PutVideoKeyText(X+X1Key,Y+YKey+12,X+X2Key,Aide);    // Aide        //
   Y += Y1Box;
   for(I = 0; I < NumBox; I++)
   {
    TY    = I + Y;
    _Dec15Chn(I,Chn);
    BIOS_WriteText_(X + (3 - strlen(Chn)),TY,Chn);
    BIOS_WriteText_(X + X1Box + (3 - strlen(Chn)) + (I * LenBox),VY,Chn);
    for(J = 0; J < NumBox; J++)
    {
     Color = J + (I << 4);
     Dec255Chn(Color,Chn);
     BIOS_WriteText((J * LenBox) + X + X1Box,TY,Chn,Color);
    }
   }
  }
 }

 void MainSetColor(unsigned char X, unsigned char Y, unsigned char *Titre, unsigned char *Correct, unsigned char *Defaut, unsigned char *Oct, unsigned char *Dec, unsigned char *Hex, unsigned char *Annule, unsigned char *Info, unsigned char *Aide, unsigned char CB, unsigned char ColPos, unsigned char BC, unsigned char *Color)
 {
   // D‚finition des constantes //
  const ABin    = 1;
  const ADec    = 0;
  const AHex    = 1;
  const AOct    = 1;
  const XBin    = X1Key;
  const XOct    = X1Key + 5;
  const XDec    = X1Key;
  const XHex    = X1Key + 6;
  const YBin    = YMax-3;
  const YOct    = YMax-2;
  const YDec    = YMax-1;
  const YHex    = YMax-1;
  const X1Ptr   = X1Box - 1;
  const X2Ptr   = X1Box + 3;
  const Y1Ptr   = Y1Box - 1;
  const Y2Ptr   = Y1Box + 1;
   // D‚finition des variables locals //
  TypeCadre     Cadre = {'Û','Û','Û',' ',' ',' ',' ',' '};
  TypeCadre     CadNo = {'Ú','Ä','¿','³','³','À','Ä','Ù'};
  unsigned char Chn[10];
  unsigned char Buffer[30];
  unsigned char CX,CY;
  unsigned int  K;
   // Fixe les valeurs de base //
  CX = *Color % NumBox;
  CY = *Color / NumBox;
   // Fonction elle-mˆme //
  SetBorderFormat(Cadre);
  BarSpaceHori(X,Y,X+XMax,CB);
  WriteText(X+((XMax-strlen(Titre)) / 2),Y,Titre,CB);
  PutSetColor(X,Y,Correct,Defaut,Oct,Dec,Hex,Annule,Info,Aide);
  FillBox(X+XBin,Y+YOct,X+XBin+7,Y+YHex,'0',ColPos);
  SetBorderFormat(CadNo);
  SaveBox(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,Buffer);
  PutEmptyBorder(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,BC);
  if(ABin == 1)
  {
   Bin255Chn(*Color,Chn);
   WriteText(X+XBin,Y+YBin,Chn,ColPos);
   _SetCube(X+XBin+8,Y+YBin,'b');
  }
  if(AOct == 1)
  {
   Oct255Chn(*Color,Chn);
   WriteText(X+XOct,Y+YOct,Chn,ColPos);
   _SetCube(X+XOct+3,Y+YOct,'o');
  }
  if(ADec == 1)
  {
   Dec255Chn(*Color,Chn);
   WriteText(X+XDec,Y+YDec,Chn,ColPos);
  }
  if(AHex == 1)
  {
   Hex255Chn(*Color,Chn);
   WriteText(X+XHex,Y+YHex,Chn,ColPos);
   _SetCube(X+XHex+2,Y+YHex,'h');
  }
  do
   {
    ShowPtr();
    K = BIOS_ReadKey();
    HidePtr();
    if(K == kbUp)
    {
     PutBox(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,Buffer);
     CY = (CY - 1) & (NumBox - 1);
     SaveBox(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,Buffer);
     PutEmptyBorder(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,BC);
     if(ABin == 1)
     {
      Bin15Chn(CY,Chn);
      WriteText(X+XBin,Y+YBin,Chn,ColPos);
     }
     if(AOct == 1)
     {
      Oct255Chn(CX + (CY * NumBox),Chn);
      WriteText(X+XOct,Y+YOct,Chn,ColPos);
     }
     if(ADec == 1)
     {
      Dec255Chn(CX + (CY * NumBox),Chn);
      WriteText(X+XDec,Y+YDec,Chn,ColPos);
     }
     if(AHex == 1)
     {
      SetCube(X+XHex,Y+YHex,DataHex[CY],ColPos);
     }
    }
     else
    if(K == kbDown)
    {
     PutBox(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,Buffer);
     CY = (CY + 1) & (NumBox - 1);
     SaveBox(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,Buffer);
     PutEmptyBorder(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,BC);
     if(ABin == 1)
     {
      Bin15Chn(CY,Chn);
      WriteText(X+XBin,Y+YBin,Chn,ColPos);
     }
     if(AOct == 1)
     {
      Oct255Chn(CX + (CY * NumBox),Chn);
      WriteText(X+XOct,Y+YOct,Chn,ColPos);
     }
     if(ADec == 1)
     {
      Dec255Chn(CX + (CY * NumBox),Chn);
      WriteText(X+XDec,Y+YDec,Chn,ColPos);
     }
     if(AHex == 1)
     {
      SetCube(X+XHex,Y+YHex,DataHex[CY],ColPos);
     }
    }
     else
    if(K == kbLeft)
    {
     PutBox(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,Buffer);
     CX = (CX - 1) & (NumBox - 1);
     SaveBox(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,Buffer);
     PutEmptyBorder(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,BC);
     if(ABin == 1)
     {
      Bin15Chn(CX,Chn);
      WriteText(X+XBin+4,Y+YBin,Chn,ColPos);
     }
     if(AOct == 1)
     {
      Oct255Chn(CX + (CY * NumBox),Chn);
      WriteText(X+XOct,Y+YOct,Chn,ColPos);
     }
     if(ADec == 1)
     {
      Dec255Chn(CX + (CY * NumBox),Chn);
      WriteText(X+XDec,Y+YDec,Chn,ColPos);
     }
     if(AHex == 1)
     {
      SetCube(X+XHex+1,Y+YHex,DataHex[CX],ColPos);
     }
    }
     else
    if(K == kbRight)
    {
     PutBox(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,Buffer);
     CX = (CX + 1) & (NumBox - 1);
     SaveBox(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,Buffer);
     PutEmptyBorder(X+CX*LenBox+X1Ptr,Y+CY+Y1Ptr,X+CX*LenBox+X2Ptr,Y+CY+Y2Ptr,BC);
     if(ABin == 1)
     {
      Bin15Chn(CX,Chn);
      WriteText(X+XBin+4,Y+YBin,Chn,ColPos);
     }
     if(AOct == 1)
     {
      Oct255Chn(CX + (CY * NumBox),Chn);
      WriteText(X+XOct,Y+YOct,Chn,ColPos);
     }
     if(ADec == 1)
     {
      Dec255Chn(CX + (CY * NumBox),Chn);
      WriteText(X+XDec,Y+YDec,Chn,ColPos);
     }
     if(AHex == 1)
     {
      SetCube(X+XHex+1,Y+YHex,DataHex[CX],ColPos);
     }
    }
   }
  while((K != kbEnter)&&(K != kbEsc));
  if(K == kbEnter) *Color = CX + (CY << 4);
 }

 void SetMenuSetColor(unsigned char *Modele, unsigned char *Search, unsigned char *Help, unsigned char *MenuChoix, unsigned char *BarRemarque)
 {
  MC = MenuChoix;
  BR = BarRemarque;
 }

#endif