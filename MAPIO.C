typedef unsigned int  Word;
typedef unsigned char Byte;

void StrMapIOFra(Word Adresse, Byte *Buffer)
{
 if((peekb(0xFFFF,0x0E) == PC_XT)||(peekb(0xFFFF,0x0E) == PC_AT))
 {
  if(Adresse <= 0x000F) strcpy(Buffer,"Contr“leur DMA 8237A");
  if((Adresse == 0x0020)||(Adresse == 0x0021)) strcpy(Buffer,"Contr“leur d'interruption, 8259A");
  if((Adresse >= 0x0040)&&(Adresse <= 0x0043)) strcpy(Buffer,"Timer programmable 8253");
  if((Adresse >= 0x0060)&&(Adresse <= 0x006F)) strcpy(Buffer,"Contr“leur de clavier 8255A");
  if(Adresse == 0x00A0) strcpy(Buffer,"Registre de masque NMI");
  if((Adresse >= 0x0200)&&(Adresse <= 0x020F)) strcpy(Buffer,"Manette de jeu");
  if((Adresse >= 0x0210)&&(Adresse <= 0x0217)) strcpy(Buffer,"Carte d'extension");
  if((Adresse >= 0x02B0)&&(Adresse <= 0x02DF)) strcpy(Buffer,"EGA (secondaire)");
  if((Adresse >= 0x02F8)&&(Adresse <= 0x02FF)) strcpy(Buffer,"COM2");
  if((Adresse >= 0x0300)&&(Adresse <= 0x0310)) strcpy(Buffer,"Carte prototype");
  if((Adresse >= 0x0320)&&(Adresse <= 0x032F)) strcpy(Buffer,"Disque dur");
  if((Adresse >= 0x0378)&&(Adresse <= 0x037F)) strcpy(Buffer,"LPT1");
  if((Adresse >= 0x0380)&&(Adresse <= 0x0389)) strcpy(Buffer,"Communication BSC (secondaire)");
  if((Adresse >= 0x038A)&&(Adresse <= 0x038C)) strcpy(Buffer,"Communication SDLC");
  if((Adresse >= 0x0390)&&(Adresse <= 0x0393)) strcpy(Buffer,"Cluster (unit‚ 0)");
  if((Adresse >= 0x03A0)&&(Adresse <= 0x03A9)) strcpy(Buffer,"Communication BSC (primaire)");
  if((Adresse >= 0x03B0)&&(Adresse <= 0x03BF)) strcpy(Buffer,"Carte monochrome/imprimante");
  if((Adresse >= 0x03D0)&&(Adresse <= 0x03DF)) strcpy(Buffer,"CGA");
  if((Adresse >= 0x03F0)&&(Adresse <= 0x03F7)) strcpy(Buffer,"Contr“leur de disquette");
  if((Adresse >= 0x03F8)&&(Adresse <= 0x03FF)) strcpy(Buffer,"COM1");
  if((Adresse >= 0x0790)&&(Adresse <= 0x0793)) strcpy(Buffer,"Cluster (unit‚ 1)");
  if((Adresse >= 0x0B90)&&(Adresse <= 0x0B93)) strcpy(Buffer,"Cluster (unit‚ 2)");
  if((Adresse >= 0x1390)&&(Adresse <= 0x1393)) strcpy(Buffer,"Cluster (unit‚ 3)");
  if((Adresse >= 0x2390)&&(Adresse <= 0x2393)) strcpy(Buffer,"Cluster (unit‚ 4)");
 }
}