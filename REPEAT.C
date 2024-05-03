/****************************************************************/
/*                                                              */
/*                Malte System/Video Repeat Header              */
/*                          1992/07/18                          */
/*                                                              */
/*          Copyright (C) par les Chevaliers de Malte           */
/*                                                              */
/****************************************************************/

#ifndef __Malte_Video_Repeat__
 #define __Malte_Video_Repeat__

 #include <MEM.H>
 #include <VIDEO\TEXT_MEM.H>
 #include <VIDEO\BIOS_TXT.H>
 #include <VIDEO\TEXT.H>
 #include <VIDEO\REPEAT.H>

  // Type //

 #ifndef __Malte_Var_Pascal__
  #define __Malte_Var_Pascal__
  typedef unsigned char Byte;
  typedef unsigned int  Word;
 #endif

 extern Byte VID;

 void _BiCubeH(Byte Y, Byte X1, Byte X2, Byte Char)
 {
  if(VID == 0)
  {
   MEM__SetCube(X1,Y,Char);
   MEM__SetCube(X2,Y,Char);
  }
   else
  {
   BIOS_SetCube_(X1,Y,Char);
   BIOS_SetCube_(X2,Y,Char);
  }
 }

 void _BiSpaceH(Byte Y, Byte X1, Byte X2)
 {
  if(VID == 0)
  {
   MEM__SetCube(X1,Y,' ');
   MEM__SetCube(X2,Y,' ');
  }
   else
  {
   BIOS_SetCube_(X1,Y,' ');
   BIOS_SetCube_(X2,Y,' ');
  }
 }

 void _TriBarSpaceHori(Byte Y, Byte XA1, Byte XA2, Byte XB1, Byte XB2, Byte XC1, Byte XC2)
 {
  if(VID == 0)
  {
   MEM__BarSpaceHori(XA1,Y,XA2);
   MEM__BarSpaceHori(XB1,Y,XB2);
   MEM__BarSpaceHori(XC1,Y,XC2);
  }
   else
  {
   BIOS_BarSpaceHori_(XA1,Y,XA2);
   BIOS_BarSpaceHori_(XB1,Y,XB2);
   BIOS_BarSpaceHori_(XC1,Y,XC2);
  }
 }

 void _TriBarTextHori(Byte Y, Byte XA1, Byte XA2, Byte XB1, Byte XB2, Byte XC1, Byte XC2, Byte Char)
 {
  if(VID == 0)
  {
   MEM__BarTextHori(XA1,Y,XA2,Char);
   MEM__BarTextHori(XB1,Y,XB2,Char);
   MEM__BarTextHori(XC1,Y,XC2,Char);
  }
   else
  {
   BIOS_BarTextHori_(XA1,Y,XA2,Char);
   BIOS_BarTextHori_(XB1,Y,XB2,Char);
   BIOS_BarTextHori_(XC1,Y,XC2,Char);
  }
 }

 void BiBarSpaceHori(Byte Y, Byte XA1, Byte XA2, Byte XB1, Byte XB2, Byte Color)
 {
  if(VID == 0)
  {
   MEM_BarSpaceHori(XA1,Y,XA2,Color);
   MEM_BarSpaceHori(XB1,Y,XB2,Color);
  }
   else
  {
   BIOS_BarSpaceHori(XA1,Y,XA2,Color);
   BIOS_BarSpaceHori(XB1,Y,XB2,Color);
  }
 }

 void BiBarTextHori(Byte Y, Byte XA1, Byte XA2, Byte XB1, Byte XB2, Byte Char, Byte Color)
 {
  BarTextHori(XA1,Y,XA2,Char,Color);
  BarTextHori(XB1,Y,XB2,Char,Color);
 }

 void BiCubeH(Byte Y, Byte X1, Byte X2, Byte Char, Byte Color)
 {
  SetCube(X1,Y,Char,Color);
  SetCube(X2,Y,Char,Color);
 }

 void BiSpaceH(Byte Y, Byte X1, Byte X2, Byte Color)
 {
  SetCube(X1,Y,' ',Color);
  SetCube(X2,Y,' ',Color);
 }

 void TriBarSpaceHori(Byte Y, Byte XA1, Byte XA2, Byte XB1, Byte XB2, Byte XC1, Byte XC2, Byte Color)
 {
  BarSpaceHori(XA1,Y,XA2,Color);
  BarSpaceHori(XB1,Y,XB2,Color);
  BarSpaceHori(XC1,Y,XC2,Color);
 }

 void TriBarTextHori(Byte Y, Byte XA1, Byte XA2, Byte XB1, Byte XB2, Byte XC1, Byte XC2, Byte Char, Byte Color)
 {
  BarTextHori(XA1,Y,XA2,Char,Color);
  BarTextHori(XB1,Y,XB2,Char,Color);
  BarTextHori(XC1,Y,XC2,Char,Color);
 }

 void WriteRepeatTypingXY(Byte X, Byte Y, Byte *Buffer[])
 {
  Word I;
  for(I = 0;Buffer[I] != NULL;I++)
  {
   WriteTypingXY(X,Y+I,Buffer[I]);
  }
 }

 void WriteRepeatTypingXYBicolor(Byte X, Byte Y, Byte *Buffer[], Byte AC, Byte NC)
 {
  Word I;
  for(I = 0;Buffer[I] != NULL;I++)
  {
   WriteTypingXYBicolor(X,Y+I,Buffer[I],AC,NC);
  }
 }

#endif