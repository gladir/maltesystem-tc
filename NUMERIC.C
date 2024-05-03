/********************************************************************/
/*                                                                  */
/*                        Malte System/Numeric                      */
/*                             1992/07/02                           */
/*                                                                  */
/*              Copyright (C) par les Chevaliers de Malte           */
/*                                                                  */
/********************************************************************/

#ifndef __Malte_Numerique__
 #define __Malte_Numerique__

 #include <NUMERIC.H>

 void ChgChr(Byte *A, Byte *B)
 {
  Byte C = A[0];
  A[0]   = B[0];
  B[0]   = C;
 }

 void ChgWord(Word *A, Word *B)
 {
  Word C = A[0];
  A[0]   = B[0];
  B[0]   = C;
 }

 void ChgDWord(LongWord *A, LongWord *B)
 {
  LongWord C = A[0];
  A[0]       = B[0];
  B[0]       = C;
 }

 #ifndef __PASCAL__

  void FillChar(Word Segment, Word Offset, Word Taille, Byte Valeur)
  {
   asm MOV AX,Segment;
   asm MOV ES,AX;
   asm MOV AL,Valeur;
   asm MOV DI,Offset;
   asm MOV CX,Taille;
   asm DEC CX;
   asm CLD;
   asm REP STOSB;
  }

 #endif

#endif