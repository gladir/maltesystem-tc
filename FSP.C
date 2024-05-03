/*********************************************************************/
/*                                                                   */
/*                Malte System/FileSize (for Pascal)                 */
/*                           1992/09/17                              */
/*                                                                   */
/*             Copyright (C) par les Chevaliers de Malte             */
/*                                                                   */
/*********************************************************************/

typedef unsigned long LongWord;
typedef unsigned int Word;
typedef unsigned char Byte;

extern Word FileError;

long FileSize(Word Handle)
{
 asm MOV AX,0x4202;
 asm MOV BX,Handle;
 asm XOR CX,CX;
 asm MOV DX,CX;
 asm INT 0x21;
 asm JNC L10;
 asm MOV FileError,0;
 return((_DX << 16) + _AX);
L10:
 asm MOV FileError,AX;
 return(-1);
}