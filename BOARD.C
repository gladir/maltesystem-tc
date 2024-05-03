/****************************************************************/
/*                                                              */
/*               Malte System/Gadget Video Board                */
/*                          1992/07/27                          */
/*                                                              */
/*          Copyright (C) par les Chevaliers de Malte           */
/*                                                              */
/****************************************************************/

#ifndef __Malte_Video_Board__
 #define __Malte_Video_Board__

 #include <CONIO.H>
 #include <NUMERIC.H>
 #include <KEYBOARD\BIOS_KEY.H>
 #include <MOUSE\MOUSE.H>
 #include <VIDEO\TEXT.H>
 #include <VIDEO\BIOS_CUR.H>

 extern Word XMouse;
 extern Word YMouse;
 extern Word ButtonMouse;

 void _SetWindowCharEditor(Byte XP, Byte YP, Word XS, Word YS, Byte Mask, Byte *Buffer)
 {
  Word I,J;
  for(I = 0; I <= YS; I++)
  {
   for(J = 0; J <= XS; J++)
   {
    if(Buffer[J+I*(XS+1)] == 1) SetChar(XP+J,YP+I,Mask);
			   else SetChar(XP+J,YP+I,' ');
   }
  }
 }

 void SetWindowCharEditor(Byte XP, Byte YP, Word XS, Word YS, Byte Mask, Byte Color, Byte *Buffer)
 {
  Word I,J;
  ClearWindow(XP,YP,XP+XS,YP+YS,Color);
  for(I = 0; I <= YS; I++)
  {
   for(J = 0; J <= XS; J++)
   {
    if(Buffer[J+I*(XS+1)] == 1) SetChar(XP+J,YP+I,Mask);
   }
  }
 }

 void CharEditorXYMouse(Byte XP, Byte YP, Word XS, Word YS, Byte Mask, Byte *Buffer)
 {
  unsigned True;
  Word     K;
  Byte     X,Y;
  X = 0; Y = 0;
  BIOS_SetPosCursor(XP+X,YP+Y,0);
  do
   {
    ShowPtr();
    while(!kbhit())
    {
     GetButPos(&ButtonMouse,&XMouse,&YMouse);
     if(ButtonMouse > 0)
     {
      Byte XMs;
      Byte YMs;
      YMs = (YMouse / 8);
      XMs = (XMouse / 8);
      if((XMs >= XP)&&(XMs <= XP+XS))
      {
       if((YMs >= YP)&&(YMs <= YP+YS))
       {
	X = XMs - XP;
	Y = YMs - YP;
	HidePtr();
	BIOS_SetPosCursor(XP+X,YP+Y,0);
	if(Buffer[X+Y*(XS+1)] == 0)
	{
	 Buffer[X+Y*(XS+1)] = 1;
	 SetChar(XP+X,YP+Y,Mask);
	}
	 else
	{
	 Buffer[X+Y*(XS+1)] = 0;
	 SetChar(XP+X,YP+Y,' ');
	}
	ShowPtr();
	ReleaseKeyMouse();
       }
      }
     }
    }
    True = 0;
    HidePtr();
    K = BIOS_ReadKey();
    if(K == kbUp)
    {
     True = 1;
     Y = Min(Y,YS);
     BIOS_SetPosCursor(XP+X,YP+Y,0);
    }
     else
    if(K == kbDown)
    {
     True = 1;
     Y = Max(Y,YS);
     BIOS_SetPosCursor(XP+X,YP+Y,0);
    }
     else
    if(K == kbLeft)
    {
     True = 1;
     X = Min(X,XS);
     BIOS_SetPosCursor(XP+X,YP+Y,0);
    }
     else
    if(K == kbRight)
    {
     True = 1;
     X = Max(X,XS);
     BIOS_SetPosCursor(XP+X,YP+Y,0);
    }
     else
    if(K == kbCtrlHome)
    {
     True = 1;
     X    = 0;
     Y    = 0;
     BIOS_SetPosCursor(XP+X,YP+Y,0);
    }
     else
    if(K == kbCtrlEnd)
    {
     True = 1;
     X    = XS;
     Y    = YS;
     BIOS_SetPosCursor(XP+X,YP+Y,0);
    }
     else
    if(Lo(K) == 32)
    {
     True = 1;
     if(Buffer[X+Y*(XS+1)] == 0)
     {
      Buffer[X+Y*(XS+1)] = 1;
      SetChar(XP+X,YP+Y,Mask);
     }
      else
     {
      Buffer[X+Y*(XS+1)] = 0;
      SetChar(XP+X,YP+Y,' ');
     }
    }
     else
    if(Lo(K) == '1')
    {
     True = 1;
     Buffer[X+Y*(XS+1)] = 1;
     SetChar(XP+X,YP+Y,Mask);
    }
     else
    if(Lo(K) == '0')
    {
     True = 1;
     Buffer[X+Y*(XS+1)] = 0;
     SetChar(XP+X,YP+Y,' ');
    }
   }
  while(True == 1);
 }

 void CharEditorXYMouse__(Byte XP, Byte YP, Word XS, Word YS, Byte Mask, Word *X, Word *Y, Word kbCursorLeft, Word kbCursorRight, Word kbCursorUp, Word kbCursorDown, Word kbCursorHome, Word kbCursorEnd, Word kbSwitch, Word kbReset, Word kbSet, Word kbClearLine, Word kbClearColumns, Word kbClearScreen, Byte *Buffer)
 {
  unsigned True;
  Word     K;
  BIOS_SetPosCursor(XP+X[0],YP+Y[0],0);
  do
   {
    ShowPtr();
    while(!kbhit())
    {
     GetButPos(&ButtonMouse,&XMouse,&YMouse);
     if(ButtonMouse > 0)
     {
      Byte XMs;
      Byte YMs;
      YMs = (YMouse / 8);
      XMs = (XMouse / 8);
      if((XMs >= XP)&&(XMs <= XP+XS))
      {
       if((YMs >= YP)&&(YMs <= YP+YS))
       {
	X[0] = XMs - XP;
	Y[0] = YMs - YP;
	HidePtr();
	BIOS_SetPosCursor(XP+X[0],YP+Y[0],0);
	if(Buffer[X[0]+Y[0]*(XS+1)] == 0)
	{
	 Buffer[X[0]+Y[0]*(XS+1)] = 1;
	 SetChar(XP+X[0],YP+Y[0],Mask);
	}
	 else
	{
	 Buffer[X[0]+Y[0]*(XS+1)] = 0;
	 SetChar(XP+X[0],YP+Y[0],' ');
	}
	ShowPtr();
	ReleaseKeyMouse();
       }
      }
     }
    }
    True = 0;
    HidePtr();
    K = BIOS_ReadKey();
    if((K == kbUp)||(K == kbCursorUp))
    {
     True = 1;
     Y[0] = Min(Y[0],YS);
     BIOS_SetPosCursor(XP+X[0],YP+Y[0],0);
    }
     else
    if((K == kbDown)||(K == kbCursorDown))
    {
     True = 1;
     Y[0] = Max(Y[0],YS);
     BIOS_SetPosCursor(XP+X[0],YP+Y[0],0);
    }
     else
    if((K == kbLeft)||(K == kbCursorLeft))
    {
     True = 1;
     X[0] = Min(X[0],XS);
     BIOS_SetPosCursor(XP+X[0],YP+Y[0],0);
    }
     else
    if((K == kbRight)||(K == kbCursorRight))
    {
     True = 1;
     X[0] = Max(X[0],XS);
     BIOS_SetPosCursor(XP+X[0],YP+Y[0],0);
    }
     else
    if((K == kbCtrlHome)||(K == kbCursorHome))
    {
     True = 1;
     X[0] = 0;
     Y[0] = 0;
     BIOS_SetPosCursor(XP+X[0],YP+Y[0],0);
    }
     else
    if((K == kbCtrlEnd)||(K == kbCursorEnd))
    {
     True = 1;
     X[0] = XS;
     Y[0] = YS;
     BIOS_SetPosCursor(XP+X[0],YP+Y[0],0);
    }
     else
    if((Lo(K) == 32)||(K == kbSwitch))
    {
     True = 1;
     if(Buffer[X[0]+Y[0]*(XS+1)] == 0)
     {
      Buffer[X[0]+Y[0]*(XS+1)] = 1;
      SetChar(XP+X[0],YP+Y[0],Mask);
     }
      else
     {
      Buffer[X[0]+Y[0]*(XS+1)] = 0;
      SetChar(XP+X[0],YP+Y[0],' ');
     }
    }
     else
    if((Lo(K) == '1')||(K == kbSet))
    {
     True = 1;
     Buffer[X[0]+Y[0]*(XS+1)] = 1;
     SetChar(XP+X[0],YP+Y[0],Mask);
    }
     else
    if((Lo(K) == '0')||(K == kbReset))
    {
     True = 1;
     Buffer[X[0]+Y[0]*(XS+1)] = 0;
     SetChar(XP+X[0],YP+Y[0],' ');
    }
     else
    if(K == kbClearLine)
    {
     Word I;
     for(True = 1,I = 0;I <= XS; I++)
     {
      Buffer[I + (Y[0] * (XS+1))] = 0;
      SetChar(XP+I,YP+Y[0],' ');
     }
    }
     else
    if(K == kbClearColumns)
    {
     Word J;
     for(True = 1,J = 0;J <= YS; J++)
     {
      Buffer[X[0] + (J * (XS+1))] = 0;
      SetChar(XP+X[0],YP+J,' ');
     }
    }
     else
    if(K == kbClearScreen)
    {
     Word I,J;
     for(True = 1,I = 0; I <= YS; I++)
     {
      for(J = 0; J <= XS; J++)
      {
       Buffer[J+I*(XS+1)] = 0;
       SetChar(XP+J,YP+I,' ');
      }
     }
    }
   }
  while(True == 1);
 }

#endif