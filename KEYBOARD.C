/**********************************************************************/
/*                                                                    */
/*                       Malte System/Keyboard                        */
/*                            1992/07/08                              */
/*                                                                    */
/*              Copyright (C) par les Chevaliers de Malte             */
/*                                                                    */
/**********************************************************************/

#ifndef __Malte_Keyboard__
 #define __Malte_Keyboard__

 #ifndef __PASCAL__

  #include <KEYBOARD\MEM_KEY.H>
  #include <KEYBOARD\BIOS_KEY.H>
  #include <KEYBOARD\KEYBOARD.H>

  Byte KeyboardMethode = 0; // (0)Direct (100% compatible) /
                            // (1)BIOS / (2)DOS (Windows mode)

  Byte KeyPressed(void)
  {
   return(MEM_KeyPressed());
  }

  Word ReadKey(void)
  {
   if(KeyboardMethode == 0) return(MEM_ReadKey());
                       else return(BIOS_ReadKey());
  }

  Word NextKey(void)
  {
   if(KeyboardMethode == 0) return(MEM_NextKey());
                       else return(BIOS_NextKey());
  }

  Byte KeyFlags(void)
  {
   if(KeyboardMethode == 0) return(MEM_KeyFlags());
                       else return(BIOS_KeyFlags());
  }

  Byte GetModeInsert(void)
  {
   if(KeyboardMethode == 0) return(MEM_GetModeInsert());
                       else return(BIOS_GetModeInsert());
  }

  Byte GetKeyboardMethode(void)
  {
   return(KeyboardMethode);
  }

  void SetKeyboardMethode(Byte Methode)
  {
   if(Methode < 3) KeyboardMethode = Methode;
  }

 #else

  typedef unsigned char Byte;
  typedef unsigned int  Word;

  extern Byte KeyboardMethode; // (0)Direct (100% compatible) /
                               // (1)BIOS / (2)DOS (Windows mode)

  Byte KeyPressed(void)
  {
   {
    asm MOV AX,0x0040;
    asm MOV ES,AX;
    asm MOV DX,ES:[0x001A];
    asm CMP DX,ES:[0x001C];
    asm JE  V0;
    return(1);
    V0:
    return(0);
   }
  }

  Word ReadKey(void)
  {
   if(KeyboardMethode == 0)
   {
    asm MOV AX,0x0040;
    asm MOV ES,AX;
    asm MOV SI,0x001A;
L:  asm MOV DI,ES:[SI];
    asm CMP DI,ES:[0x001C];
    asm JE  L;
    asm MOV BX,ES:[0x0080];
    asm MOV CX,ES:[0x0082];
    asm SUB CX,BX;
    asm MOV AX,ES:[DI];
    asm SUB DI,BX;
    asm ADD DI,6;
    asm AND DI,CX;
    asm ADD DI,BX;
    asm MOV ES:[SI],DI;
    return(_AX);
   }
    else
   {
    asm MOV AH,0x00;
    asm INT 0x16;
    return(_AX);
   }
  }

  Word NextKey(void)
  {
   if(KeyboardMethode == 0)
   {
    asm MOV AX,0x0040;
    asm MOV ES,AX;
    asm MOV DI,ES:[0x001A];
    asm MOV AX,ES:[DI];
    return(_AX);
   }
    else
   {
    asm MOV AH,0x01;
    asm INT 0x16;
    return(_AX);
   }
  }

  Byte KeyFlags(void)
  {
   if(KeyboardMethode == 0)
   {
    asm MOV AX,0x0040;
    asm MOV ES,AX;
    asm MOV AL,ES:[0x0017];
    return(_AL);
   }
    else
   {
    asm MOV AH,0x02;
    asm INT 0x16;
    return(_AL);
   }
  }

  Byte GetModeInsert(void)
  {
   if(KeyboardMethode == 0)
   {
    asm MOV AX,0x0040;
    asm MOV ES,AX;
    asm MOV AL,ES:[0x0017];
    asm ROL AL,1;
    asm AND AL,1;
    return(_AL);
   }
    else
   {
    asm MOV AH,0x02;
    asm INT 0x16;
    return((_AL >> 7) & 1);
   }
  }

  Byte GetKeyboardMethode(void)
  {
   return(KeyboardMethode);
  }

  void SetKeyboardMethode(Byte Methode)
  {
   if(Methode < 3) KeyboardMethode = Methode;
  }

  Byte KeyFlagsAT(void)
  {
   asm MOV AX,0x0040;
   asm MOV ES,AX;
   asm MOV AL,ES:[0x0018];
   return(_AL);
  }

 #endif

#endif
