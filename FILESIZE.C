/********************************************************/
/*                                                      */
/*             Malte System/Handle File Size            */
/*                     1993/05/15                       */
/*                                                      */
/*       Copyright (C) par les Chevaliers de Malte      */
/*                                                      */
/********************************************************/

//
// Programmeur :
//
//  Sylvain Maltais
//
// Compatible :
//
//  Turbo Pascal 4.xx ou post‚rieur,
//  Turbo C++ ou post‚rieur
//

// *******************************************************
//                   INTERFACE/HEADER
// *******************************************************

#include <NUMERIC.H>

extern LongInt FileSize(Word Handle);

// *******************************************************
//                     IMPLEMENTATION
// *******************************************************

extern Word FileError;

#ifndef __HandleFileSize__
 #define __HandleFileSize__

// ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
// ³                       FileSize                       ³Û
// ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÛ
//  ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß

 #if defined(__286__) || defined(__386__)

  LongInt FileSize(Word Handle)
  {
   asm MOV  AX,0x4202;
   asm MOV  BX,Handle;
   asm XOR  CX,CX;
   asm XOR  DX,DX;
   asm INT  0x21;
   asm JC   Error;
   asm PUSH 0x0000;
   asm POP  FileError;
   return(_AX + (_DX << 16));
Error:
   asm MOV FileError,AX;
   return(-1);
  }

 #else

  LongInt FileSize(Word Handle)
  {
   asm MOV AX,0x4202;
   asm MOV BX,Handle;
   asm XOR CX,CX;
   asm XOR DX,DX;
   asm INT 0x21;
   asm JC  Error;
   asm MOV FileError,0;
   return(_AX + (_DX << 16));
Error:
   asm MOV FileError,AX;
   return(-1);
  }

 #endif

#endif