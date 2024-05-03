#ifndef __Malte_Video_Key__
 #define __Malte_Video_Key__

 #include <VIDEO\TEXT\BIOS.H>
 #include <VIDEO\TEXT\DIRECT.H>

 extern struct 
        {
         Byte ColorKey;
         Byte ColorShade;
         Byte LeftChar;
         Byte RightChar;
         Byte Shade;
        }
        VideoKey;

 void _PutVideoKey(Byte X1, Byte Y, Byte X2)
 {
  SetColor(VideoKey.ColorKey);
  _SetCube(X1,Y,VideoKey.LeftChar);
  _BarSpaceHori(X1+1,Y,X2-1);
  _SetCube(X2,Y,VideoKey.RightChar);
  if(VideoKey.Shade == 1)
  {
   SetColor(VideoKey.ColorShade);
   _SetCube(X2+1,Y,'Ü');
   _BarTextHori(X1+1,Y+1,X2+1,'ß');
  }
 }

 #ifndef __PASCAL__
  void _PutVideoKeyText(Byte X1, Byte Y, Byte X2, Byte *Text)
 #else
  void _PutVideoKeyText(Byte X1, Byte Y, Byte X2, String Text)
 #endif
 {
  SetColor(VideoKey.ColorKey);
  _SetCube(X1,Y,VideoKey.LeftChar);
  _BarSpaceHori(X1+1,Y,X2-1);
  _SetCube(X2,Y,VideoKey.RightChar);
  #ifndef __PASCAL__
   _WriteText(X1+(((X2-X1+1)-strlen(Text)) / 2),Y,Text);
  #else 
   _WriteText(X1+(((X2-X1+1)-Text[0]) >> 1),Y,Text);
  #endif
  if(VideoKey.Shade == 1)
  {
   SetColor(VideoKey.ColorShade);
   _SetCube(X2+1,Y,'Ü');
   _BarTextHori(X1+1,Y+1,X2+1,'ß');
  }
 }

 #ifndef __PASCAL__
  void _PutVideoKeyTextNoShade(Byte X1, Byte Y, Byte X2, Byte *Text)
 #else
  void _PutVideoKeyTextNoShade(Byte X1, Byte Y, Byte X2, String Chn)
 #endif
 {
  SetColor(VideoKey.ColorKey);
  _SetCube(X1,Y,VideoKey.LeftChar);
  _BarSpaceHori(X1+1,Y,X2-1);
  _SetCube(X2,Y,VideoKey.RightChar);
  #ifndef __PASCAL__
   _WriteText(X1+(((X2-X1+1)-strlen(Text)) >> 1),Y,Text);
  #else
   _WriteText(X1+(((X2-X1+1)-Chn[0]) >> 1),Y,Chn);
  #endif
 }

 #ifndef __PASCAL__

  void SetColorKey(Byte ColorKey, Byte ColorShade)
  {
   VideoKey.ColorKey = ColorKey; VideoKey.ColorShade = ColorShade;
  }

  void SetShadeKey(Byte Shade)
  {
   VideoKey.Shade = Shade;
  }

  void SetVideoKey(Byte LeftKey, Byte RightKey, Byte Color, Byte ColorOmbre)
  {
   VideoKey.ColorShade = ColorOmbre;
   VideoKey.ColorKey = Color;
   VideoKey.LeftChar = LeftKey;
   VideoKey.RightChar = RightKey;
  }

 #endif

#endif
