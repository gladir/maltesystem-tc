typedef unsigned char Byte;
typedef Byte String[255];

void BIOS_PutCharType(Byte X, Byte Y, Byte Char, Byte Color, Byte Fond)
{
 asm MOV AH,0x02;
 asm XOR BH,BH;
 asm MOV DL,X;
 asm MOV DH,Y;
 asm INT 0x10;
 asm MOV AH,0x0E;
 asm MOV AL,Fond;
 asm ROR AL,1;
 asm OR  AL,Char;
 asm MOV BL,Color;
 asm INT 0x10;
}

#ifdef __PASCAL__
 
 void BIOS_WriteType(Byte X, Byte Y, String Chn, Byte Color, Byte Fond)
 {
  Byte I;
  for(I = 1; I <= Chn[0]; I++) BIOS_PutCharType(X++,Y,Chn[I],Color,Fond);
 }

#endif