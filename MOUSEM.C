/**************************************************************/
/*                                                            */
/*                       Malte System/Mouse                   */
/*                           1992/08/13                       */
/*                                                            */
/*         Copyright (C) par les Chevaliers de Malte          */
/*                                                            */
/**************************************************************/

//
// Programmeur :
//
//  Sylvain Maltais
//
// DerniŠre modification :
//
//  Jeudi, le 1 juin 1993 (UpDate all function).
//
// Directive de compilation conditionnel :
//
// __PASCAL__   Indique qu'il doit fonctionner avec le
//              compilateur Turbo Pascal 4 ou post‚rieur.
//

#ifndef __MALTEMOUSE__
 #define __MALTEMOUSE__

 #include "DOS.H"
 #include <NUMERIC.H>
// #include <MOUSE.H>

 #ifndef __PASCAL__

  Byte MON  = 0;
  Word Msk  = 0;
  int  MPRX = 8,
       MPRY = 16;

 #else

  extern Byte MON;
  extern Word Msk;
  extern int  MPRX, MPRY;

 #endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      ExcludeZone                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void ExcludeZone(Word X1, Word Y1, Word X2, Word Y2)
 {
  if(MON)
  {
   asm MOV AX,0x10;
   asm MOV CX,X1;
   asm MOV DX,Y1;
   asm MOV SI,X2;
   asm MOV DI,Y2;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      GetButPos                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void GetButPos(Word *Button, Word *X, Word *Y)
 {
  if(MON)
  {
   asm MOV AX,0x0003;
   asm INT 0x33;
   asm LES DI,Button;
   asm MOV ES:[DI],BX;
   asm LES DI,X;
   asm MOV ES:[DI],CX;
   asm LES DI,Y;
   asm MOV ES:[DI],DX;
  }
   else
  {
   *Button = 0;
   *X      = 0;
   *Y      = 0;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      GetButPress                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void GetButPress(Word But, Word *Butt, Word *Num, Word *X, Word *Y)
 {
  if(MON)
  {
   asm MOV AX,0x0005;
   asm MOV BX,But;
   asm INT 0x33;
   asm LES DI,Butt;
   asm MOV ES:[DI],AX;
   asm LES DI,Num;
   asm MOV ES:[DI],BX;
   asm LES DI,X;
   asm MOV ES:[DI],CX;
   asm LES DI,Y;
   asm MOV ES:[DI],DX;
  }
   else
  {
   *Butt = 0;
   *Num  = 0;
   *X    = 0;
   *Y    = 0;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      GetButRelease                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void GetButRelease(Word But, Word *Butt, Word *Num, Word *X, Word *Y)
 {
  if(MON)
  {
   asm MOV AX,0x0006;
   asm MOV BX,But;
   asm INT 0x33;
   asm LES DI,Butt;
   asm MOV ES:[DI],AX;
   asm LES DI,Num;
   asm MOV ES:[DI],BX;
   asm LES DI,X;
   asm MOV ES:[DI],CX;
   asm LES DI,Y;
   asm MOV ES:[DI],DX;
  }
   else
  {
   *Butt = 0;
   *Num  = 0;
   *X    = 0;
   *Y    = 0;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   GetMickeyPixelRatio                ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void GetMickeyPixelRatio(int *X, int *Y)
 {
  *X = MPRX;
  *Y = MPRY;
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   GetMotionCounters                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void GetMotionCounters(Word *X, Word *Y)
 {
  if(MON)
  {
   asm MOV AX,0x000B;
   asm INT 0x33;
   asm LES DI,X;
   asm MOV ES:[DI],CX;
   asm LES DI,Y;
   asm MOV ES:[DI],DX;
  }
   else
  {
   *X = 0;
   *Y = 0;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       GetMouse                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 Byte GetMouse(void)
 {
  return(MON);
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    GetMouseLanguage                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 Word GetMouseLanguage(void)
 {
  if(MON)
  {
   asm MOV AX,0x0023;
   asm INT 0x33;
   return(_BX);
  }
   else
  return(0);
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      GetPageMouse                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 Word GetPageMouse(void)
 {
  if(MON)
  {
   asm MOV AX,0x001E;
   asm INT 0x33;
   return(_BX);
  }
   else
  return(0);
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      GetSetupMouse                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void GetSetupMouse(Byte *HiVer, Byte *LoVer, Byte *Type, Byte *IRQ)
 {
  if(MON)
  {
   asm MOV AX,0x0024;
   asm INT 0x33;
   asm LES DI,HiVer;
   asm MOV ES:[DI],BH;
   asm LES DI,LoVer;
   asm MOV ES:[DI],BL;
   asm LES DI,Type;
   asm MOV ES:[DI],CH;
   asm LES DI,IRQ;
   asm MOV ES:[DI],CL;
  }
   else
  {
   *HiVer = 0;
   *LoVer = 0;
   *Type  = 0;
   *IRQ   = 0;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   GetSizeMouseBuffer                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 Word GetSizeMouseBuffer(void)
 {
  if(MON)
  {
   asm MOV AX,0x0015;
   asm INT 0x33;
   return(_BX);
  }
   else
  return(0);
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       GetTextMouse                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 Word GetTextMouse(void)
 {
  return(Msk);
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                         HidePtr                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void HidePtr(void)
 {
  if(MON)
  {
   asm MOV AX,0x0002;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     LightPenEmulOff                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void LightPenEmulOff(void)
 {
  if(MON)
  {
   asm MOV AX,0x000E;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      LightPenEmulOn                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void LightPenEmulOn(void)
 {
  if(MON)
  {
   asm MOV AX,0x000D;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      MouseResetStat                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void MouseResetStat(Word *Flags, Word *Button)
 {
  if(MON)
  {
   asm XOR AX,AX;
   asm INT 0x33;
   asm LES DI,Flags;
   asm MOV ES:[DI],AX;
   asm LES DI,Button;
   asm MOV ES:[DI],BX;
   MPRX = 8;
   MPRY = 16;
   Msk  = 0;
  }
   else
  {
   *Flags  = 0;
   *Button = 0;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     MouseSoftWareStat                ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 Word MouseSoftwareReset(void)
 {
  if(MON)
  {
   asm MOV AX,0x21;
   asm INT 0x33;
   MPRX = 8;
   MPRY = 16;
   Msk  = 0;
   return(_AX == 0xFFFF ? _BX : 0);
  }
   else
  return(0);
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    RestoreMouseBuffer                ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void RestoreMouseBuffer(const *Buffer)
 {
  if(MON)
  {
   asm LES DX,Buffer;
   asm MOV AX,0x17;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      SaveMouseBuffer                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SaveMouseBuffer(const *Buffer)
 {
  if(MON)
  {
   asm LES DX,Buffer;
   asm MOV AX,0x16;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                   SetDisableMouseDriver              ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetDisableMouseDriver(Word *Seg, Word *Ofs)
 {
  asm CMP MON,True;
  asm MOV AX,0x001F;
  asm INT 0x33;
  asm CMP AX,0x001F;
  asm JNE __1;
  asm MOV AX,ES;
  asm LES DI,Seg;
  asm MOV ES:[DI],AX;
  asm LES DI,Ofs;
  asm MOV ES:[DI],BX;
  asm JMP __2;
__1:
  asm XOR AX,AX;
  asm LES DI,Seg;
  asm MOV ES:[DI],AX;
  asm LES DI,Ofs;
  asm MOV ES:[DI],AX;
__2:;
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    SetEnableMouseDriver              ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetEnableMouseDriver(void)
 {
  if(MON)
  {
   asm MOV AX,0x0020;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      SetGraphPtrBlock                ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetGraphPtrBlock(Word Hori, Word Vert, const *Buffer)
 {
  if(MON)
  {
   asm LES DX,Buffer;
   asm MOV AX,0x0009;
   asm MOV BX,Hori;
   asm MOV CX,Vert;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      SetMickeyRatio                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetMickeyRatio(int X, int Y)
 {
  if(MON)
  {
   asm MOV AX,0x000F;
   asm MOV CX,X;
   asm MOV DX,Y;
   asm INT 0x33;
   MPRX = X;
   MPRY = Y;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    SetMinMaxHoriPtrPos               ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetMinMaxHoriPtrPos(Word X1, Word X2)
 {
  if(MON)
  {
   asm MOV AX,0x0007;
   asm MOV CX,X1;
   asm MOV DX,X2;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    SetMinMaxVertPtrPos               ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetMinMaxVertPtrPos(Word Y1, Word Y2)
 {
  if(MON)
  {
   asm MOV AX,0x0008;
   asm MOV CX,Y1;
   asm MOV DX,Y2;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                         SetMouse                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetMouse(Byte Mode)
 {
  MON = Mode;
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    SetMouseLanguage                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetMouseLanguage(Word Langue)
 {
  if(MON)
  {
   asm MOV AX,0x0022;
   asm MOV BX,Langue;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       SetMouseSpeed                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetMouseSpeed(Word Speed)
 {
  if(MON)
  {
   asm MOV AX,0x0013;
   asm MOV DX,Speed;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       SetPageMouse                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetPageMouse(Word Page)
 {
  if(MON)
  {
   asm MOV AX,0x001D;
   asm MOV BX,Page;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                         SetPtrPos                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetPtrPos(Word X, Word Y)
 {
  if(MON)
  {
   asm MOV AX,0x0004;
   asm MOV CX,X;
   asm MOV DX,Y;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    SetSubCenterPress                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetSubCenterPress(const *SubProg)
 {
  if(MON)
  {
   asm LES DX,SubProg;
   asm MOV AX,0x0018;
   asm MOV CX,5;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    SetSubCenterRelease               ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetSubCenterRelease(const *SubProg)
 {
  if(MON)
  {
   asm LES DX,SubProg;
   asm MOV AX,0x0018;
   asm MOV CX,6;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      SetSubMouse                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetSubMouse(Word Num, const *SubProg)
 {
  if(MON)
  {
   asm LES DX,SubProg;
   asm MOV AX,0x0018;
   asm MOV CX,Num;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      SetSubMove                      ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetSubMove(const *SubProg)
 {
  if(MON)
  {
   asm LES DX,SubProg;
   asm MOV AX,0x0018;
   asm XOR CX,CX;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                      SetSubLeftPress                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetSubLeftPress(const *SubProg)
 {
  if(MON)
  {
   asm LES DX,SubProg;
   asm MOV AX,0x0018;
   asm MOV CX,1;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     SetSubLeftRelease                ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetSubLeftRelease(const *SubProg)
 {
  if(MON)
  {
   asm LES DX,SubProg;
   asm MOV AX,0x0018;
   asm MOV CX,2;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     SetSubRightPress                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetSubRightPress(const *SubProg)
 {
  if(MON)
  {
   asm LES DX,SubProg;
   asm MOV AX,0x0018;
   asm MOV CX,3;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                    SetSubRightRelease                ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetSubRightRelease(const *SubProg)
 {
  if(MON)
  {
   asm LES DX,SubProg;
   asm MOV AX,0x0018;
   asm MOV CX,4;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       SetTextMouse                   ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetTextMouse(Word Mode, Word Start, Word End)
 {
  if(MON)
  {
   asm MOV AX,0x000A;
   asm MOV BX,Mode;
   asm MOV CX,Start;
   asm MOV DX,End;
   asm INT 0x33;
   Msk = Mode;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     SetTextMouseHard                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetTextMouseHard(Word Start, Word End)
 {
  if(MON)
  {
   asm MOV AX,0x000A;
   asm MOV BX,1;
   asm MOV CX,Start;
   asm MOV DX,End;
   asm INT 0x33;
   Msk = 1;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     SetTextMouseSoft                 ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void SetTextMouseSoft(Word xAND, Word xXOR)
 {
  if(MON)
  {
   asm MOV AX,0x000A;
   asm XOR BX,BX;
   asm MOV CX,xAND;
   asm MOV DX,xXOR;
   asm INT 0x33;
   Msk = 0;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                        ShowPtr                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void ShowPtr(void)
 {
  if(MON)
  {
   asm MOV AX,0x0001;
   asm INT 0x33;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     ReleaseKeyMouse                  ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 void ReleaseKeyMouse(void)
 {
  Word ButtonMouse;
  ButtonMouse = 0xFFFF;
  while(ButtonMouse > 0)
  {
   asm MOV AX,0x0003;
   asm INT 0x33;
   ButtonMouse = _BX;
  }
 }

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                     SetSubMouse_                     ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 #ifndef __PASCAL__

  void SetSubMouse_(Word Num, const *Routine)
  {
   SetSubMouse(Num,FP_SEG(Routine),FP_OFF(Routine));
  }

 #endif

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       SetSubMove_                    ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 #ifndef __PASCAL__

  void SetSubMove_(const *Routine)
  {
   SetSubMove(FP_SEG(Routine),FP_OFF(Routine));
  }

 #endif

#endif
