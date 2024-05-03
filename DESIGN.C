#include <DOS.H>

typedef unsigned char Byte;
typedef unsigned int  Word;

void SetPolice(Byte Line, Word Start, Word Quantite, const *Buffer)
{
 struct REGPACK reg;
 reg.r_bp = FP_OFF(Buffer);
 reg.r_es = FP_SEG(Buffer);
 reg.r_ax = 0x1100;
 reg.r_bx = (Line << 8) + 0;
 reg.r_cx = Quantite;
 reg.r_dx = Start;
 intr(0x10,&reg);
}

void main(void)
{
 Byte Buffer[18] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
// _AH = 0x11;
// _AL = 0x03;
// _BL = 0x00;
// asm INT 0x10;
// _AX = 0x1114;
// _BL = 0x00;
// asm INT 0x10;
 _AX = 0x0003;
 asm INT 0x10;
 SetPolice(16,182,1,Buffer);
 pokeb(0xB800,0,182);
 _AH = 0;
 asm INT 0x16;
}