/*************************************************************/
/*                                                           */
/*                  Malte System/Put Message                 */
/*                         1992/07/12                        */
/*                                                           */
/*        Copyright (C) par les Chevaliers de Malte          */
/*                                                           */
/*************************************************************/

#ifndef __Malte_Video_Message__
 #define __Malte_Video_Message__

 #include <DOS.H>
 #include <STRING.H>
 #include <TRANSLTR.H>
 #include <KEYBOARD\KEYBOARD.H>
 #include <MOUSE\MOUSE.H>
 #include <VIDEO\KEYVIDEO.H>
 #include <VIDEO\TEXT.H>

 extern Byte WX1,WY1,WX2,WY2,WXS,WYS;

 extern Word XMouse,YMouse,ButtonMouse;

 Byte MergeTl = 4, YPosTl = 2, CIcon, *Icon = "";

 Byte GetLineMessage(Byte X1, Byte X2, Byte *P)
 {
  Byte XS = (X2-X1), AX, AY, Len = strlen(P); AY = 0; AX = 0;
 Deb:if(Len - AX >= XS)
  {
   Word I,J;
   for(I = AX + XS; (P[I] > 32) && (I > AX); I--);
   for(J = AX; J <= I; J++);
   AX = J; AY++;
   goto Deb;
  }
   else
  AY++;
  return(AY);
 }

 void _PutMessage(Byte X1, Byte Y1, Byte X2, Byte *P)
 {
  Byte XS = (X2-X1), AX, AY, Len = strlen(P); AY = Y1; AX = 0;
 Deb:if(Len - AX >= XS)
  {
   Word I,J;
   for(I = AX + XS; (P[I] > ' ') && (I > AX); I--);
   for(J = AX; J <= I; J++) _SetCube(X1+J-AX,AY,P[J]);
   AX = J; AY++;
   goto Deb;
  }
   else
  {
   Word J; for(J = AX; J <= strlen(P); J++) _SetCube(X1+J-AX,AY,P[J]);
  }
 }

 void _PutMessage_W(Byte *P)
 {
  Byte AX, AY, Len = strlen(P); AY = WY1; AX = 0;
 Deb:if(Len - AX >= WXS)
  {
   Word I,J;
   for(I = AX + WXS; (P[I] > 32) && (I > AX); I--);
   for(J = AX; J <= I; J++) _SetCube(WX1+J-AX,AY,P[J]);
   AX = J; AY++;
   goto Deb;
  }
   else
  {
   Word J, Len = strlen(P);
   for(J = AX; J <= Len; J++) _SetCube(WX1+J-AX,AY,P[J]);
  }
 }

 void PutMessage_W(Byte *P, Byte Color)
 {
  Byte AX, AY;
  AY = WY1; AX = 0;
 Deb:if(strlen(P) - AX >= WXS)
  {
   Word I,J;
   for(I = AX + WXS; (P[I] > 32) && (I > AX); I--);
   for(J = AX; J <= I; J++) SetCube(WX1+J-AX,AY,P[J],Color);
   AX = J; AY++;
   goto Deb;
  }
   else
  {
   Word J, Len = strlen(P);
   for(J = AX; J <= Len; J++) SetCube(WX1+J-AX,AY,P[J],Color);
  }
 }

 void PutMessage(Byte X1, Byte Y1, Byte X2, Byte *P, Byte Color)
 {
  Byte XS = (X2-X1), AX, AY, Len = strlen(P); AY = Y1; AX = 0;
 Deb:if(Len - AX >= XS)
  {
   Word I,J;
   for(I = AX + XS; (P[I] > 32) && (I > AX); I--);
   for(J = AX; J <= I; J++) SetCube(X1+J-AX,AY,P[J],Color);
   AX = J; AY++;
   goto Deb;
  }
   else
  {
   Word J, Len = strlen(P);
   for(J = AX; J <= Len; J++) SetCube(X1+J-AX,AY,P[J],Color);
  }
 }

 void _PutBoxMessage(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte *Tl, Byte *P, Byte CC, Byte CT)
 {
  Byte XS = (X2-X1), XM;
  PutFillBorder(X1,Y1,X2,Y2,CC);
  if(Tl[0] != 0)
  {
   WriteText(X1 + ((XS - strlen(Tl))/2),Y1+YPosTl,Tl,CT);
   XM = 0;
  }
   else
  XM = 2;
  _PutMessage(X1+2,Y1+MergeTl-XM,X2-2,P);
 }

 void _PutBoxMessage_W(Byte *Tl, Byte *P, Byte CC, Byte CT)
 {
  Byte XM;
  PutFillBorder(WX1,WY1,WX2,WY2,CC);
  if(Tl[0] != 0)
  {
   WriteText(WX1 + ((WXS - strlen(Tl))/2),WY1+YPosTl,Tl,CT);
   XM = 0;
  }
   else
  XM = 2; 
  _PutMessage(WX1+2,WY1+MergeTl-XM,WX2-2,P);
 }

 void PutBoxMessage(Byte X1, Byte Y1, Byte X2, Byte Y2, Byte *Tl, Byte *P, Byte CC, Byte CT, Byte CE)
 {
  Byte XS = (X2-X1), XM;
  PutFillBorder(X1,Y1,X2,Y2,CC);
  if(Tl[0] != 0)
  {
   WriteText(X1 + ((XS - strlen(Tl))/2),Y1+YPosTl,Tl,CT);
   XM = 0;
  }
   else
  XM = 2;
  PutMessage(X1+2,Y1+MergeTl-XM,X2-2,P,CE);
 }

 Byte PutBoxMessageKey(Byte X1, Byte Y, Byte X2, Byte Merge, Byte *Tl, Byte *P, Byte *Key, Byte CC, Byte CT, Byte CE, Byte *Buffer)
 {
  Byte XS = (X2-X1);
  Word SK = strlen(Key) + 4, K, Len = strlen(Tl),
       Y2 = Y + GetLineMessage(X1,X2,P) + 3 + Merge + YPosTl;
  SaveBox(X1,Y,X2+2,Y2+1,Buffer);
  PutFillBorder(X1,Y,X2,Y2,CC);
  if(Tl[0] != 0)
  {
   BarSelectHori(X1,Y,X2,CT);
   WriteText(X1,Y,Icon,CIcon);
   WriteText(X1 + ((XS - Len)/2),Y+YPosTl,Tl,CT);
  }
  PutMessage(X1+2,Y+MergeTl,X2-2,P,CE);
  _PutVideoKeyText(X1+((XS-SK)/2),Y2,X2-((XS-SK)/2),Key);
Rpt:K = ReadKey();
    if(K == kbEnter)
    {
     PutBox(X1,Y,X2+2,Y2+1,Buffer);
     return(0);
    }
    if(K == kbEsc)
    {
     PutBox(X1,Y,X2+2,Y2+1,Buffer);
     return(1);
    }
    goto Rpt;
 }

 Byte PutBoxMessageKeyMouse(Byte X1, Byte Y, Byte X2, Byte Merge, Byte *Tl, Byte *P, Byte *Key, Byte CC, Byte CT, Byte CE, Byte *Buffer)
 {
  Byte True, XS = (X2-X1);
  Word SK = strlen(Key) + 4, K, Y2 = Y+GetLineMessage(X1,X2,P)+3+Merge+YPosTl;
  SaveBox(X1,Y,X2+2,Y2+1,Buffer);
  PutFillBorder(X1,Y,X2,Y2,CC);
  if(Tl[0] != 0)
  {
   BarSelectHori(X1,Y,X2,CT);
   WriteText(X1,Y,Icon,CIcon);
   WriteText(X1 + ((XS - strlen(Tl))/2),Y+YPosTl,Tl,CT);
  }
  PutMessage(X1+2,Y+MergeTl,X2-2,P,CE);
  _PutVideoKeyText(X1+((XS-SK)/2),Y2,X2-((XS-SK)/2),Key);
  do
   {
    ShowPtr();
    while(!KeyPressed())
    {
     GetButPos(&ButtonMouse,&XMouse,&YMouse);
     if(ButtonMouse > 0)
     {
      Byte XMs = (XMouse / 8), YMs = (YMouse / 8);
      if((XMs >= X1+((XS-SK)/2))&&(XMs <= X2-((XS-SK)/2)))
      {
       if(YMs == Y2)
       {
        HidePtr();
	SetCube(X1+((XS-SK)/2),Y2,' ',CC);
	_PutVideoKeyTextNoShade(X1+((XS-SK)/2)+1,Y2,X2-((XS-SK)/2)+1,Key);
	BarTextHori(X1+((XS-SK)/2)+1,Y2+1,X2-((XS-SK)/2)+1,' ',CC);
	ShowPtr();
	ReleaseKeyMouse();
	HidePtr();
	PutBox(X1,Y,X2+2,Y2+1,Buffer);
	return(0);
       }
      }
       else
      if(Icon[0] != 0)
      {
       if((XMs >= X1)&&(XMs <= X1+strlen(Icon)))
       {
	if(YMs == Y)
	{
	 HidePtr();
	 WriteText(X1,Y,Icon,CT);
	 ShowPtr();
	 ReleaseKeyMouse();
	 HidePtr();
	 PutBox(X1,Y,X2+2,Y2+1,Buffer);
	 return(1);
	}
       }
      }
     }
    }
    True = 0;
    HidePtr();
    K = ReadKey();
    if((K == kbEnter)||(K == kbEsc)) True = 1;
   }
  while(True != 1);
  Exit:
  PutBox(X1,Y,X2+2,Y2+1,Buffer);
  if(K == kbEnter) return(0);
  if(K  ==  kbEsc) return(1);
	      else return(255);
 }

 void PutBoxMessage_W(Byte *Tl, Byte *P, Byte CC, Byte CT, Byte CE)
 {
  Byte XM;
  PutFillBorder(WX1,WY1,WX2,WY2,CC);
  if(Tl[0] != 0)
  {
   WriteText(WX1 + ((WXS - strlen(Tl))/2),WY1+YPosTl,Tl,CT);
   XM = 0;
  }
   else
  XM = 2;
  PutMessage(WX1+2,WY1+MergeTl-XM,WX2-2,P,CE);
 }

 void SetYPosTitle(Byte Y)
 {
  YPosTl = Y;
 }

 void SetYPosText(Byte Y)
 {
  MergeTl = Y;
 }

 Byte GetYPosText(void)
 {
  return(MergeTl);
 }

 void SetIcon(Byte *P, Byte Color)
 {
  Icon = P; CIcon = Color;
 }

#endif