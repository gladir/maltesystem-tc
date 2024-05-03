/****************************************************************/
/*                                                              */
/*                        Malte System Input                    */
/*                            1992/07/08                        */
/*                                                              */
/*             Copyright (C) par les Chevalier de Malte         */
/*                                                              */
/****************************************************************/

#ifndef __Malte_Video_Input__
 #define __Malte_Video_Input__

 #include <DOS.H>
 #include <STRING.H>
 #include <STDLIB.H>
 #include <NUMERIC.H>

  // D괽init le syst둴e vid굊 Malte //

 #define __MALTE__
 #define __Keyboard__
 #define __Mouse__
 #define __VideoText__
 #define __VideoInput__
 #define __VideoRepeat__

 #include <MALTE.H>

  // D괽init les variables //

 extern Byte MON;

 Byte MinCursor = 6, MaxCursor = 7;
 Word ButtonMouse = 0, XMouse = 0, YMouse = 0;

 PutSpcIf0(Byte Value, Byte X, Byte Y, Byte Color)
 {
  if(Value == 0) SetCube(X,Y,' ',Color);
 }

 void _InputNotArrow(Byte *T, Word Max)
 {
  Word I, K; Byte XS,YS,XP;
  for(I = 0;I <= Max;I++) T[I] = 0;
  GetPos(&XS,&YS);
  _BarSpaceHori(XS,YS,XS+Max-1);
  SetPosCursor(XS,YS);
  SetCursor(MinCursor,MaxCursor);
  XP = 0;
  do
   {
    K = ReadKey();
    if(K == kbBack)
    {
     if(XP > 0)
     {
      T[XP--] = 0;
      _SetCube(XS+XP,YS,' ');
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if((Lo(K) != 0) && (Lo(K) > 31))
    {
     if(XP < Max)
     {
      _SetCube(XS+XP,YS,Lo(K));
      T[XP++] = Lo(K);
      SetPosCursor(XS+XP,YS);
     }
    }
   }
  while (K != kbEnter);
 }

 void InputNotArrow(Byte *T, Word Max, Byte Color)
 {
  Word I,K; Byte XS,YS,XP;
  for(I = 0;I <= Max;I++) T[I] = 0;
  GetPos(&XS,&YS);
  BarSpaceHori(XS,YS,XS+Max-1,Color);
  SetPosCursor(XS,YS);
  SetCursor(MinCursor,MaxCursor);
  XP = 0;
  do
   {
    K = ReadKey();
    if(K == kbBack)
    {
     if(XP > 0)
     {
      T[XP--] = 0;
      SetCube(XS+XP,YS,' ',Color);
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if((Lo(K) != 0) && (Lo(K) > 31))
    {
     if(XP < Max)
     {
      SetCube(XS+XP,YS,Lo(K),Color);
      T[XP++] = Lo(K);
      SetPosCursor(XS+XP,YS);
     }
    }
   }
  while (K != kbEnter);
 }

 Word InputXY(Byte XS, Byte YS, Word XP, Byte *T, Word Max, Byte Color)
 {
  Word K, I, LS = strlen(T); unsigned Ok;
  if(XP > LS) XP = 0;
  BarSpaceHori(XS,YS,XS+Max-1,Color);
  WriteText(XS,YS,T,Color);
  SetPosCursor(XS+XP,YS);
  SetCursor(MinCursor,MaxCursor);
  do
   {
    Ok = 0;
    K = ReadKey();
    if(K == kbBack)
    {
     Ok = 1;
     if(XP > 0)
     {
      if(XP == LS)
      {
       T[XP--] = 0; LS--;
       SetCube(XS+XP,YS,' ',Color);
       SetPosCursor(XS+XP,YS);
      }
       else
      {
       for(I = XP;I <= LS; I++)
       {
    T[I-1] = T[I];
    SetCube(XS+I-1,YS,T[I],Color);
       }
       SetCube(XS+LS,YS,' ',Color);
       XP--; T[LS--] = 0;
       SetPosCursor(XS+XP,YS);
      }
     }
    }
     else
    if(K == kbDel)
    {
     Ok = 1;
     if((LS != 0)&&(LS != XP))
     {
      for(I = XP; I < LS; I++)
      {
       T[I] = T[I+1];
       SetCube(XS+I,YS,T[I],Color);
      }
      T[LS--] = 0;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbLeft)
    {
     Ok = 1;
     if(XP > 0)
     {
      XP--;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbRight)
    {
     Ok = 1;
     if(XP < LS)
     {
      XP++;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbHome)
    {
     Ok = 1; XP = 0;
     SetPosCursor(XS,YS);
    }
     else
    if(K == kbEnd)
    {
     Ok = 1; XP = LS;
     SetPosCursor(XS+XP,YS);
    }
     else
    if(K == kbIns) Ok = 1;
     else
    if((Lo(K) != 0) && (Lo(K) > 31))
    {
     Ok = 1;
     if(GetModeInsert() == 0)
     {
      if(LS < Max)
      {
       SetCube(XS+XP,YS,Lo(K),Color);
       if(XP == LS) LS++;
       T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
      else
     {
      if(LS == 0)
      {
       SetCube(XS,YS,Lo(K),Color);
       T[0] = Lo(K); T[1] = 0; LS = 1; XP = 1;
       SetPosCursor(XS+1,YS);
      }
       else
      if(LS == XP)
      {
       if(LS < Max)
       {
	SetCube(XS+XP,YS,Lo(K),Color);
    LS++; T[XP++] = Lo(K);
	SetPosCursor(XS+XP,YS);
       }
      }
       else
      if(LS < Max)
      {
       for(I = LS;I >= XP; I--)
       {
    T[I+1] = T[I];
    SetCube(XS+I+1,YS,T[I],Color);
       }
       SetCube(XS+XP,YS,Lo(K),Color);
       LS++; T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
    }
   }
  while (Ok == 1);
  return(K);
 }

 Word InputXYMouse(Byte XS, Byte YS, Word XP, Byte *T, Word Max, Byte Color)
 {
  Word K, I, LS = strlen(T); unsigned Ok;
  if(XP > LS) XP = 0;
  BarSpaceHori(XS,YS,XS+Max-1,Color);
  WriteText(XS,YS,T,Color);
  SetPosCursor(XS+XP,YS);
  SetCursor(MinCursor,MaxCursor);
  do
   {
    ShowPtr();
    while(!KeyPressed())
    {
     GetButPos(&ButtonMouse,&XMouse,&YMouse);
     if(ButtonMouse > 0)
     {
      Byte YMs = (YMouse / 8);
      if(YMs == YS)
      {
       Byte XMs = (XMouse / 8);
       if((XMs >= XS)&&(XMs <= XS + LS))
       {
	XP = XMs - XS;
	SetPosCursor(XS+XP,YS);
	ReleaseKeyMouse();
	ButtonMouse = 0;
       }
	else
       {
	ReleaseKeyMouse();
	HidePtr();
	goto Exit;
       }
      }
       else
      {
       ReleaseKeyMouse();
       HidePtr();
       goto Exit;
      }
     }
    }
    Ok = 0;
    HidePtr();
    K = ReadKey();
    if(K == kbBack)
    {
     Ok = 1;
     if(XP > 0)
     {
      if(XP == LS)
      {
       T[XP--] = 0; LS--;
       SetCube(XS+XP,YS,' ',Color);
       SetPosCursor(XS+XP,YS);
      }
       else
      {
       for(I = XP;I <= LS; I++)
       {
    T[I-1] = T[I];
    SetCube(XS+I-1,YS,T[I],Color);
       }
       SetCube(XS+LS,YS,' ',Color);
       XP--; T[LS--] = 0;
       SetPosCursor(XS+XP,YS);
      }
     }
    }
     else
    if(K == kbDel)
    {
     Ok = 1;
     if((LS != 0)&&(LS != XP))
     {
      for(I = XP;I < LS; I++)
      {
       T[I] = T[I+1];
       SetCube(XS+I,YS,T[I],Color);
      }
      T[LS--] = 0;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbLeft)
    {
     Ok = 1;
     if(XP > 0)
     {
      XP--;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbRight)
    {
     Ok = 1;
     if(XP < LS)
     {
      XP++;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbHome)
    {
     Ok = 1; XP = 0;
     SetPosCursor(XS,YS);
    }
     else
    if(K == kbEnd)
    {
     Ok = 1; XP = LS;
     SetPosCursor(XS+XP,YS);
    }
     else
    if(K == kbIns) Ok = 1;
     else
    if((Lo(K) != 0) && (Lo(K) > 31))
    {
     Ok = 1;
     if(GetModeInsert() == 0)
     {
      if(LS < Max)
      {
       SetCube(XS+XP,YS,Lo(K),Color);
       if(XP == LS) LS++;
       T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
      else
     {
      if(LS == 0)
      {
       SetCube(XS,YS,Lo(K),Color);
       T[0] = Lo(K); T[1] = 0; LS = 1; XP = 1;
       SetPosCursor(XS+1,YS);
      }
       else
      if(LS == XP)
      {
       if(LS < Max)
       {
	SetCube(XS+XP,YS,Lo(K),Color);
    LS++; T[XP++] = Lo(K);
	SetPosCursor(XS+XP,YS);
       }
      }
       else
      if(LS < Max)
      {
       for(I = LS;I >= XP; I--)
       {
    T[I+1] = T[I];
    SetCube(XS+I+1,YS,T[I],Color);
       }
       SetCube(XS+XP,YS,Lo(K),Color);
       LS++; T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
    }
    T[LS] = 0;
   }
  while (Ok == 1);
 Exit:
  if(ButtonMouse > 0) return(0xFFFF-ButtonMouse); else return(K);
 }

 Word InputXYMouse__(Byte XS, Byte YS, Word *XP, Byte *T, Word Max,
		     Word kbCursorLeft, Word kbCursorRight,
		     Word kbCursorHome, Word kbCursorEnd,
		     Word kbDelChar,    Word kbBackChar,
		     Word kbClearLine,
		     Byte Color)
 {
  Word K,I,LS = strlen(T); unsigned Ok;
  if(XP[0] > LS) XP[0] = 0;
  BarSpaceHori(XS,YS,XS+Max-1,Color);
  WriteText(XS,YS,T,Color);
  SetPosCursor(XS+XP[0],YS);
  SetCursor(MinCursor,MaxCursor);
  do
   {
    ShowPtr();
    while(!KeyPressed())
    {
     GetButPos(&ButtonMouse,&XMouse,&YMouse);
     if(ButtonMouse > 0)
     {
      Byte YMs = (YMouse / 8);
      if(YMs == YS)
      {
       Byte XMs = (XMouse / 8);
       if((XMs >= XS)&&(XMs <= XS + LS))
       {
	XP[0] = XMs - XS;
	SetPosCursor(XS+XP[0],YS);
	ReleaseKeyMouse();
	ButtonMouse = 0;
       }
	else
       {
	ReleaseKeyMouse();
	HidePtr();
	goto Exit;
       }
      }
       else
      {
       ReleaseKeyMouse();
       HidePtr();
       goto Exit;
      }
     }
    }
    Ok = 0;
    HidePtr();
    K = ReadKey();
    if((K == kbBack)||(K == kbBackChar))
    {
     Ok = 1;
     if(XP[0] > 0)
     {
      if(XP[0] == LS)
      {
       T[XP[0]--] = 0; LS--;
       SetCube(XS+XP[0],YS,' ',Color);
       SetPosCursor(XS+XP[0],YS);
      }
       else
      {
       for(I = XP[0];I <= LS; I++)
       {
    T[I-1] = T[I];
    SetCube(XS+I-1,YS,T[I],Color);
       }
       SetCube(XS+LS,YS,' ',Color);
       XP[0]--; T[LS--] = 0;
       SetPosCursor(XS+XP[0],YS);
      }
     }
    }
     else
    if((K == kbDel)||(K == kbDelChar))
    {
     Ok = 1;
     if((LS != 0)&&(LS != XP[0]))
     {
      for(I = XP[0];I < LS; I++)
      {
       T[I] = T[I+1];
       SetCube(XS+I,YS,T[I],Color);
      }
      T[LS--] = 0;
      SetPosCursor(XS+XP[0],YS);
     }
    }
     else
    if((K == kbLeft)||(K == kbCursorLeft))
    {
     Ok = 1;
     if(XP[0] > 0)
     {
      XP[0]--;
      SetPosCursor(XS+XP[0],YS);
     }
    }
     else
    if((K == kbRight)||(K == kbCursorRight))
    {
     Ok = 1;
     if(XP[0] < LS)
     {
      XP[0]++;
      SetPosCursor(XS+XP[0],YS);
     }
    }
     else
    if((K == kbHome)||(K == kbCursorHome))
    {
     Ok = 1; XP[0] = 0;
     SetPosCursor(XS,YS);
    }
     else
    if((K == kbEnd)||(K == kbCursorEnd))
    {
     Ok = 1; XP[0] = LS;
     SetPosCursor(XS+XP[0],YS);
    }
     else
    if(K == kbIns) Ok = 1;
     else
    if(K == kbClearLine)
    {
     Ok = 1; T[0] = 0; XP[0] = 0; LS = 0;
     SetPosCursor(XS,YS);
     BarSpaceHori(XS,YS,XS+Max-1,Color);
    }
     else
    if((Lo(K) != 0) && (Lo(K) > 31))
    {
     Ok = 1;
     if(GetModeInsert() == 0)
     {
      if(LS < Max)
      {
       SetCube(XS+XP[0],YS,Lo(K),Color);
       if(XP[0] == LS) LS++;
       T[XP[0]++] = Lo(K);
       SetPosCursor(XS+XP[0],YS);
      }
     }
      else
     {
      if(LS == 0)
      {
       SetCube(XS,YS,Lo(K),Color);
       T[0] = Lo(K); T[1] = 0; LS = 1; XP[0] = 1;
       SetPosCursor(XS+1,YS);
      }
       else
      if(LS == XP[0])
      {
       if(LS < Max)
       {
	SetCube(XS+XP[0],YS,Lo(K),Color);
    LS++; T[XP[0]++] = Lo(K);
	SetPosCursor(XS+XP[0],YS);
       }
      }
       else
      if(LS < Max)
      {
       for(I = LS;I >= XP[0]; I--)
       {
    T[I+1] = T[I];
    SetCube(XS+I+1,YS,T[I],Color);
       }
       SetCube(XS+XP[0],YS,Lo(K),Color);
       LS++; T[XP[0]++] = Lo(K);
       SetPosCursor(XS+XP[0],YS);
      }
     }
    }
    T[LS] = 0;
   }
  while (Ok == 1);
 Exit:
  if(ButtonMouse > 0) return(0xFFFF-ButtonMouse); else return(K);
 }

 Word _InputXYMouse(Byte XS, Byte YS, Word XP, Byte *T, Word Max)
 {
  Word K, I, LS = strlen(T); Byte Ok;
  if(XP > LS) XP = 0;
  _BarSpaceHori(XS,YS,XS+Max-1);
  _WriteText(XS,YS,T);
  SetPosCursor(XS+XP,YS);
  SetCursor(MinCursor,MaxCursor);
  do
   {
    ShowPtr();
    while(!KeyPressed())
    {
     GetButPos(&ButtonMouse,&XMouse,&YMouse);
     if(ButtonMouse > 0)
     {
      Byte YMs = (YMouse / 8);
      if(YMs == YS)
      {
       Byte XMs = (XMouse / 8);
       if((XMs >= XS)&&(XMs <= XS + LS))
       {
	XP = XMs - XS;
	SetPosCursor(XS+XP,YS);
	ReleaseKeyMouse();
	ButtonMouse = 0;
       }
	else
       {
	ReleaseKeyMouse();
	HidePtr();
	goto Exit;
       }
      }
       else
      {
       ReleaseKeyMouse();
       HidePtr();
       goto Exit;
      }
     }
    }
    Ok = 0;
    HidePtr();
    K = ReadKey();
    if(K == kbBack)
    {
     Ok = 1;
     if(XP > 0)
     {
      if(XP == LS)
      {
       T[XP--] = 0; LS--;
       _SetCube(XS+XP,YS,' ');
       SetPosCursor(XS+XP,YS);
      }
       else
      {
       for(I = XP;I <= LS; I++)
       {
    T[I-1] = T[I];
    _SetCube(XS+I-1,YS,T[I]);
       }
       _SetCube(XS+LS,YS,' ');
       XP--; T[LS--] = 0;
       SetPosCursor(XS+XP,YS);
      }
     }
    }
     else
    if(K == kbDel)
    {
     Ok = 1;
     if((LS != 0)&&(LS != XP))
     {
      for(I = XP;I < LS; I++)
      {
       T[I] = T[I+1];
       _SetCube(XS+I,YS,T[I]);
      }
      T[LS--] = 0;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbLeft)
    {
     Ok = 1;
     if(XP > 0)
     {
      XP--;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbRight)
    {
     Ok = 1;
     if(XP < LS)
     {
      XP++;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbHome)
    {
     Ok = 1; XP = 0;
     SetPosCursor(XS,YS);
    }
     else
    if(K == kbEnd)
    {
     Ok = 1; XP = LS;
     SetPosCursor(XS+XP,YS);
    }
     else
    if(K == kbIns) Ok = 1;
     else
    if((Lo(K) != 0) && (Lo(K) > 31))
    {
     Ok = 1;
     if(GetModeInsert() == 0)
     {
      if(LS < Max)
      {
       _SetCube(XS+XP,YS,Lo(K));
       if(XP == LS) LS++;
       T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
      else
     {
      if(LS == 0)
      {
       _SetCube(XS,YS,Lo(K));
       T[0] = Lo(K); T[1] = 0; LS = 1; XP = 1;
       SetPosCursor(XS+1,YS);
      }
       else
      if(LS == XP)
      {
       if(LS < Max)
       {
	_SetCube(XS+XP,YS,Lo(K));
    LS++; T[XP++] = Lo(K);
	SetPosCursor(XS+XP,YS);
       }
      }
       else
      if(LS < Max)
      {
       for(I = LS;I >= XP; I--)
       {
    T[I+1] = T[I];
    _SetCube(XS+I+1,YS,T[I]);
       }
       _SetCube(XS+XP,YS,Lo(K));
       LS++; T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
    }
   }
  while (Ok == 1);
 Exit:
  if(ButtonMouse > 0) return(0xFFFF-ButtonMouse); else return(K);
 }

 Word _InputXY(Byte XS, Byte YS, Word XP, Byte *T, Word Max)
 {
  Word K, I, LS = strlen(T); Byte Ok;
  _BarSpaceHori(XS,YS,XS+Max-1);
  _WriteText(XS,YS,T);
  if(XP > LS) XP = 0;
  SetPosCursor(XS+XP,YS);
  SetCursor(MinCursor,MaxCursor);
  do
   {
    Ok = 0;
    K = ReadKey();
    if(K == kbBack)
    {
     Ok = 1;
     if(XP > 0)
     {
      if(XP == LS)
      {
       T[XP--] = 0; LS--;
       _SetCube(XS+XP,YS,' ');
       SetPosCursor(XS+XP,YS);
      }
       else
      {
       for(I = XP;I <= LS; I++)
       {
    T[I-1] = T[I]; _SetCube(XS+I-1,YS,T[I]);
       }
       _SetCube(XS+LS,YS,' ');
       XP--; T[LS--] = 0;
       SetPosCursor(XS+XP,YS);
      }
     }
    }
     else
    if(K == kbDel)
    {
     Ok = 1;
     if((LS != 0)&&(LS != XP))
     {
      for(I = XP;I < LS; I++)
      {
       T[I] = T[I+1];
       _SetCube(XS+I,YS,T[I]);
      }
      T[LS--] = 0;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbLeft)
    {
     Ok = 1;
     if(XP > 0)
     {
      XP--;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbRight)
    {
     Ok = 1;
     if(XP < LS)
     {
      XP++;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbHome)
    {
     Ok = 1; XP = 0;
     SetPosCursor(XS,YS);
    }
     else
    if(K == kbEnd)
    {
     Ok = 1; XP = LS;
     SetPosCursor(XS+XP,YS);
    }
     else
    if(K == kbIns) Ok = 1;
     else
    if((Lo(K) != 0) && (Lo(K) > 31))
    {
     Ok = 1;
     if(GetModeInsert() == 0)
     {
      if(LS < Max)
      {
       _SetCube(XS+XP,YS,Lo(K));
       if(XP == LS) LS++;
       T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
      else
     {
      if(LS == 0)
      {
       _SetCube(XS,YS,Lo(K));
       T[0] = Lo(K); T[1] = 0; LS = 1; XP = 1;
       SetPosCursor(XS+1,YS);
      }
       else
      if(LS == XP)
      {
       if(LS < Max)
       {
	_SetCube(XS+XP,YS,Lo(K));
    LS++; T[XP++] = Lo(K);
	SetPosCursor(XS+XP,YS);
       }
      }
       else
      if(LS < Max)
      {
       for(I = LS;I >= XP; I--)
       {
    T[I+1] = T[I];
    _SetCube(XS+I+1,YS,T[I]);
       }
       _SetCube(XS+XP,YS,Lo(K));
       LS++; T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
    }
   }
  while (Ok == 1);
  return(K);
 }

 Word _InputXY_(Byte XS, Byte YS, Byte *T, Word Max)
 {
  Word I; for(I = 0; I <= Max; I++) T[I] = 0;
  return(_InputXY(XS,YS,0,T,Max));
 }

 Word InputXY_(Byte XS, Byte YS, Byte *T, Word Max, Byte Color)
 {
  Word I; for(I = 0; I <= Max; I++) T[I] = 0;
  return(InputXY(XS,YS,0,T,Max,Color));
 }

 void SetInputCursor(Byte Min, Byte Max)
 {
  MinCursor = Min; MaxCursor = Max;
 }

 Word _PasswordXYMouse(Byte XS, Byte YS, Word XP, Byte *T, Word Max, Byte Mark)
 {
  Word K, I, LS = strlen(T); Byte Ok;
  _BarSpaceHori(XS,YS,XS+Max-1);
  if(LS > 0) _BarTextHori(XS,YS,XS+LS-1,Mark);
  if(XP > LS) XP = 0;
  SetPosCursor(XS+XP,YS);
  SetCursor(MinCursor,MaxCursor);
  do
   {
    ShowPtr();
    while(!KeyPressed())
    {
     GetButPos(&ButtonMouse,&XMouse,&YMouse);
     if(ButtonMouse > 0)
     {
      Byte YMs = (YMouse / 8);
      if(YMs == YS)
      {
       Byte XMs = (XMouse / 8);
       if((XMs >= XS)&&(XMs <= XS + LS))
       {
	XP = XMs - XS;
	SetPosCursor(XS+XP,YS);
	ReleaseKeyMouse();
	ButtonMouse = 0;
       }
	else
       {
	ReleaseKeyMouse();
	HidePtr();
	goto Exit;
       }
      }
       else
      {
       ReleaseKeyMouse();
       HidePtr();
       goto Exit;
      }
     }
    }
    Ok = 0;
    HidePtr();
    K = ReadKey();
    if(K == kbBack)
    {
     Ok = 1;
     if(XP > 0)
     {
      if(XP == LS)
      {
       T[XP--] = 0; LS--;
       _SetCube(XS+XP,YS,' ');
       SetPosCursor(XS+XP,YS);
      }
       else
      {
       for(I = XP;I <= LS; I++)
       {
    T[I-1] = T[I];
	_SetCube(XS+I-1,YS,Mark);
       }
       _SetCube(XS+LS,YS,' ');
       XP--; T[LS--] = 0;
       SetPosCursor(XS+XP,YS);
      }
     }
    }
    if(K == kbDel)
    {
     Ok = 1;
     if((LS != 0)&&(LS != XP))
     {
      for(I = XP;I < LS; I++)
      {
       T[I] = T[I+1];
       _SetCube(XS+I,YS,Mark);
      }
      T[LS--] = 0;
      _SetCube(XS+LS,YS,' ');
      SetPosCursor(XS+XP,YS);
     }
    }
    if(K == kbLeft) { Ok = 1; if(XP > 0) { XP--; SetPosCursor(XS+XP,YS);}}
    if(K == kbRight) { Ok = 1; if(XP < LS) { XP++; SetPosCursor(XS+XP,YS);}}
    if(K == kbHome) { Ok = 1; XP = 0; SetPosCursor(XS,YS); }
    if(K == kbEnd) { Ok = 1; XP = LS; SetPosCursor(XS+XP,YS); }
    if(K == kbIns) Ok = 1;
    if(Lo(K) > 31)
    {
     Ok = 1;
     if(GetModeInsert() == 0)
     {
      if(LS < Max)
      {
       _SetCube(XS+XP,YS,Mark);
       if(XP == LS) LS++;
       T[XP++] = K & 0xFF;
       SetPosCursor(XS+XP,YS);
      }
     }
      else
     {
      if(LS == 0)
      {
       _SetCube(XS,YS,Mark);
       T[0] = Lo(K); T[1] = 0; LS = 1; XP = 1;
       SetPosCursor(XS+1,YS);
      }
       else
      if(LS == XP)
      {
       if(LS < Max)
       {
	_SetCube(XS+XP,YS,Mark);
    LS++; T[XP++] = Lo(K);
	SetPosCursor(XS+XP,YS);
       }
      }
       else
      if(LS < Max)
      {
       for(I = LS;I >= XP; I--)
       {
    T[I+1] = T[I];
	_SetCube(XS+I+1,YS,Mark);
       }
       _SetCube(XS+XP,YS,Mark);
       LS++; T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
    }
   }
  while (Ok == 1);
 Exit:
  strupr(T);
  if(ButtonMouse > 0) return(0xFFFF-ButtonMouse); else return(K);
 }

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

 Word PasswordXYMouse(Byte XS, Byte YS, Word XP, Byte *T, Word Max, Byte Mark, Byte Color)
 {
   // D괽init les variables locals //
  Word     K, I, LS = strlen(T);
  unsigned Ok = 0;
   // Initialise l'괹ran //
  BarSpaceHori(XS,YS,XS+Max-1,Color);
  if(LS > 0) BarTextHori(XS,YS,XS+LS-1,Mark,Color);
  if(XP > LS) XP = 0;
  SetPosCursor(XS+XP,YS);
  SetCursor(MinCursor,MaxCursor);
  do
   {
    ShowPtr();
    while(!KeyPressed())
    {
     GetButPos(&ButtonMouse,&XMouse,&YMouse);
     if(ButtonMouse > 0)
     {
      Byte YMs = (YMouse / 8);
      if(YMs == YS)
      {
       Byte XMs = (XMouse / 8);
       if((XMs >= XS)&&(XMs <= XS + LS))
       {
	XP = XMs - XS;
	SetPosCursor(XS+XP,YS);
	ReleaseKeyMouse();
	ButtonMouse = 0;
       }
	else
       {
	ReleaseKeyMouse();
	HidePtr();
	goto Exit;
       }
      }
       else
      {
       ReleaseKeyMouse();
       HidePtr();
       goto Exit;
      }
     }
    }
    Ok = 0;
    HidePtr();
    K = ReadKey();
    if(K == kbBack)
    {
     Ok = 1;
     if(XP > 0)
     {
      if(XP == LS)
      {
       T[XP--] = 0; LS--;
       SetCube(XS+XP,YS,' ',Color);
       SetPosCursor(XS+XP,YS);
      }
       else
      {
       for(I = XP;I <= LS; I++)
       {
    T[I-1] = T[I];
	SetCube(XS+I-1,YS,Mark,Color);
       }
       SetCube(XS+LS,YS,' ',Color);
       XP--; T[LS--] = 0;
       SetPosCursor(XS+XP,YS);
      }
     }
    }
     else
    if(K == kbDel)
    {
     Ok = 1;
     if((LS != 0)&&(LS != XP))
     {
      for(I = XP;I < LS; I++)
      {
       T[I] = T[I+1];
       SetCube(XS+I,YS,Mark,Color);
      }
      T[LS--] = 0;
      SetCube(XS+LS,YS,' ',Color);
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbLeft)
    {
     Ok = 1;
     if(XP > 0)
     {
      XP--;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbRight)
    {
     Ok = 1;
     if(XP < LS)
     {
      XP++;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbHome)
    {
     Ok = 1; XP = 0;
     SetPosCursor(XS,YS);
    }
     else
    if(K == kbEnd)
    {
     Ok = 1; XP = LS;
     SetPosCursor(XS+XP,YS);
    }
     else
    if(K == kbIns) Ok = 1;
     else
    if((Lo(K) != 0) && (Lo(K) > 31))
    {
     Ok = 1;
     if(GetModeInsert() == 0)
     {
      if(LS < Max)
      {
       SetCube(XS+XP,YS,Mark,Color);
       if(XP == LS) LS++;
       T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
      else
     {
      if(LS == 0)
      {
       SetCube(XS,YS,Mark,Color);
       T[0] = Lo(K); T[1] = 0; LS = 1; XP = 1;
       SetPosCursor(XS+1,YS);
      }
       else
      if(LS == XP)
      {
       if(LS < Max)
       {
	SetCube(XS+XP,YS,Mark,Color);
    LS++; T[XP++] = Lo(K);
	SetPosCursor(XS+XP,YS);
       }
      }
       else
      if(LS < Max)
      {
       for(I = LS;I >= XP; I--)
       {
    T[I+1] = T[I];
	SetCube(XS+I+1,YS,Mark,Color);
       }
       SetCube(XS+XP,YS,Mark,Color);
       LS++; T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
    }
    T[LS] = 0;
   }
  while (Ok == 1);
 Exit:
  strupr(T);
  if(ButtonMouse > 0) return(0xFFFF-ButtonMouse); else return(K);
 }

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

 Word PasswordXYMouse__(Byte XS, Byte YS, Word *XP, Byte *T, Word Max, Byte Mark, Word kbCursorLeft, Word kbCursorRight, Word kbCursorHome, Word kbCursorEnd, Word kbDelChar, Word kbBackChar, Word kbClearLine, Byte Color)
 {
   // D괽init les variables locals //
  Word     K, I, LS = strlen(T);
  unsigned Ok;
   // Initialise l'괹ran //
  BarSpaceHori(XS,YS,XS+Max-1,Color);
  if(LS > 0) BarTextHori(XS,YS,XS+LS-1,Mark,Color);
  if(XP[0] > LS) XP[0] = 0;
  SetPosCursor(XS+XP[0],YS);
  SetCursor(MinCursor,MaxCursor);
  do
   {
    ShowPtr();
    while(!KeyPressed())
    {
     GetButPos(&ButtonMouse,&XMouse,&YMouse);
     if(ButtonMouse > 0)
     {
      Byte YMs = (YMouse / 8);
      if(YMs == YS)
      {
       Byte XMs = (XMouse / 8);
       if((XMs >= XS)&&(XMs <= XS + LS))
       {
	XP[0] = XMs - XS;
	SetPosCursor(XS+XP[0],YS);
	ReleaseKeyMouse();
	ButtonMouse = 0;
       }
	else
       {
	ReleaseKeyMouse();
	HidePtr();
	goto Exit;
       }
      }
       else
      {
       ReleaseKeyMouse();
       HidePtr();
       goto Exit;
      }
     }
    }
    Ok = 0;
    HidePtr();
    K = ReadKey();
    if((K == kbBack)||(K == kbBackChar))
    {
     Ok = 1;
     if(XP > 0)
     {
      if(XP[0] == LS)
      {
       T[XP[0]--] = 0; LS--;
       SetCube(XS+XP[0],YS,' ',Color);
       SetPosCursor(XS+XP[0],YS);
      }
       else
      {
       for(I = XP[0];I <= LS; I++)
       {
    T[I-1] = T[I];
	SetCube(XS+I-1,YS,Mark,Color);
       }
       SetCube(XS+LS,YS,' ',Color);
       XP[0]--; T[LS--] = 0;
       SetPosCursor(XS+XP[0],YS);
      }
     }
    }
     else
    if((K == kbDel)||(K == kbDelChar))
    {
     Ok = 1;
     if((LS != 0)&&(LS != XP[0]))
     {
      for(I = XP[0];I < LS; I++)
      {
       T[I] = T[I+1];
       SetCube(XS+I,YS,Mark,Color);
      }
      T[LS--] = 0;
      SetCube(XS+LS,YS,' ',Color);
      SetPosCursor(XS+XP[0],YS);
     }
    }
     else
    if((K == kbLeft)||(K == kbCursorLeft))
    {
     Ok = 1;
     if(XP[0] > 0)
     {
      XP[0]--;
      SetPosCursor(XS+XP[0],YS);
     }
    }
     else
    if((K == kbRight)||(K == kbCursorRight))
    {
     Ok = 1;
     if(XP[0] < LS)
     {
      XP++;
      SetPosCursor(XS+XP[0],YS);
     }
    }
     else
    if((K == kbHome)||(K == kbCursorHome))
    {
     Ok = 1; XP[0] = 0;
     SetPosCursor(XS,YS);
    }
     else
    if((K == kbEnd)||(K == kbCursorEnd))
    {
     Ok = 1; XP[0] = LS;
     SetPosCursor(XS+XP[0],YS);
    }
     else
    if(K == kbIns) Ok = 1;
     else
    if(K == kbClearLine)
    {
     Ok = 1; T[0] = 0; XP[0] = 0; LS = 0;
     SetPosCursor(XS,YS);
     BarSpaceHori(XS,YS,XS+Max-1,Color);
    }
     else
    if((Lo(K) != 0) && (Lo(K) > 31))
    {
     Ok = 1;
     if(GetModeInsert() == 0)
     {
      if(LS < Max)
      {
       SetCube(XS+XP[0],YS,Mark,Color);
       if(XP[0] == LS) LS++;
       T[XP[0]++] = Lo(K);
       SetPosCursor(XS+XP[0],YS);
      }
     }
      else
     {
      if(LS == 0)
      {
       SetCube(XS,YS,Mark,Color);
       T[0] = Lo(K); T[1] = 0; LS = 1; XP[0] = 1;
       SetPosCursor(XS+1,YS);
      }
       else
      if(LS == XP[0])
      {
       if(LS < Max)
       {
	SetCube(XS+XP[0],YS,Mark,Color);
    LS++; T[XP[0]++] = Lo(K);
	SetPosCursor(XS+XP[0],YS);
       }
      }
       else
      if(LS < Max)
      {
       for(I = LS;I >= XP[0]; I--)
       {
    T[I+1] = T[I];
	SetCube(XS+I+1,YS,Mark,Color);
       }
       SetCube(XS+XP[0],YS,Mark,Color);
       LS++; T[XP[0]++] = Lo(K);
       SetPosCursor(XS+XP[0],YS);
      }
     }
    }
    T[LS] = 0;
   }
  while (Ok == 1);
 Exit:
  strupr(T);
  if(ButtonMouse > 0) return(0xFFFF-ButtonMouse); else return(K);
 }

 // **************************************************************** //
 // *               Questionne jusqu'a x position                  * //
 // **************************************************************** //

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

 Word InputExitEndXYMouse(Byte XS, Byte YS, Word XP, Byte *T, Word Max, Byte Color)
 {
   // D괽init les variables locals //
  Word     K, I, LS = strlen(T);
  unsigned Ok = 0;
   // Initialise les donn괻s //
  if(XP > LS) XP = 0;
   // Initialise l'괹ran //
  BarSpaceHori(XS,YS,XS+Max-1,Color);
  WriteText(XS,YS,T,Color);
  SetPosCursor(XS+XP,YS);
  SetCursor(MinCursor,MaxCursor);
  do
   {
    ShowPtr();
    while(!KeyPressed())
    {
     GetButPos(&ButtonMouse,&XMouse,&YMouse);
     if(ButtonMouse > 0)
     {
      Byte YMs = (YMouse / 8);
      if(YMs == YS)
      {
       Byte XMs = (XMouse / 8);
       if((XMs >= XS)&&(XMs <= XS + LS))
       {
	XP = XMs - XS;
	SetPosCursor(XS+XP,YS);
	ReleaseKeyMouse();
	ButtonMouse = 0;
       }
	else
       {
	ReleaseKeyMouse();
	HidePtr();
	goto Exit;
       }
      }
       else
      {
       ReleaseKeyMouse();
       HidePtr();
       goto Exit;
      }
     }
    }
    Ok = 0;
    HidePtr();
    K = ReadKey();
    if(K == kbBack)
    {
     Ok = 1;
     if(XP > 0)
     {
      if(XP == LS)
      {
       T[XP--] = 0; LS--;
       SetCube(XS+XP,YS,' ',Color);
       SetPosCursor(XS+XP,YS);
      }
       else
      {
       for(I = XP;I <= LS; I++)
       {
    T[I-1] = T[I];
    SetCube(XS+I-1,YS,T[I],Color);
       }
       SetCube(XS+LS,YS,' ',Color);
       XP--; T[LS--] = 0;
       SetPosCursor(XS+XP,YS);
      }
     }
    }
     else
    if(K == kbDel)
    {
     Ok = 1;
     if((LS != 0)&&(LS != XP))
     {
      for(I = XP;I < LS; I++)
      {
       T[I] = T[I+1];
       SetCube(XS+I,YS,T[I],Color);
      }
      T[LS--] = 0;
      SetPosCursor(XS+XP,YS);
     }
    }
     else
    if(K == kbLeft)
    {
     Ok = 1;
     if(XP > 0)
     {
      XP--;
      SetPosCursor(XS+XP,YS);
     }
      else
     goto Exit;
    }
     else
    if(K == kbRight)
    {
     Ok = 1;
     if(XP < LS)
     {
      XP++;
      SetPosCursor(XS+XP,YS);
     }
      else
     {
      Ok = 1;
      if(GetModeInsert() == 0)
      {
       if(LS < Max)
       {
	SetCube(XS+XP,YS,' ',Color);
	if(XP == LS) LS++;
    T[XP++] = ' ';
	SetPosCursor(XS+XP,YS);
       }
      }
       else
      {
       if(LS == 0)
       {
	SetCube(XS,YS,' ',Color);
    T[0] = ' '; T[1] = 0; LS = 1; XP = 1;
	SetPosCursor(XS+1,YS);
       }
	else
       if(LS == XP)
       {
	if(LS < Max)
	{
	 SetCube(XS+XP,YS,' ',Color);
     LS++; T[XP++] = ' ';
	 SetPosCursor(XS+XP,YS);
	}
       }
	else
       if(LS < Max)
       {
	for(I = LS;I >= XP; I--)
	{
     T[I+1] = T[I];
     SetCube(XS+I+1,YS,T[I],Color);
	}
	SetCube(XS+XP,YS,' ',Color);
    LS++; T[XP++] = ' ';
	SetPosCursor(XS+XP,YS);
       }
      }
     }
    }
     else
    if(K == kbHome)
    {
     Ok = 1; XP = 0;
     SetPosCursor(XS,YS);
    }
     else
    if(K == kbEnd)
    {
     Ok = 1; XP = LS;
     SetPosCursor(XS+XP,YS);
    }
     else
    if(K == kbIns) Ok = 1;
     else
    if((Lo(K) != 0) && (Lo(K) > 31))
    {
     Ok = 1;
     if(GetModeInsert() == 0)
     {
      if(LS < Max)
      {
       SetCube(XS+XP,YS,Lo(K),Color);
       if(XP == LS) LS++;
       T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
      else
     {
      if(LS == 0)
      {
       SetCube(XS,YS,Lo(K),Color);
       T[0] = Lo(K); T[1] = 0; LS = 1; XP = 1;
       SetPosCursor(XS+1,YS);
      }
       else
      if(LS == XP)
      {
       if(LS < Max)
       {
	SetCube(XS+XP,YS,Lo(K),Color);
    LS++; T[XP++] = Lo(K);
	SetPosCursor(XS+XP,YS);
       }
      }
       else
      if(LS < Max)
      {
       for(I = LS;I >= XP; I--)
       {
    T[I+1] = T[I];
    SetCube(XS+I+1,YS,T[I],Color);
       }
       SetCube(XS+XP,YS,Lo(K),Color);
       LS++; T[XP++] = Lo(K);
       SetPosCursor(XS+XP,YS);
      }
     }
     T[LS] = 0;
    }
    if(XP == Max) goto Exit;
   }
  while (Ok == 1);
 Exit:
  if(ButtonMouse > 0) return(0xFFFF-ButtonMouse); else return(K);
 }

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

 Word InputExitEndXYMouse__(Byte XS, Byte YS, Word *XP, Byte *T,
			    Word Max,
			    Word kbCursorLeft, Word kbCursorRight,
			    Word kbCursorHome, Word kbCursorEnd,
			    Word kbDelChar,    Word kbBackChar,
			    Word kbClearLine,
			    Byte Color)
 {
   // D괽init les variables locals //
  Word     K, I, LS = strlen(T);
  unsigned Ok = 0;
   // Initialise les donn괻s //
  if(XP[0] > LS) XP[0] = 0;
   // Initialise l'괹ran //
  BarSpaceHori(XS,YS,XS+Max-1,Color);
  WriteText(XS,YS,T,Color);
  SetPosCursor(XS+XP[0],YS);
  SetCursor(MinCursor,MaxCursor);
  do
   {
    ShowPtr();
    while(!KeyPressed())
    {
     GetButPos(&ButtonMouse,&XMouse,&YMouse);
     if(ButtonMouse > 0)
     {
      Byte YMs = (YMouse / 8);
      if(YMs == YS)
      {
       Byte XMs = (XMouse / 8);
       if((XMs >= XS)&&(XMs <= XS + LS))
       {
	XP[0] = XMs - XS;
	SetPosCursor(XS+XP[0],YS);
	ReleaseKeyMouse();
	ButtonMouse = 0;
       }
	else
       {
	ReleaseKeyMouse();
	HidePtr();
	goto Exit;
       }
      }
       else
      {
       ReleaseKeyMouse();
       HidePtr();
       goto Exit;
      }
     }
    }
    Ok = 0;
    HidePtr();
    K = ReadKey();
    if((K == kbBack)||(K == kbBackChar))
    {
     Ok = 1;
     if(XP[0] > 0)
     {
      if(XP[0] == LS)
      {
       T[XP[0]--] = 0; LS--;
       SetCube(XS+XP[0],YS,' ',Color);
       SetPosCursor(XS+XP[0],YS);
      }
       else
      {
       for(I = XP[0];I <= LS; I++)
       {
    T[I-1] = T[I];
    SetCube(XS+I-1,YS,T[I],Color);
       }
       if(LS < Max) SetCube(XS+LS,YS,' ',Color);
       XP[0]--; T[LS--] = 0;
       SetPosCursor(XS+XP[0],YS);
      }
     }
    }
     else
    if((K == kbDel)||(K == kbDelChar))
    {
     Ok = 1;
     if((LS != 0)&&(LS != XP[0]))
     {
      for(I = XP[0];I < LS; I++)
      {
       T[I] = T[I+1]; SetCube(XS+I,YS,T[I],Color);
      }
      T[LS--] = 0; SetPosCursor(XS+XP[0],YS);
     }
    }
     else
    if((K == kbLeft)||(K == kbCursorLeft))
    {
     Ok = 1;
     if(XP[0] > 0)
     {
      XP[0]--; SetPosCursor(XS+XP[0],YS);
     }
      else
     goto Exit;
    }
     else
    if((K == kbRight)||(K == kbCursorRight))
    {
     Ok = 1;
     if(XP[0] < LS)
     {
      XP[0]++; SetPosCursor(XS+XP[0],YS);
     }
      else
     {
      Ok = 1;
      if(GetModeInsert() == 0)
      {
       if(LS < Max)
       {
	SetCube(XS+XP[0],YS,' ',Color);
	if(XP[0] == LS) LS++;
    T[XP[0]++] = ' ';
	SetPosCursor(XS+XP[0],YS);
       }
      }
       else
      {
       if(LS == 0)
       {
	SetCube(XS,YS,' ',Color);
    T[0] = ' '; T[1] = 0; LS = 1; XP[0] = 1;
	SetPosCursor(XS+1,YS);
       }
	else
       if(LS == XP[0])
       {
	if(LS < Max)
	{
	 SetCube(XS+XP[0],YS,' ',Color);
     LS++; T[XP[0]++] = ' ';
	 SetPosCursor(XS+XP[0],YS);
	}
       }
	else
       if(LS < Max)
       {
	for(I = LS;I >= XP[0]; I--)
	{
     T[I+1] = T[I];
     SetCube(XS+I+1,YS,T[I],Color);
	}
	SetCube(XS+XP[0],YS,' ',Color);
    LS++; T[XP[0]++] = ' ';
	SetPosCursor(XS+XP[0],YS);
       }
      }
     }
    }
     else
    if((K == kbHome)||(K == kbCursorHome))
    {
     Ok = 1; XP[0] = 0;
     SetPosCursor(XS,YS);
    }
     else
    if((K == kbEnd)||(K == kbCursorEnd))
    {
     Ok = 1; XP[0] = LS;
     SetPosCursor(XS+XP[0],YS);
    }
     else
    if(K == kbIns) Ok = 1;
     else
    if(K == kbClearLine)
    {
     Ok = 1; T[0] = 0; XP[0] = 0; LS = 0;
     SetPosCursor(XS,YS);
     BarSpaceHori(XS,YS,XS+Max-1,Color);
    }
     else
    if((Lo(K) != 0) && (Lo(K) > 31))
    {
     Ok = 1;
     if(GetModeInsert() == 0)
     {
      if(LS < Max)
      {
       SetCube(XS+XP[0],YS,Lo(K),Color);
       if(XP[0] == LS) LS++;
       T[XP[0]++] = Lo(K);
       SetPosCursor(XS+XP[0],YS);
      }
     }
      else
     {
      if(LS == 0)
      {
       SetCube(XS,YS,Lo(K),Color);
       T[0] = Lo(K); T[1] = 0; LS = 1; XP[0] = 1;
       SetPosCursor(XS+1,YS);
      }
       else
      if(LS == XP[0])
      {
       if(LS < Max)
       {
	SetCube(XS+XP[0],YS,Lo(K),Color);
	LS++;
    T[XP[0]++] = Lo(K);
	SetPosCursor(XS+XP[0],YS);
       }
      }
       else
      if(LS < Max)
      {
       for(I = LS;I >= XP[0]; I--)
       {
    T[I+1] = T[I];
    SetCube(XS+I+1,YS,T[I],Color);
       }
       SetCube(XS+XP[0],YS,Lo(K),Color);
       LS++; T[XP[0]++] = Lo(K);
       SetPosCursor(XS+XP[0],YS);
      }
     }
     T[LS] = 0;
    }
    if(XP[0] == Max) goto Exit;
   }
  while (Ok == 1);
 Exit:
  if(ButtonMouse > 0) return(0xFFFF-ButtonMouse); else return(K);
 }

 Word GetYearExitEndXYMouse__(Byte XYear, Byte Y, Word *XP, Byte CQ, Byte CC, Word kbCursorLeft, Word kbCursorRight, Word kbCursorHome, Word kbCursorEnd,Word kbDelChar, Word kbBackChar, Word kbClearLine, Word *Year)
 {
  Byte Tmp[10]; Word Rep;
  if(*Year != 0) itoa(*Year,Tmp,10); else Tmp[0] = 0;
  Rep   = InputExitEndXYMouse__(XYear,Y,XP,Tmp,4,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearLine,CQ);
  *Year = atoi(Tmp);
  BarSelectHori(XYear,Y,XYear+3,CC);
  return(Rep);
 }

 Word GetMonthExitEndXYMouse__(Byte XMonth, Byte Y, Word *XP, Byte CQ, Byte CC, Word kbCursorLeft, Word kbCursorRight, Word kbCursorHome, Word kbCursorEnd,Word kbDelChar, Word kbBackChar, Word kbClearLine, Byte *Month)
 {
  Byte Tmp[10]; Word Rep;
  if(*Month != 0) itoa(*Month,Tmp,10); else Tmp[0] = 0;
  Rep    = InputExitEndXYMouse__(XMonth,Y,XP,Tmp,2,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearLine,CQ);
  *Month = atoi(Tmp);
  BarSelectHori(XMonth,Y,XMonth+1,CC);
  return(Rep);
 }

 Word GetDayExitEndXYMouse__(Byte XDay, Byte Y, Word *XP, Byte CQ, Byte CC, Word kbCursorLeft, Word kbCursorRight, Word kbCursorHome, Word kbCursorEnd,Word kbDelChar, Word kbBackChar, Word kbClearLine, Byte *Day)
 {
  Byte Tmp[10]; Word Rep;
  if(*Day != 0) itoa(*Day,Tmp,10); else Tmp[0] = 0;
  Rep  = InputExitEndXYMouse__(XDay,Y,XP,Tmp,2,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearLine,CQ);
  *Day = atoi(Tmp);
  BarSelectHori(XDay,Y,XDay+1,CC);
  return(Rep);
 }

 Word InputDateExitEndXYMouse__(Byte X, Byte Y, Byte ModeleDate, Byte SepDate, Byte CQ, Byte CC, Byte CE2, Word kbClearLine, Word kbCursorLeft, Word kbCursorRight, Word kbCursorHome, Word kbCursorEnd, Word kbDelChar, Word kbBackChar, Word kbClearWord, Word *Year, Byte *Month, Byte *Day)
 {
  Word Rep;
  Byte XYear, XMonth, XDay;
  if(ModeleDate == 0)
  {
   XYear  = X + 6; XMonth = X; XDay   = X + 3;
LU100:
   Rep = GetMonthExitEndXYMouse__(XMonth,Y,0,CQ,CC,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearWord,Month);
   if(Rep == kbClearLine)
   {
    TriBarSpaceHori(Y,XMonth,XMonth+1,XDay,XDay+1,XYear,XYear+3,CC);
    BiSpaceH(Y,X+2,X+5,CE2);
    *Year = 0; *Day = 0; *Month = 0;
    goto LU100;
   }
   if((Rep == kbDown)||(Rep == kbUp)||(Rep == kbEsc)||(Rep == kbCtrlLeft)||(Rep > 0xFFF0)) return(Rep);
LU105:
   SetCube(X+2,Y,SepDate,CE2);
   Rep = GetDayExitEndXYMouse__(XDay,Y,0,CQ,CC,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearWord,Day);
   if(Rep == kbClearLine)
   {
    TriBarSpaceHori(Y,XMonth,XMonth+1,XDay,XDay+1,XYear,XYear+3,CC);
    BiSpaceH(Y,X+2,X+5,CE2);
    *Year = 0; *Day = 0; *Month = 0;
    goto LU100;
   }
   if((Rep == kbLeft)||(Rep == kbCtrlLeft))
   {
    SetCube(X+2,Y,' ',CE2); goto LU100;
   }
   if((Rep == kbDown)||(Rep == kbUp)||(Rep == kbEsc)||(Rep > 0xFFF0)) return(Rep);
LU110:
   SetCube(X+5,Y,SepDate,CE2);
   Rep = GetYearExitEndXYMouse__(XYear,Y,0,CQ,CC,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearWord,Year);
   if(Rep == kbClearLine)
   {
    TriBarSpaceHori(Y,XMonth,XMonth+1,XDay,XDay+1,XYear,XYear+3,CC);
    BiSpaceH(Y,X+2,X+5,CE2);
    *Year = 0; *Day = 0; *Month = 0;
    goto LU100;
   }
   if((Rep == kbLeft)||(Rep == kbCtrlLeft))
   {
    SetCube(X+5,Y,' ',CE2); goto LU105;
   }
   PutSpcIf0(&Day,X+2,Y,CE2);
   PutSpcIf0(&Year,X+2,Y,CE2);
   return(Rep);
  }
   else
  if(ModeleDate == 1)
  {
   XYear = X + 6; XMonth = X + 3; XDay = X;
LE100:
   Rep = GetDayExitEndXYMouse__(XDay,Y,0,CQ,CC,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearWord,Day);
   if(Rep == kbClearLine)
   {
    TriBarSpaceHori(Y,XMonth,XMonth+1,XDay,XDay+1,XYear,XYear+3,CC);
    BiSpaceH(Y,X+2,X+5,CE2);
    *Year = 0; *Day = 0; *Month = 0;
    goto LE100;
   }
   if((Rep == kbDown)||(Rep == kbUp)||(Rep == kbEsc)||(Rep == kbCtrlLeft)||(Rep > 0xFFF0)) return(Rep);
LE105:
   SetCube(X+2,Y,SepDate,CE2);
   Rep = GetMonthExitEndXYMouse__(XMonth,Y,0,CQ,CC,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearWord,Month);
   if(Rep == kbClearLine)
   {
    TriBarSpaceHori(Y,XMonth,XMonth+1,XDay,XDay+1,XYear,XYear+3,CC);
    BiSpaceH(Y,X+2,X+5,CE2);
    *Year = 0; *Day = 0; *Month = 0;
    goto LE100;
   }
   if((Rep == kbLeft)||(Rep == kbCtrlLeft))
   {
    PutSpcIf0(&Month,X+2,Y,CE2); goto LE100;
   }
   if((Rep == kbDown)||(Rep == kbUp)||(Rep == kbEsc)||(Rep > 0xFFF0)) return(Rep);
LE110:
   SetCube(X+5,Y,SepDate,CE2);
   Rep = GetYearExitEndXYMouse__(XYear,Y,0,CQ,CC,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearWord,Year);
   if(Rep == kbClearLine)
   {
    TriBarSpaceHori(Y,XMonth,XMonth+1,XDay,XDay+1,XYear,XYear+3,CC);
    BiSpaceH(Y,X+2,X+5,CE2);
    *Year = 0; *Day = 0; *Month = 0;
    goto LE100;
   }
   if((Rep == kbLeft)||(Rep == kbCtrlLeft))
   {
    PutSpcIf0(&Year,X+5,Y,CE2); goto LE105;
   }
   PutSpcIf0(&Month,X+2,Y,CE2);
   PutSpcIf0(&Year,X+5,Y,CE2);
   return(Rep);
  }
   else
  {
   XYear = X; XMonth = X + 5; XDay = X + 8;
L100:
   Rep = GetYearExitEndXYMouse__(XYear,Y,0,CQ,CC,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearWord,Year);
   if(Rep == kbClearLine)
   {
    TriBarSpaceHori(Y,XMonth,XMonth+1,XDay,XDay+1,XYear,XYear+3,CC);
    BiSpaceH(Y,X+4,X+7,CE2);
    *Year = 0; *Day = 0; *Month = 0;
    goto L100;
   }
   if((Rep == kbDown)||(Rep == kbUp)||(Rep == kbEsc)||(Rep == kbCtrlLeft)||(Rep > 0xFFF0)) return(Rep);
L105:
   SetCube(X+4,Y,SepDate,CE2);
   Rep = GetMonthExitEndXYMouse__(XMonth,Y,0,CQ,CC,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearWord,Month);
   if(Rep == kbClearLine)
   {
    TriBarSpaceHori(Y,XMonth,XMonth+1,XDay,XDay+1,XYear,XYear+3,CC);
    BiSpaceH(Y,X+4,X+7,CE2);
    *Year = 0; *Day = 0; *Month = 0;
    goto L100;
   }
   if((Rep == kbLeft)||(Rep == kbCtrlLeft))
   {
    PutSpcIf0(&Month,X+4,Y,CE2); goto L100;
   }
   if((Rep == kbDown)||(Rep == kbUp)||(Rep == kbEsc)||(Rep > 0xFFF0)) return(Rep);
L110:
   SetCube(X+7,Y,SepDate,CE2);
   Rep = GetDayExitEndXYMouse__(XDay,Y,0,CQ,CC,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearWord,Day);
   if(Rep == kbClearLine)
   {
    TriBarSpaceHori(Y,XMonth,XMonth+1,XDay,XDay+1,XYear,XYear+3,CC);
    BiSpaceH(Y,X+4,X+7,CE2);
    *Year = 0; *Day = 0; *Month = 0;
    goto L100;
   }
   if((Rep == kbLeft)||(Rep == kbCtrlLeft))
   {
    PutSpcIf0(&Day,X+7,Y,CE2); goto L105;
   }
   PutSpcIf0(&Month,X+4,Y,CE2);
   PutSpcIf0(&Day,X+7,Y,CE2);
   return(Rep);
  }
 }

#endif
