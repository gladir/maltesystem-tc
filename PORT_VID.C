/**********************************************************************/
/*                                                                    */
/*                   Malte System/Direct I/O Video                    */
/*                            1992/06/30                              */
/*                                                                    */
/*              Copyright (C) par les Chevaliers de Malte             */
/*                                                                    */
/**********************************************************************/

#ifndef __Malte_Video_IO__
 #define __Malte_Video_IO__

 extern void IO_Blink(char Autorise);

 void IO_Blink(char Autorise)
 {
  asm MOV AX,0x0040;
  asm MOV ES,AX;
  asm MOV DX,ES:[0x63];
  asm ADD DX,4;
  asm MOV AL,Autorise;
  asm ROR AL,1;
  asm ROR AL,1;
  asm ADD AL,0x09;
  asm OUT DX,AL;
 }

#endif