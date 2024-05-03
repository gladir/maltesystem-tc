#include <NUMERIC.H>

Word BIOS_RAMMemory(void)
{
 asm INT 0x12;
 return(_AX); 
}

Word BIOS_Equipe(void)
{
 asm INT 0x11;
 return(_AX);
}

void BIOS_WarmBoot(void)
{
 asm MOV AX,0x0040;
 asm MOV ES,AX;
 asm MOV DX,0x1234;
 asm MOV ES:[0x0072],DX;
 asm INT 0x19;
}