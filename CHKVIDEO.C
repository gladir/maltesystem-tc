/******************************************************************/
/*                                                                */
/*                   Malte System/Check Video                     */
/*                          1992/08/19                            */
/*                                                                */
/*           Copyright (C) par les Chevaliers de Malte            */
/*                                                                */
/******************************************************************/

#ifndef __Malte_Check_Video__
 #define __Malte_Check_Video__

 #include <DOS.H>
 #include <VIDEO\CHKVIDEO.H>

 #ifdef __PASCAL__

 Word strlen(Byte *Buffer)
 {
  Word I;
  for(I = 0; (Buffer[I] > 0)||(I < 8192); I++);
  return(I+1);
 }
 
 #else
  #include <STRING.H>
 #endif

 Byte StrCmpROM(Word Segment, Word Offset, Byte *Str)
 {
  Byte I; Word Len = strlen(Str);
  for(I = 0; I < Len; I++)
  {
   if(peekb(Segment,Offset+I) != Str[I]) return(0);
  }
  return(1);
 }

 Byte Check6845(Word Port)
 {
  asm MOV DX,Port;
  asm MOV AL,0x0A;
  asm OUT DX,AL;
  asm INC DX;
  asm IN  AL,DX;
  asm MOV AH,AL;
  asm OUT DX,AL;
  asm MOV AL,0x10;
  asm OUT DX,AL;
  asm MOV CX,0x0100;
 Wait:
  asm LOOP Wait;
  asm IN   AL,DX;
  asm XCHG AL,AH;
  asm OUT  DX,AL;
  asm CMP  AH,0x10;
  asm JE   Yes;
  return(0);
 Yes:
  return(1);
 }

 Byte _Check6845(void)
 {
  return(Check6845(peek(0x0040,0x0063)));
 }

 Byte CheckHGC(void)
 {
  asm MOV  DX,0x03B4;
  asm IN   AL,DX;
  asm AND  AL,0x80;
  asm MOV  AH,AL;
  asm MOV  CX,0x8000;
Chk:
  asm IN   AL,DX;
  asm AND  AL,0x80;
  asm CMP  AL,AH;
  asm JNE  IS_HGC;
  asm LOOP Chk;
  return(0);
IS_HGC:
  return(1);
 }

 Byte CheckITVGA2(void)
 {
  return(StrCmpROM(0xC000,0x0181,"IT - VGA2"));
 }

 Byte CheckATI(void)
 {
  return(StrCmpROM(0xC000,0x00F9,"ATI"));
 }

/*
 Byte CheckGS(void)
 {
  int Iabs(), Inp();
  unsigned a;
  long t1,t2;
  int count, vr1;
  static t_type = 255;
  if(t_type != 255) return(t_type);
  if(peek(0x0040,0x0063) != 0x03D4) return(255);
  Time_1A(&a, &t1);
  for(t2 = t1; t2 == t1; Time_1A(&a, &t2));
  count = 0;
  vr1 = Inp(0x03DA) & 0x08;
  for(t1 = t2; (t2 - t1) <= 18; Time_1A(&a,&t2))
  {
   for(; vr1 != 0; vr1 = Inp(0x03DA) & 0x0008);
   for(; vr1 == 0; vr1 = Inp(0x03DA) & 0x0008);
   ++count;
  }
  if(Iabs(count - 50) <= 5) return(0);
  if(Iabs(count - 60) <= 5) return(1);
  return(255);
 }
*/

#endif