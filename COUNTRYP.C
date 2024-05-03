#include <DOS.H>

#ifdef __PASCAL__

typedef unsigned char Byte;
typedef unsigned int  Word;

typedef struct {
                Word CO_DATE;
                Byte CO_CURR[5];
                Byte CO_THSEP[2];
                Byte CO_DESEP[2];
                Byte CO_DTSEP[2];
                Byte CO_TMSEP[2];
                Byte CO_CURRSTYLE;
                Byte CO_DIGITS;
                Byte CO_TIME;
                Byte CO_DASEP[2];
               }
               CountryType;

void GetCurrCountry(CountryType *C)
{
 Byte B[33];
 Word S = FP_SEG(&B), O = FP_OFF(&B);
 asm MOV AX,DS;
 asm MOV ES,AX;
 asm MOV DX,O;
 asm MOV AX,S;
 asm MOV DS,AX;
 asm MOV AX,0x3800;
 asm INT 0x21;
 asm MOV AX,ES;
 asm MOV DS,AX;
 (*C).CO_DATE = ((B[1] << 8) + B[0]);
 {
  Byte I;
  for(I = 0; B[I+2] != 0; I++);
  (*C).CO_CURR[0] = I; 
 }
 (*C).CO_CURR[1] = B[2];
 (*C).CO_CURR[2] = B[3];
 (*C).CO_CURR[3] = B[4];
 (*C).CO_CURR[4] = B[5];
 (*C).CO_CURR[5] = B[6];
 (*C).CO_THSEP[0] = (B[8] == 0 ? 1 : 2);
 (*C).CO_THSEP[1] = B[7];
 (*C).CO_THSEP[2] = B[8];
 (*C).CO_DESEP[0] = (B[10] == 0 ? 1 : 2);
 (*C).CO_DESEP[1] = B[9];
 (*C).CO_DESEP[2] = B[10];
 (*C).CO_DTSEP[0] = (B[12] == 0 ? 1 : 2);
 (*C).CO_DTSEP[1] = B[11];
 (*C).CO_DTSEP[2] = B[12];
 (*C).CO_TMSEP[0] = (B[14] == 0 ? 1 : 2);
 (*C).CO_TMSEP[1] = B[13];
 (*C).CO_TMSEP[2] = B[14];
 (*C).CO_CURRSTYLE = B[15];
 (*C).CO_DIGITS = B[16];
 (*C).CO_TIME = B[17];
 (*C).CO_DASEP[0] = (B[23] == 0 ? 1 : 2);
 (*C).CO_DASEP[1] = B[22];
 (*C).CO_DASEP[2] = B[23];
}

#endif