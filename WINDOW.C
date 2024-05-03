/********************************************************************/
/*                                                                  */
/*                        Malte System/Windows                      */
/*                             1992/07/01                           */
/*                                                                  */
/*           Copyright (C) par les Chevaliers de Malte              */
/*                                                                  */
/********************************************************************/

#ifndef __Malte_Video_Text_Windows__
 #define __Malte_Video_Text_Windows__

 #include <VIDEO\TEXT\WINDOW.H>
 #include <VIDEO\TEXT\DIRECT.H>
 #include <VIDEO\TEXT\BIOS.H>
 #include <VIDEO\TEXT\TEXT.H>

 extern struct {
                Byte Methode;
               } 
               VC;
 extern struct {
                Byte Borde[7];
                Byte ColorNor;
               }
               VD;
 extern struct {
                Byte Borde[7];
                Byte ColorNor;
               }
               VB;

  // D‚finition des variables //

 #ifndef __PASCAL__
  Byte WX1 = 0;
  Byte WY1 = 0;
  Byte WX2 = 79;
  Byte WY2 = 24;
  Byte WXS = 79;
  Byte WYS = 24;
  Byte WX  = 0;
  Byte WY  = 0;
 #else
  extern Byte WX1;
  extern Byte WY1;
  extern Byte WX2;
  extern Byte WY2;
  extern Byte WXS;
  extern Byte WYS;
  extern Byte WX;
  extern Byte WY;
 #endif

  // D‚finition des proc‚dures locals //

 void GetXY_W(Byte *X, Byte *Y)
 {
  *X = WX;
  *Y = WY;
 }

 void SetXY_W(Byte X, Byte Y)
 {
  WX = X + WX1;
  WY = Y + WY1;
  if(WX > WX2)
  {
   WX = WX1;
   WY++;
   if(WY > WY2)
   {
    WY = WY1;
   }
  }
 }

 void SetXY_W_(Byte X, Byte Y)
 {
  WX = X;
  WY = Y;
  if(WX > WX2)
  {
   WX = WX1;
   WY++;
   if(WY > WY2)
   {
    WY = WY1;
   }
  }
 }

 void SetWindow_W(Byte X1, Byte Y1, Byte X2, Byte Y2)
 {
  WX1 = X1;
  WY1 = Y1;
  WX2 = X2;
  WY2 = Y2;
  if(WX1 > WX2) ChgChr(&WX1,&WX2);
  if(WY1 > WY2) ChgChr(&WY1,&WY2);
  WX  = WX1;
  WY  = WY1;
  WXS = WX2 - WX1;
  WYS = WY2 - WY1;
 }

 void SetNormalWindow_W(void)
 {
  WX1 = 0;
  WY1 = 0;
  WX2 = GetMaxX();
  WY2 = GetMaxY();
  WX  = 0;
  WY  = 0;
  WXS = WX2;
  WYS = WY2;
 }

 void WriteChar_W(Byte C)
 {
  if(WX > WX2)
  {
   WX = 0;
   WY++;
   if(WY > WY2)
   {
    WY = WY1;
   }
  }
  _SetCube(WX,WY,C);
  WX++;
  if(WX > WX2)
  {
   WX = WX1;
   WY++;
   if(WY > WY2)
   {
    WY = WY1;
   }
  }
 }

 void WriteCharXY_W(Byte X, Byte Y, Byte C)
 {
  WX = X + WX1;
  WY = Y + WY1;
  if(WX > WX2)
  {
   WX = WX1;
   WY++;
   if(WY > WY2)
   {
    WY = WY1;
   }
  }
  _SetCube(WX,WY,C);
  WX++;
  if(WX > WX2)
  {
   WX = WX1;
   WY++;
   if(WY > WY2)
   {
    WY = WY1;
   }
  }
 }

 void WriteCharXY_W_(Byte X, Byte Y, Byte C)
 {
  WX = X;
  WY = Y;
  if(WX > WX2)
  {
   WX = WX1;
   WY++;
   if(WY > WY2)
   {
    WY = WY1;
   }
  }
  _SetCube(WX,WY,C);
  WX++;
  if(WX > WX2)
  {
   WX = WX1;
   WY++;
   if(WY > WY2)
   {
    WY = WY1;
   }
  }
 }

 #ifndef __PASCAL__

  void WriteText_W(Byte *P)
  {
   Word I;
   for(I = 0; P[I]; I++) WriteChar_W(P[I]);
  }

  void WriteTextLn_W(Byte *P)
  {
   WriteText_W(P);
   if(WY == WYS)
   {
    if(VID == 0) _BH = CN;
            else _BH = BIOS_CN;
    asm MOV AX,0x0701;
    asm MOV CL,WX1;
    asm MOV CH,WY1;
    asm MOV DL,WX2;
    asm MOV DH,WY2;
    asm INT 0x10;
   }
    else
   WY++;
  }

  void WindowRepeatText_W(Byte *P)
  {
   Byte TR,I;
   for(TR=((WX2-WX1+1)*(WY2-WY1+1))/strlen(P),WX=WX1,WY=WY1,I=1; I<=TR; I++)
   {
    WriteText_W(P);
   }
  }

 #else

  void WriteText_W(String P)
  {
   Word I;
   for(I = 1; P[0] <= I; I++) WriteChar_W(P[I]);
  }

  void WriteTextLn_W(String P)
  {
   WriteText_W(P);
   if(WY == WYS) BIOS_ScrollUp_(WX1,WY1,WX2,WY2,(VC.Methode == 0 ? VD.ColorNor : VB.ColorNor));
            else WY++;
  }

  void WindowRepeatText_W(String P)
  {
   Byte TR,I;
   for(TR=((WX2-WX1+1)*(WY2-WY1+1))/P[0],WX=WX1,WY=WY1,I=1; I<=TR; I++)
   {
    WriteText_W(P);
   }
  }

 #endif

 void BarTextHori_W(Byte X1, Byte Y, Byte X2, Byte Char)
 {
  Byte I;
  SetXY_W(X1,Y);
  for(I = X1; I <= X2; I++)
  {
   WriteChar_W(Char);
  }
 }

 void BarTextHori_W_(Byte X1, Byte Y, Byte X2, Byte Char)
 {
  Byte I;
  SetXY_W(X1,Y);
  for(I = X1; I <= X2; I++)
  {
   WriteChar_W(Char);
  }
 }

 void BarTextVert_W(Byte X, Byte Y1, Byte Y2, Byte Char)
 {
  Byte I;
  for(I = Y1; I <= Y2; I++)
  {
   WriteCharXY_W(X,I,Char);
  }
 }

 void BarTextVert_W_(Byte X, Byte Y1, Byte Y2, Byte Char)
 {
  Byte I;
  for(I = Y1; I <= Y2; I++)
  {
   WriteCharXY_W_(X,I,Char);
  }
 }

 void PutEmptyBorder_W(Byte X1, Byte Y1, Byte X2, Byte Y2)
 {
  if(X1 > X2) ChgChr(&X1,&X2);
  if(Y1 > Y2) ChgChr(&Y1,&Y2);
  if(VC.Methode == 0)
  {
   WriteCharXY_W_(X1,Y1,VD.Borde[0]);
   BarTextHori_W_(X1+1,Y1,X2-1,VD.Borde[1]);
   WriteChar_W(VD.Borde[2]);
   BarTextVert_W_(X1,Y1+1,Y2-1,VD.Borde[3]);
   BarTextVert_W_(X2,Y1+1,Y2-1,VD.Borde[4]);
   WriteCharXY_W_(X1,Y2,VD.Borde[5]);
   BarTextHori_W_(X1+1,Y2,X2-1,VD.Borde[6]);
   WriteChar_W(VD.Borde[7]);
  }
   else
  {
   WriteCharXY_W(X1,Y1,VB.Borde[0]);
   BarTextHori_W_(X1+1,Y1,X2-1,VB.Borde[1]);
   WriteChar_W(VB.Borde[2]);
   BarTextVert_W_(X1,Y1+1,Y2-1,VB.Borde[3]);
   BarTextVert_W_(X2,Y1+1,Y2-1,VB.Borde[4]);
   WriteCharXY_W_(X1,Y2,VB.Borde[5]);
   BarTextHori_W_(X1+1,Y2,X2-1,VB.Borde[6]);
   WriteChar_W(VB.Borde[7]);
  }
 }

 void ClearZone_W(Byte X1, Byte Y1, Byte X2, Byte Y2)
 {
  if(X1 > X2) ChgChr(&X1,&X2);
  if(Y1 > Y2) ChgChr(&Y1,&Y2);
  if(X1 < WX1) X1 = WX1;
  if(Y1 < WY1) Y1 = WY1;
  if(X2 > WX2) X2 = WX2;
  if(Y2 > WY2) Y2 = WY2;
  if(VC.Methode == 0) MEM__ClearWindow(X1,Y1,X2,Y2);
	         else BIOS_ClearWindow_(X1,Y1,X2,Y2);
 }

 void PutFillBorder_W(Byte X1, Byte Y1, Byte X2, Byte Y2)
 {
  if(X1 > X2) ChgChr(&X1,&X2);
  if(Y1 > Y2) ChgChr(&Y1,&Y2);
  ClearZone_W(X1,Y1,X2,Y2);
  if(VC.Methode == 0)
  {
   WriteCharXY_W_(X1,Y1,VD.Borde[0]);
   BarTextHori_W_(X1+1,Y1,X2-1,VD.Borde[1]);
   WriteChar_W(VD.Borde[2]);
   BarTextVert_W_(X1,Y1+1,Y2-1,VD.Borde[3]);
   BarTextVert_W_(X2,Y1+1,Y2-1,VD.Borde[4]);
   WriteCharXY_W_(X1,Y2,VD.Borde[5]);
   BarTextHori_W_(X1+1,Y2,X2-1,VD.Borde[6]);
   WriteChar_W(VD.Borde[7]);
  }
   else
  {
   WriteCharXY_W_(X1,Y1,VB.Borde[0]);
   BarTextHori_W_(X1+1,Y1,X2-1,VB.Borde[1]);
   WriteChar_W(VB.Borde[2]);
   BarTextVert_W_(X1,Y1+1,Y2-1,VB.Borde[3]);
   BarTextVert_W_(X2,Y1+1,Y2-1,VB.Borde[4]);
   WriteCharXY_W_(X1,Y2,VB.Borde[5]);
   BarTextHori_W_(X1+1,Y2,X2-1,VB.Borde[6]);
   WriteChar_W(VB.Borde[7]);
  }
 }

#endif
