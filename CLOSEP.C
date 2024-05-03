/****************************************************************/
/*                                                              */
/*              Malte System/Close (for Pascal)                 */
/*                       1992/10/18                             */
/*                                                              */
/*          Copyright (C) par les Chevaliers de Malte           */
/*                                                              */
/****************************************************************/

//
//       *** Summary information ***
//
//  The file name is        : CLOSEP.C
//  The header file name is : No file (Only pascal)
//  Created the             : 1992/09/17
//  Author is               : Sylvain Maltais
//

#ifdef __PASCAL__

 typedef unsigned long LongWord;
 typedef unsigned int Word;
 typedef unsigned char Byte;

 extern Word FileError;

 void Close(Word Handle)
 {
  asm MOV AX,0x3E00;
  asm MOV BX,Handle;
  asm INT 0x21;
  asm JNC __2;
  asm XOR AX,AX;
__2:
  asm MOV FileError,AX;
 }

#endif