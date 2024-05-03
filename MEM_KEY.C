/**********************************************************************/
/*                                                                    */
/*                     Malte System/Direct Keyboard                   */
/*                            1992/10/18                              */
/*                                                                    */
/*              Copyright (C) par les Chevaliers de Malte             */
/*                                                                    */
/**********************************************************************/

//
//     *** Summary information ***
//
//  The file name is        : MEM_KEY.C
//  The header file name is : MEM_KEY.H
//  Created the             : 1992/08/14
//  Author is               : Sylvain Maltais
//

#include <MEM_KEY.H>

Byte MEM_KeyPressed(void)
{
 asm XOR AX,AX;
 asm MOV ES,AX;
 asm MOV DX,ES:[0x041A];
 asm CMP DX,ES:[0x041C];
 asm JE  V0;
 return(1);
 V0:
 return(0);
}

Word MEM_NextKey(void)
{
 asm MOV AX,0x0040;
 asm MOV ES,AX;
 asm MOV DI,ES:[0x001A];
 asm MOV AX,ES:[DI];
 return(_AX);
}

Word MEM_ReadKey(void)
{
 asm XOR AX,AX;
 asm MOV ES,AX;
 asm MOV SI,0x041A;
L:
 asm MOV DI,ES:[SI];
 asm CMP DI,ES:[0x041C];
 asm JE  L;
 asm MOV BX,ES:[0x0480];
 asm MOV CX,ES:[0x0482];
 asm SUB CX,BX;
 asm MOV AX,ES:[DI];
 asm SUB DI,BX;
 asm ADD DI,6;
 asm AND DI,CX;
 asm ADD DI,BX;
 asm MOV ES:[SI],DI;
 return(_AX);
}

Byte MEM_KeyFlags(void)
{
 asm XOR AX,AX;
 asm MOV ES,AX;
 asm MOV AL,ES:[0x0417];
 return(_AL);
}

Byte MEM_GetModeInsert(void)
{
 asm XOR AX,AX;
 asm MOV ES,AX;
 asm MOV AL,ES:[0x0417];
 asm ROL AL,1;
 asm AND AL,1;
 return(_AL);
}