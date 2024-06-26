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
// Derni�re modification :
//
//  Jeudi, le 1 juin 1993 (UpDate all function).
//
// Directive de compilation conditionnel :
//
// __PASCAL__   Indique qu'il doit fonctionner avec le
//              compilateur Turbo Pascal 4 ou post�rieur.
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

// ������������������������������������������������������Ŀ
// �                      ExcludeZone                     ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                      GetButPos                       ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                      GetButPress                     ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                      GetButRelease                   ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                   GetMickeyPixelRatio                ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 void GetMickeyPixelRatio(int *X, int *Y)
 {
  *X = MPRX;
  *Y = MPRY;
 }

// ������������������������������������������������������Ŀ
// �                   GetMotionCounters                  ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                       GetMouse                       ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 Byte GetMouse(void)
 {
  return(MON);
 }

// ������������������������������������������������������Ŀ
// �                    GetMouseLanguage                  ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                      GetPageMouse                    ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                      GetSetupMouse                   ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                   GetSizeMouseBuffer                 ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                       GetTextMouse                   ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 Word GetTextMouse(void)
 {
  return(Msk);
 }

// ������������������������������������������������������Ŀ
// �                         HidePtr                      ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 void HidePtr(void)
 {
  if(MON)
  {
   asm MOV AX,0x0002;
   asm INT 0x33;
  }
 }

// ������������������������������������������������������Ŀ
// �                     LightPenEmulOff                  ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 void LightPenEmulOff(void)
 {
  if(MON)
  {
   asm MOV AX,0x000E;
   asm INT 0x33;
  }
 }

// ������������������������������������������������������Ŀ
// �                      LightPenEmulOn                  ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 void LightPenEmulOn(void)
 {
  if(MON)
  {
   asm MOV AX,0x000D;
   asm INT 0x33;
  }
 }

// ������������������������������������������������������Ŀ
// �                      MouseResetStat                  ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                     MouseSoftWareStat                ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                    RestoreMouseBuffer                ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 void RestoreMouseBuffer(const *Buffer)
 {
  if(MON)
  {
   asm LES DX,Buffer;
   asm MOV AX,0x17;
   asm INT 0x33;
  }
 }

// ������������������������������������������������������Ŀ
// �                      SaveMouseBuffer                 ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 void SaveMouseBuffer(const *Buffer)
 {
  if(MON)
  {
   asm LES DX,Buffer;
   asm MOV AX,0x16;
   asm INT 0x33;
  }
 }

// ������������������������������������������������������Ŀ
// �                   SetDisableMouseDriver              ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                    SetEnableMouseDriver              ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 void SetEnableMouseDriver(void)
 {
  if(MON)
  {
   asm MOV AX,0x0020;
   asm INT 0x33;
  }
 }

// ������������������������������������������������������Ŀ
// �                      SetGraphPtrBlock                ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                      SetMickeyRatio                  ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                    SetMinMaxHoriPtrPos               ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                    SetMinMaxVertPtrPos               ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                         SetMouse                     ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 void SetMouse(Byte Mode)
 {
  MON = Mode;
 }

// ������������������������������������������������������Ŀ
// �                    SetMouseLanguage                  ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 void SetMouseLanguage(Word Langue)
 {
  if(MON)
  {
   asm MOV AX,0x0022;
   asm MOV BX,Langue;
   asm INT 0x33;
  }
 }

// ������������������������������������������������������Ŀ
// �                       SetMouseSpeed                  ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 void SetMouseSpeed(Word Speed)
 {
  if(MON)
  {
   asm MOV AX,0x0013;
   asm MOV DX,Speed;
   asm INT 0x33;
  }
 }

// ������������������������������������������������������Ŀ
// �                       SetPageMouse                   ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 void SetPageMouse(Word Page)
 {
  if(MON)
  {
   asm MOV AX,0x001D;
   asm MOV BX,Page;
   asm INT 0x33;
  }
 }

// ������������������������������������������������������Ŀ
// �                         SetPtrPos                    ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                    SetSubCenterPress                 ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                    SetSubCenterRelease               ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                      SetSubMouse                     ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                      SetSubMove                      ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                      SetSubLeftPress                 ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                     SetSubLeftRelease                ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                     SetSubRightPress                 ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                    SetSubRightRelease                ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                       SetTextMouse                   ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                     SetTextMouseHard                 ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                     SetTextMouseSoft                 ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                        ShowPtr                       ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 void ShowPtr(void)
 {
  if(MON)
  {
   asm MOV AX,0x0001;
   asm INT 0x33;
  }
 }

// ������������������������������������������������������Ŀ
// �                     ReleaseKeyMouse                  ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

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

// ������������������������������������������������������Ŀ
// �                     SetSubMouse_                     ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 #ifndef __PASCAL__

  void SetSubMouse_(Word Num, const *Routine)
  {
   SetSubMouse(Num,FP_SEG(Routine),FP_OFF(Routine));
  }

 #endif

// ������������������������������������������������������Ŀ
// �                       SetSubMove_                    ��
// ���������������������������������������������������������
//  ��������������������������������������������������������

 #ifndef __PASCAL__

  void SetSubMove_(const *Routine)
  {
   SetSubMove(FP_SEG(Routine),FP_OFF(Routine));
  }

 #endif

#endif
