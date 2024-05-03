#include <DOS.H>
#include <STDIO.H>

#define TRUE	1
#define FALSE	0

typedef unsigned int Word;

unsigned FirstMCB(void)
{
 unsigned es,bx;
 _AH = 0x52;
 geninterrupt(0x21);
 es = _ES;
 bx = _BX;
 return(peek(es, bx-2));
}

static int resident(char *signature)
{
 Word sg;
 unsigned df;
 unsigned blkseg, mcbs = FirstMCB();
 df = _DS - _psp;
 while (peekb(mcbs, 0) == 0x4d)
 {
  blkseg = peek(mcbs, 1);
  if (peek(blkseg, 0) == 0x20cd)
  {
   if (blkseg == _psp) break; /* if the transient copy */
   for (sg = 0; peekb(blkseg+df,sg); sg++)
   {
    putchar(peekb(blkseg+df, sg));
    if (signature[sg] != peekb(blkseg+df, sg)) break;
   }
   if (peekb(blkseg+df,sg) == '\0') return TRUE;
  }
  mcbs += peek(mcbs, 3) + 1;
 }
 return FALSE;
}

void main(void)
{
 pokeb(0xB800,0,48+resident("salut"));
}