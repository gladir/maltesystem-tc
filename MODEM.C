#include <DOS.H>
#include <stdio.h>

typedef unsigned char Byte;
typedef unsigned int  Word;

Word RS232State;

Byte NumRS232(void)
{
 struct REGPACK reg;
 Byte Temp;
 intr(0x11,&reg);
 Temp = (reg.r_ax & 0x0E00) >> 9;
 if(Temp > 2) Temp = 2;
 return(Temp);
}

// Port = '1'..'8' (COM1, COM2, ...)
// retour :
//          253  Vitesse invalide.
//          254  Port invalide.

Byte InitRS232(Byte Port, Word Speed, Byte Parity, Byte Data, Byte Stop)
{
 struct REGPACK reg;
 unsigned T;
 if(Port < 49) return(254);
 reg.r_dx = Port-49;
 T = 0;
 switch (Speed)
 {
  case 110  : T=1;reg.r_ax = 0;
  case 150  : T=1;reg.r_ax = 32;
  case 300  : T=1;reg.r_ax = 64;
  case 600  : T=1;reg.r_ax = 96;
  case 1200 : T=1;reg.r_ax = 128;
  case 2400 : T=1;reg.r_ax = 160;
  case 4800 : T=1;reg.r_ax = 192;
  case 9600 : T=1;reg.r_ax = 224;
 }
 if(T == 0) return(253);
 T = 0;
 switch (Parity)
 {
  case 'N' : T=1;reg.r_ax = reg.r_ax | 0;
  case 'O' : T=1;reg.r_ax = reg.r_ax | 8;
  case 'E' : T=1;reg.r_ax = reg.r_ax | 24;
  case 'n' : T=1;reg.r_ax = reg.r_ax | 0;
  case 'o' : T=1;reg.r_ax = reg.r_ax | 8;
  case 'e' : T=1;reg.r_ax = reg.r_ax | 24;
 }
 if(T == 0) return(252);
 T = 0;
 switch (Data)
 {
  case 7  : T=1;reg.r_ax = reg.r_ax | 2;
  case 8  : T=1;reg.r_ax = reg.r_ax | 3;
 }
 if(T == 0) return(251);
 T = 0;
 switch (Stop)
 {
  case 1  : T=1;reg.r_ax = reg.r_ax | 0;
  case 2  : T=1;reg.r_ax = reg.r_ax | 4;
 }
 if(T == 0) return(250);
 intr(0x14,&reg);
 RS232State = reg.r_ax;
 return(0);
}

Byte RS232Ready(Byte Port)
{
 struct REGPACK reg;
 if(Port < 49) return(254);
 reg.r_ax = 0x0300;
 reg.r_dx = Port-49;
 intr(0x14,&reg);
 RS232State = reg.r_ax;
 if((reg.r_ax & 0x0300) == 0) return(0);
			 else return(1);

}

Byte RS232Send(Byte Port, Byte *String)
{
 const Delay = 250;
 struct REGPACK reg;
 Byte K,L;
 Word I;
 for(I = 0;String[I];I++)
 {
  L = 0;
  while((L < Delay)&&(RS232Ready(Port) == 0)) L++;
  if(L >= Delay) return(249);
  reg.r_ax = 0x0100 + String[I];
  reg.r_dx = Port - 49;
  intr(0x14,&reg);
  if(((reg.r_ax >> 8) & 0x8E) != 0) return(248);
 }
 return(0);
}

Byte RS232Receive(Byte Port, Byte *String)
{
 const Delay = 250;
 struct REGPACK reg;
 reg.r_dx = Port - 49;
 reg.r_ax = 0x0200;
 intr(0x14,&reg);
 String[0] = (reg.r_ax & 0xFF);
 String[1] = 0;
 return(0);
}

main()
{
 Byte Chaine[255];
 pokeb(0xB800,0,InitRS232('2',2400,'N',8,1));
 pokeb(0xB800,2,RS232Ready('2'));
 pokeb(0xB800,4,RS232Send('2',"AT S1?"));
 Chaine[0] = 0;
 while(Chaine[0] == 0)
 {
  RS232Receive('2',Chaine);
 }
 printf("%s",Chaine);
}