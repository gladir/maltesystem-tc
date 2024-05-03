/********************************************************************/
/*                                                                  */
/*                      Malte System/BIOS VGA/PS2                   */
/*                             1992/10/18                           */
/*                                                                  */
/*              Copyright (C) par les Chevaliers de Malte           */
/*                                                                  */
/********************************************************************/

//
//       *** Summary information ***
//
//  The file name is        : BIOS_VGA.C
//  The header file name is : VIDEO\VGA\BIOS_VGA.H
//  Created the             : 1992/06/12
//  Author is               : Sylvain Maltais
//

#include "DOS.H"
#include <VIDEO\VGA\BIOS_VGA.H>

Word BIOS_GetVideoCardPrim(void)
{
 asm MOV AX,0x1A00;
 asm INT 0x10;
 asm CMP AL,0x1A;
 asm JNE Not_Support;
 asm XOR AH,AH;
 asm MOV AL,BL;
 return(_AX);
Not_Support:
 return(0xFFFF);
}

Word BIOS_GetVideoCardSec(void)
{
 asm MOV AX,0x1A00;
 asm INT 0x10;
 asm CMP AL,0x1A;
 asm JNE Not_Support;
 asm XOR AH,AH;
 asm MOV AL,BH;
 return(_AX);
Not_Support:
 return(0xFFFF);
}

Word BIOS_GetVideoCard(void)
{
 asm MOV AX,0x1A00;
 asm INT 0x10;
 asm CMP AL,0x1A;
 asm JNE Not_Support;
 asm XOR AH,AH;
 asm MOV AL,BL;
 return(_AX);
Not_Support:
 return(0xFFFF);
}

Byte BIOS_Info(Word Segment, Word Offset)
{
 asm MOV ES,Segment;
 asm MOV DI,Offset;
 asm MOV AH,0x1B;
 asm XOR BX,BX;
 asm INT 0x10;
 return(_AL);
}

Byte BIOS_VGA_PS2_Get_Line(void)
{
 Byte Table[63];
 return((BIOS_Info(FP_SEG(&Table),FP_OFF(&Table)) != 0x1B) ? 0 : Table[0x22]);
}

Word BIOS_GetNumColor(void)
{
 Byte Table[63];
 return((BIOS_Info(FP_SEG(&Table),FP_OFF(&Table)) != 0x1B) ? 0 : ((Table[0x28] << 8) + Table[0x27]));
}

Byte BIOS_GetNumPage(void)
{
 Byte Table[63];
 return((BIOS_Info(FP_SEG(&Table),FP_OFF(&Table)) != 0x1B) ? 0 : Table[0x29]);
}

Byte BIOS_GetBlinkControl(void)
{
 Word Table[31];
 BIOS_Info(FP_SEG(&Table),FP_OFF(&Table));
 asm MOV ES,Table[1];
 asm MOV SI,Table[0];
 asm ADD SI,0x0B;
 asm MOV AL,ES:[SI];
 #if (defined(_286)||defined(_80286))
  asm SHR AL,2;
 #else
  asm SHR AL,1;
  asm SHR AL,1;
 #endif
 asm AND AL,1;
 return(_AL);
}

Word BIOS_GetHeightChar(void)
{
 Byte Table[63];
 return((BIOS_Info(FP_SEG(&Table),FP_OFF(&Table)) != 0x1B) ? 0 : ((Table[0x24] << 8) + Table[0x23]));
}

Byte BIOS_GetScanLine(void)
{
 Byte Table[63];
 return((BIOS_Info(FP_SEG(&Table),FP_OFF(&Table)) != 0x1B) ? 0 : Table[0x2A]);
}

Word BIOS_GetScanLine_(void)
{
 Byte Tmp = BIOS_GetScanLine();
 if(BIOS_Info_() == 0) return(0);
 if(Tmp == 0) return(200);
 if(Tmp == 1) return(350);
 if(Tmp == 2) return(400);
 if(Tmp == 3) return(480);
 if(Tmp == 5) return(600);
 if(Tmp == 6) return(768);
 if(Tmp == 8) return(352);
 if(Tmp == 9) return(364);
 return(0);
}

void BIOS_SetPaletteVGA(Word Register, Byte Red, Byte Green, Byte Blue)
{
 asm MOV AX,0x1010;
 asm MOV BX,Register;
 asm MOV CL,Blue;
 asm MOV CH,Green;
 asm MOV DH,Red;
 asm INT 0x10;
}

void BIOS_SetMatrix8x16(Byte Table)
{
 asm MOV AX,0x1114;
 asm MOV BL,Table;
 asm INT 0x10;
}

/**********************************************************************/
/*                          C -- Zone                                 */
/**********************************************************************/

#ifndef __PASCAL__

 Byte BIOS_Info_(void)
 {
  Byte Table[63];
  return((BIOS_Info(FP_SEG(&Table),FP_OFF(&Table)) == 0x1B) ? 1 : 0);
 }

 Byte BIOS_GetBlink(void)
 {
  Byte Table[63];
  BIOS_Info(FP_SEG(&Table),FP_OFF(&Table));
  return((Table[0x2D] >> 5) & 1);
 }

#endif