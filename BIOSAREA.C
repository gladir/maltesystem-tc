#include <ctype.h>
#include <dos.h>
#include <stdio.h>

const NumSpc = 13;

typedef unsigned char Byte;
typedef unsigned int  Word;

Byte ConstBIOSArea[89] = {
			  0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E,
			  0x10,0x12,0x13,0x15,0x17,0x18,0x19,0x1A,
			  0x1C,0x1E,0x3E,0x3F,0x40,0x41,0x42,0x49,
			  0x4A,0x4C,0x4E,0x50,0x51,0x52,0x53,0x54,
			  0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,
			  0x5D,0x5E,0x5F,0x60,0x61,0x62,0x63,0x65,
			  0x66,0x67,0x69,0x6B,0x6C,0x70,0x71,0x72,
			  0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,
			  0x7C,0x7D,0x7E,0x7F,0x80,0x82,0x84,0x85,
			  0x87,0x88,0x89,0x8B,0x8C,0x8D,0x8E,0x8F,
			  0x90,0x91,0x92,0x94,0x95,0x96,0x97,0x98,
			  0xA0
			 };

void StrMemFra(Byte Offset, Byte *Buffer)
{
 Buffer[0] = 0;
 if(Offset <= 0x01) strcpy(Buffer,"Adresse de base (port E/S) de COM1");
 if((Offset|1) == 0x03) strcpy(Buffer,"Adresse de base (port E/S) de COM2");
 if((Offset|1) == 0x05) strcpy(Buffer,"Adresse de base (port E/S) de COM3");
 if((Offset|1) == 0x07) strcpy(Buffer,"Adresse de base (port E/S) de COM4");
 if((Offset|1) == 0x09) strcpy(Buffer,"Adresse de base (port E/S) de LPT1");
 if((Offset|1) == 0x0B) strcpy(Buffer,"Adresse de base (port E/S) de LPT2");
 if((Offset|1) == 0x0D) strcpy(Buffer,"Adresse de base (port E/S) de LPT3");
 if((Offset|1) == 0x0F) strcpy(Buffer,"Adresse de base (port E/S) de LPT4");
 if((Offset|1) == 0x11) strcpy(Buffer,"Equipement (interruption 11h");
 if(Offset == 0x12) strcpy(Buffer,"R‚serv‚");
 if((Offset == 0x13)||(Offset == 0x14)) strcpy(Buffer,"Taille de la m‚moire conventionnel");
 if((Offset == 0x15)||(Offset == 0x16)) strcpy(Buffer,"R‚serv‚");
 if(Offset == 0x17) strcpy(Buffer,"Etat du clavier (hotkey)");
 if(Offset == 0x18) strcpy(Buffer,"Etat actuel du clavier");
 if(Offset == 0x19) strcpy(Buffer,"Usage ult‚rieur du clavier");
 if((Offset|1) == 0x1B) strcpy(Buffer,"Offset du prochain touche a lire");
 if((Offset|1) == 0x1D) strcpy(Buffer,"Offset de la dernier touche a lire");
 if((Offset >= 0x1E)&&(Offset <= 0x3D)) strcpy(Buffer,"Tampon du clavier");
 if(Offset == 0x3E) strcpy(Buffer,"Disque a ˆtre r‚calibr‚");
 if(Offset == 0x3F) strcpy(Buffer,"Etat des disque");
 if(Offset == 0x40) strcpy(Buffer,"Contr“le le temps des disques");
 if(Offset == 0x41) strcpy(Buffer,"Code d'erreur du disque");
 if((Offset >= 0x42)&&(Offset <= 0x48)) strcpy(Buffer,"Etat du contr“leur disque");
 if(Offset == 0x49) strcpy(Buffer,"Mode vid‚o actuel");
 if((Offset|1) == 0x4B) strcpy(Buffer,"Nombre de colonne affich‚");
 if((Offset|1) == 0x4D) strcpy(Buffer,"Taille d'un page vid‚o actuel");
 if((Offset|1) == 0x4F) strcpy(Buffer,"Offset de la page courante");
 if(Offset == 0x50) strcpy(Buffer,"Position X du curseur en page 1");
 if(Offset == 0x51) strcpy(Buffer,"Position Y du curseur en page 1");
 if(Offset == 0x52) strcpy(Buffer,"Position X du curseur en page 2");
 if(Offset == 0x53) strcpy(Buffer,"Position Y du curseur en page 2");
 if(Offset == 0x54) strcpy(Buffer,"Position X du curseur en page 3");
 if(Offset == 0x55) strcpy(Buffer,"Position Y du curseur en page 3");
 if(Offset == 0x56) strcpy(Buffer,"Position X du curseur en page 4");
 if(Offset == 0x57) strcpy(Buffer,"Position Y du curseur en page 4");
 if(Offset == 0x58) strcpy(Buffer,"Position X du curseur en page 5");
 if(Offset == 0x59) strcpy(Buffer,"Position Y du curseur en page 5");
 if(Offset == 0x5A) strcpy(Buffer,"Position X du curseur en page 6");
 if(Offset == 0x5B) strcpy(Buffer,"Position Y du curseur en page 6");
 if(Offset == 0x5C) strcpy(Buffer,"Position X du curseur en page 7");
 if(Offset == 0x5D) strcpy(Buffer,"Position Y du curseur en page 7");
 if(Offset == 0x5E) strcpy(Buffer,"Position X du curseur en page 8");
 if(Offset == 0x5F) strcpy(Buffer,"Position Y du curseur en page 8");
 if(Offset == 0x60) strcpy(Buffer,"Ligne de d‚part du curseur");
 if(Offset == 0x61) strcpy(Buffer,"Ligne d'arriv‚e du curseur");
 if(Offset == 0x62) strcpy(Buffer,"Num‚ro de la page active");
 if((Offset == 0x63)||(Offset == 0x64)) strcpy(Buffer,"Adresse de base de la carte vid‚o");
 if(Offset == 0x65) strcpy(Buffer,"Registre de s‚lection de mode");
 if(Offset == 0x66) strcpy(Buffer,"Palette de couleur utilis‚e");
 if((Offset == 0x67)||(Offset == 0x68)) strcpy(Buffer,"Pointeur de routine d'initialisation");
 if((Offset == 0x69)||(Offset == 0x6A)) strcpy(Buffer,"Pointe sur le segment ROM d'E/S");
 if(Offset == 0x6B) strcpy(Buffer,"Etat d'interruption");
 if((Offset >= 0x6C)&&(Offset <= 0x6F)) strcpy(Buffer,"Compteur de l'heure");
 if(Offset == 0x70) strcpy(Buffer,"Indicateur pass‚ minuit");
 if(Offset == 0x71) strcpy(Buffer,"Indicateur Ctrl-Break");
 if((Offset|1) == 0x73) strcpy(Buffer,"Indicateur de d‚marrage a chaud");
 if(Offset == 0x74) strcpy(Buffer,"Code erreur de disque dur");
 if(Offset == 0x75) strcpy(Buffer,"Nombre de disque dur");
 if(Offset == 0x76)
 {
  if(peekb(0xFFFF,0x0E) == 0xFE) strcpy(Buffer,"Octet de contr“le");
			    else strcpy(Buffer,"R‚serv‚");
 }
 if(Offset == 0x77)
 {
  if(peekb(0xFFFF,0x0E) == 0xFE) strcpy(Buffer,"Adresse de base du contr“leur disque dur");
			    else strcpy(Buffer,"R‚serv‚");
 }
 if(Offset == 0x78) strcpy(Buffer,"Temps maximal de r‚ponse de LPT1");
 if(Offset == 0x79) strcpy(Buffer,"Temps maximal de r‚ponse de LPT2");
 if(Offset == 0x7A) strcpy(Buffer,"Temps maximal de r‚ponse de LPT3");
 if(Offset == 0x7B) strcpy(Buffer,"Temps maximal de r‚ponse de LPT4");
 if(Offset == 0x7C) strcpy(Buffer,"Temps maximal de r‚ponse de COM1");
 if(Offset == 0x7D) strcpy(Buffer,"Temps maximal de r‚ponse de COM2");
 if(Offset == 0x7E) strcpy(Buffer,"Temps maximal de r‚ponse de COM3");
 if(Offset == 0x7F) strcpy(Buffer,"Temps maximal de r‚ponse de COM4");
 if((Offset|1) == 0x81) strcpy(Buffer,"Offset de d‚but du tampon clavier");
 if((Offset|1) == 0x83) strcpy(Buffer,"Offset de fin du tampon clavier");
 if(Offset == 0x84) strcpy(Buffer,"Nombre ligne video - 1 de l'‚cran 0");
 if((Offset == 0x85)||(Offset == 0x86)) strcpy(Buffer,"Hauteur d'un caractŠre");
 if((Offset == 0x87)||(Offset == 0x88)) strcpy(Buffer,"Pour le contr“le du vid‚o");
 if((Offset == 0x89)||(Offset == 0x8A)) strcpy(Buffer,"R‚serv‚");
 if(Offset == 0x8B) strcpy(Buffer,"Temps de transfert disquette");
 if(Offset == 0x8C) strcpy(Buffer,"Etat du contr“leur disquette");
 if(Offset == 0x8D) strcpy(Buffer,"Code d'erreur du contr“leur disquette");
 if(Offset == 0x8E) strcpy(Buffer,"Contr“le d'interruption de disque dur");
 if(Offset == 0x8F) strcpy(Buffer,"R‚serv‚");
 if(Offset == 0x90) strcpy(Buffer,"Etat de lecteur A:");
 if(Offset == 0x91) strcpy(Buffer,"Etat de lecteur B:");
 if((Offset|1) == 0x93) strcpy(Buffer,"R‚serv‚");
 if(Offset == 0x94) strcpy(Buffer,"Num‚ro de cylindre du lecteur 0");
 if(Offset == 0x95) strcpy(Buffer,"Num‚ro de cylindre du lecteur 1");
 if(Offset == 0x96) strcpy(Buffer,"Indicateur d'un clavier ‚tendu");
 if(Offset == 0x97)
 {
  if(peekb(0xFFFF,0x0E) == 252) strcpy(Buffer,"Drapeau des indicateurs lumineux");
			   else strcpy(Buffer,"R‚serv‚");
 }
 if((Offset >= 0x98)&&(Offset <= 0xA0))
 {
  if(peekb(0xFFFF,0x0E) == 252) strcpy(Buffer,"Horloge en temps-r‚el");
			   else strcpy(Buffer,"R‚serv‚");
 }
}

void StrMemSp(Byte Offset, Byte *Buffer)
{
 Buffer[0] = 0;
 if(Offset <= 0x01) strcpy(Buffer,"Port I/O in COM1");
 if((Offset|1) == 0x03) strcpy(Buffer,"Port I/O in COM2");
 if((Offset|1) == 0x05) strcpy(Buffer,"Port I/O in COM3");
 if((Offset|1) == 0x07) strcpy(Buffer,"Port I/O in COM4");
 if((Offset|1) == 0x09) strcpy(Buffer,"Port I/O in LPT1");
 if((Offset|1) == 0x0B) strcpy(Buffer,"Port I/O in LPT2");
 if((Offset|1) == 0x0D) strcpy(Buffer,"Port I/O in LPT3");
 if((Offset|1) == 0x0F) strcpy(Buffer,"Port I/O in LPT4");
 if((Offset|1) == 0x11) strcpy(Buffer,"Equipement (interrupt 11h)");
 if(Offset == 0x12) strcpy(Buffer,"Reserved");
 if((Offset == 0x13)||(Offset == 0x14)) strcpy(Buffer,"Size in conventionnal memory");
 if((Offset == 0x15)||(Offset == 0x16)) strcpy(Buffer,"Reserved");
 if(Offset == 0x17) strcpy(Buffer,"Flags in HotKey");
 if(Offset == 0x18) strcpy(Buffer,"State present in keyboard");
 if(Offset == 0x19) strcpy(Buffer,"Futur option in keyboard");
 if((Offset|1) == 0x1B) strcpy(Buffer,"Offset of next key read");
 if((Offset|1) == 0x1D) strcpy(Buffer,"Offset of previous key read");
 if((Offset >= 0x1E)&&(Offset <= 0x3D)) strcpy(Buffer,"Key buffer");
 if(Offset == 0x3E) strcpy(Buffer,"Calibrat disk");
 if(Offset == 0x3F) strcpy(Buffer,"State disk");
 if(Offset == 0x40) strcpy(Buffer,"Disk time-controler");
 if(Offset == 0x41) strcpy(Buffer,"Disk Error code");
 if((Offset >= 0x42)&&(Offset <= 0x48)) strcpy(Buffer,"State controler disk");
 if(Offset == 0x49) strcpy(Buffer,"Video mode present");
 if((Offset == 0x4A)||(Offset == 0x4B)) strcpy(Buffer,"Number of colonne in screen");
 if((Offset == 0x4C)||(Offset == 0x4D)) strcpy(Buffer,"Size of video page present");
 if((Offset == 0x4E)||(Offset == 0x4F)) strcpy(Buffer,"Offset present page");
 if(Offset == 0x50) strcpy(Buffer,"X position of curseur in page 1");
 if(Offset == 0x51) strcpy(Buffer,"Y position of curseur in page 1");
 if(Offset == 0x52) strcpy(Buffer,"X position of curseur in page 2");
 if(Offset == 0x53) strcpy(Buffer,"Y position of curseur in page 2");
 if(Offset == 0x54) strcpy(Buffer,"X position of curseur in page 3");
 if(Offset == 0x55) strcpy(Buffer,"Y position of curseur in page 3");
 if(Offset == 0x56) strcpy(Buffer,"X position of curseur in page 4");
 if(Offset == 0x57) strcpy(Buffer,"Y position of curseur in page 4");
 if(Offset == 0x58) strcpy(Buffer,"X position of curseur in page 5");
 if(Offset == 0x59) strcpy(Buffer,"Y position of curseur in page 5");
 if(Offset == 0x5A) strcpy(Buffer,"X position of curseur in page 6");
 if(Offset == 0x5B) strcpy(Buffer,"Y position of curseur in page 6");
 if(Offset == 0x5C) strcpy(Buffer,"X position of curseur in page 7");
 if(Offset == 0x5D) strcpy(Buffer,"Y position of curseur in page 7");
 if(Offset == 0x5E) strcpy(Buffer,"X position of curseur in page 8");
 if(Offset == 0x5F) strcpy(Buffer,"Y position of curseur in page 8");
 if(Offset == 0x60) strcpy(Buffer,"Start line cursor");
 if(Offset == 0x61) strcpy(Buffer,"End of line cursor");
 if(Offset == 0x62) strcpy(Buffer,"Number present page");
 if((Offset == 0x63)||(Offset == 0x64)) strcpy(Buffer,"Port I/O in video map");
 if(Offset == 0x65) strcpy(Buffer,"Register select mode");
 if(Offset == 0x66) strcpy(Buffer,"Color palette");
 if((Offset == 0x67)||(Offset == 0x68)) strcpy(Buffer,"Pointer init. sub-routine");
 if((Offset == 0x69)||(Offset == 0x6A)) strcpy(Buffer,"Pointer of segment ROM I/O");
 if(Offset == 0x6B) strcpy(Buffer,"State interrupt");
 if((Offset >= 0x6C)&&(Offset <= 0x6F)) strcpy(Buffer,"Time clock counter");
 if(Offset == 0x70) strcpy(Buffer,"Flags midnight");
 if(Offset == 0x71) strcpy(Buffer,"Flags Ctrl-Break");
 if((Offset == 0x72)||(Offset == 0x73)) strcpy(Buffer,"Flags warm boot");
 if(Offset == 0x74) strcpy(Buffer,"Hard-disk error code");
 if(Offset == 0x75) strcpy(Buffer,"Number of hard-disk");
 if(Offset == 0x76)
 {
  if(peekb(0xFFFF,0x0E) == 0xFE) strcpy(Buffer,"Controle byte");
			    else strcpy(Buffer,"Reserved");
 }
 if(Offset == 0x77)
 {
  if(peekb(0xFFFF,0x0E) == 0xFE) strcpy(Buffer,"Hard-disk port I/O");
			    else strcpy(Buffer,"Reserved");
 }
 if(Offset == 0x78) strcpy(Buffer,"Time-out LPT1");
 if(Offset == 0x79) strcpy(Buffer,"Time-out LPT2");
 if(Offset == 0x7A) strcpy(Buffer,"Time-out LPT3");
 if(Offset == 0x7B) strcpy(Buffer,"Time-out LPT4");
 if(Offset == 0x7C) strcpy(Buffer,"Time-out COM1");
 if(Offset == 0x7D) strcpy(Buffer,"Time-out COM2");
 if(Offset == 0x7E) strcpy(Buffer,"Time-out COM3");
 if(Offset == 0x7F) strcpy(Buffer,"Time-out COM4");
 if((Offset == 0x80)||(Offset == 0x81)) strcpy(Buffer,"Offset buffer key started");
 if((Offset == 0x82)||(Offset == 0x83)) strcpy(Buffer,"Offset buffer key finish");
 if(Offset == 0x84) strcpy(Buffer,"Line number video - 1 in screen 0");
 if((Offset == 0x85)||(Offset == 0x86)) strcpy(Buffer,"char height");
 if((Offset == 0x87)||(Offset == 0x88)) strcpy(Buffer,"Video controle");
 if((Offset == 0x89)||(Offset == 0x8A)) strcpy(Buffer,"Reserved");
 if(Offset == 0x8B) strcpy(Buffer,"Time transfered disk");
 if(Offset == 0x8C) strcpy(Buffer,"State floppy-disk controler");
 if(Offset == 0x8D) strcpy(Buffer,"Floppy-disk controler code error");
 if(Offset == 0x8E) strcpy(Buffer,"Interrupt controler hard-disk");
 if(Offset == 0x8F) strcpy(Buffer,"Reserved");
 if(Offset == 0x90) strcpy(Buffer,"State in drive A:");
 if(Offset == 0x91) strcpy(Buffer,"State in drive B:");
 if((Offset == 0x92)||(Offset == 0x93)) strcpy(Buffer,"Reserved");
 if(Offset == 0x94) strcpy(Buffer,"Track number in drive 0");
 if(Offset == 0x95) strcpy(Buffer,"Track number in drive 1");
 if(Offset == 0x96) strcpy(Buffer,"Flags in extended keyboard");
 if(Offset == 0x97)
 {
  if(peekb(0xFFFF,0x0E) == 252) strcpy(Buffer,"Flags light keyboard");
			   else strcpy(Buffer,"Reserved");
 }
 if((Offset >= 0x98)&&(Offset <= 0xA0))
 {
  if(peekb(0xFFFF,0x0E) == 252) strcpy(Buffer,"Real-time clock");
			   else strcpy(Buffer,"Reserved");
 }
}

void SimplifyParameter(Byte *Valeur)
{
 if((Valeur[0] == '/')||(Valeur[0] = '-'))
 {
  Word J;
  for(J = 0;J < strlen(Valeur);J++)
  {
   Valeur[J] = toupper(Valeur[J+1]);
  }
  Valeur[J+1] = 0;
 }
  else
 {
  Word J;
  for(J = 0;J < strlen(Valeur);J++)
  {
   Valeur[J] = toupper(Valeur[J]);
  }
 }
}

void printfSpace(Word Nombre)
{
 Word I;
 for(I = 1;I <= Nombre;I++) printf(" ");
}

void EnteteDescription(Byte Langue)
{
 if(Langue == 1)
 {
  printf("Malte Operator, BIOS Area, Version 1.01\n");
  printf("______________________________________________________________\n\n");
  printf("Address, Length, Value, Description\n\n");
 }
  else
 {
  printf("Op‚rateur Malte, R‚gion BIOS, Version 1.01\n");
  printf("______________________________________________________________\n\n");
  printf("Adresse, Longeur, Valeur, Description\n\n");
 }
}

void ConMem(Byte Langue)
{
 printfSpace(NumSpc);
 if(Langue == 1) printf("Conventionnal memory %dKo\n",peek(0x0040,0x13));
	    else printf("%dKo de m‚moire conventionel\n",peek(0x0040,0x13));
}

void VideoMode(Byte Langue)
{
 Byte Line;
 Line = peek(0x0040,0x0084) + 1;
 if(Line == 1) Line = 25;
 printfSpace(NumSpc);
 if(Langue == 1)
 {
  if(peekb(0x0040,0x0049) == 0) printf("40x%d, Text, BW\n",Line);
  if(peekb(0x0040,0x0049) == 1) printf("40x%d, Text, Color\n",Line);
  if(peekb(0x0040,0x0049) == 2) printf("80x%d, Text, BW\n",Line);
  if(peekb(0x0040,0x0049) == 3) printf("80x%d, Text, Color\n",Line);
  if(peekb(0x0040,0x0049) == 4) printf("320x200, Graph, 4 Color\n");
  if(peekb(0x0040,0x0049) == 5) printf("320x200, Graph, 4 Color\n");
  if(peekb(0x0040,0x0049) == 6) printf("640x200, Graph, 2 Color\n");
  if(peekb(0x0040,0x0049) == 7) printf("80x%d, Text, Mono\n",Line);
  if(peekb(0x0040,0x0049) == 8)
  {
   if(peekb(0xFFFF,0x0E) == 253) printf("160x200, Graph, 16 color\n");
			    else printf("Unknown\n");
  }
  if(peekb(0x0040,0x0049) == 0x09)
  {
   if(peekb(0xFFFF,0x0E) == 253) printf("320x200, Graph, 16 color\n");
			    else printf("Unknown\n");
  }
  if(peekb(0x0040,0x0049) == 0x0A)
  {
   if(peekb(0xFFFF,0x0E) == 253) printf("640x200, Graph, 4 color\n");
			    else printf("Unknown\n");
  }
  if(peekb(0x0040,0x0049) == 0x0B) printf("Unknown\n");
  if(peekb(0x0040,0x0049) == 0x0C) printf("Unknown\n");
  if(peekb(0x0040,0x0049) == 0x0D) printf("320x200, Graph, 16 color\n");
  if(peekb(0x0040,0x0049) == 0x0E) printf("640x200, Graph, 16 color\n");
  if(peekb(0x0040,0x0049) == 0x0F) printf("640x350, Graph, 4 color, BW\n");
  if(peekb(0x0040,0x0049) == 0x10) printf("640x350, Graph, 16 color\n");
  if(peekb(0x0040,0x0049) == 0x11) printf("640x480, Graph, 2 color\n");
  if(peekb(0x0040,0x0049) == 0x12) printf("640x480, Graph\n");
  if(peekb(0x0040,0x0049) == 0x13) printf("320x200, Graph, 256 color\n");
 }
  else
 {
  if(peekb(0x0040,0x0049) == 0) printf("Texte 40x%d, Noir & Blanc\n",Line);
  if(peekb(0x0040,0x0049) == 1) printf("Texte 40x%d, Couleur\n",Line);
  if(peekb(0x0040,0x0049) == 2) printf("Texte 80x%d, Noir & Blanc\n",Line);
  if(peekb(0x0040,0x0049) == 3) printf("Texte 80x%d, Couleur\n",Line);
  if(peekb(0x0040,0x0049) == 4) printf("Graphique 320x200, 4 Couleur\n");
  if(peekb(0x0040,0x0049) == 5) printf("Graphique 320x200, 4 Couleur\n");
  if(peekb(0x0040,0x0049) == 6) printf("Graphique 640x200, 2 Couleur\n");
  if(peekb(0x0040,0x0049) == 7) printf("Texte 80x%d, Monochrome\n",Line);
  if(peekb(0x0040,0x0049) == 8)
  {
   if(peekb(0xFFFF,0x0E) == 253) printf("Graphique 160x200, 16 couleur\n");
			    else printf("Inconnu\n");
  }
  if(peekb(0x0040,0x0049) == 0x09)
  {
   if(peekb(0xFFFF,0x0E) == 253) printf("Graphique 320x200, 16 couleur\n");
			    else printf("Inconnu\n");
  }
  if(peekb(0x0040,0x0049) == 0x0A)
  {
   if(peekb(0xFFFF,0x0E) == 253) printf("Graphique 640x200 4 couleur\n");
			    else printf("Inconnu\n");
  }
  if(peekb(0x0040,0x0049) == 0x0B) printf("Inconnu\n");
  if(peekb(0x0040,0x0049) == 0x0C) printf("Inconnu\n");
  if(peekb(0x0040,0x0049) == 0x0D) printf("Graphique 320x200, 16 couleur\n");
  if(peekb(0x0040,0x0049) == 0x0E) printf("Graphique 640x200, 16 couleur\n");
  if(peekb(0x0040,0x0049) == 0x0F) printf("Graphique 640x350, 4 couleur, Noir & Blanc\n");
  if(peekb(0x0040,0x0049) == 0x10) printf("Graphique 640x350, 16 couleur\n");
  if(peekb(0x0040,0x0049) == 0x11) printf("Graphique 640x480, 2 couleur\n");
  if(peekb(0x0040,0x0049) == 0x12) printf("Graphique 640x480\n");
  if(peekb(0x0040,0x0049) == 0x13) printf("Graphique 320x200, 256 couleur\n");
 }
}

void main(int argc, char *argv[], char *env[])
{
 Byte Hex[16] = "0123456789abcdef";
 Byte Buffer[255];
 Byte Valeur[255];
 Byte I,J,Len,Ofs;
 Byte Langue = 0, SelLan = 0;
 Byte Etendu = 0, SelEtd = 0;
 for(I = 1;I < argc;I++)
 {
  strcpy(Valeur,argv[I]);
  SimplifyParameter(Valeur);
  if((strcmp(Valeur,"CONMEM") == 0)||
     (strcmp(Valeur,"CM") == 0))
  {
   EnteteDescription(Langue);
   Len = 2;
   for(J = 0;J <= Len; J++)
   {
    Byte Val = peekb(0x0040,0x13 + (J-1));
    Valeur[(Len-J)*2]     = Hex[Val >> 4];
    Valeur[((Len-J)*2)+1] = Hex[Val & 15];
   }
   Valeur[(Len)*2] = 0;
   if(Langue == 1) StrMemSp(0x13,&Buffer);
	      else StrMemFra(0x13,&Buffer);
   printf("0040h:00%xh,  %d, %sh, %s\n",0x13,2,Valeur,Buffer);
   ConMem(Langue);
   printf("\n");
   exit(0);
  }
  if((strcmp(Valeur,"VIDEOMODE") == 0)||
     (strcmp(Valeur,"VM") == 0))
  {
   EnteteDescription(Langue);
   Len = 1;
   for(J = 0;J <= Len; J++)
   {
    Byte Val = peekb(0x0040,0x49 + (J-1));
    Valeur[(Len-J)*2]     = Hex[Val >> 4];
    Valeur[((Len-J)*2)+1] = Hex[Val & 15];
   }
   Valeur[(Len)*2] = 0;
   if(Langue == 1) StrMemSp(0x49,&Buffer);
	      else StrMemFra(0x49,&Buffer);
   printf("0040h:00%xh,  %d, %sh, %s\n",0x49,1,Valeur,Buffer);
   VideoMode(Langue);
   printf("\n");
   exit(0);
  }
  if((strcmp(Valeur,"?") == 0)||
     (strcmp(Valeur,"H") == 0)||
     (strcmp(Valeur,"HLP") == 0)||
     (strcmp(Valeur,"HELP") == 0)||
     (strcmp(Valeur,"AIDE") == 0))
  {
   if(Langue == 1)
   {
    printf("Malte Operator, BIOS Area, Version 1.01\n");
    printf("\n");
    printf("Usage : BIOSAREA [/FR|/SP][/E]");
    printf("\n\n");
    printf(" /?     Help information\n");
    printf(" /FR    Display message in french (default)\n");
    printf(" /SP    Display message in spanish\n");
    printf(" /CM    Display only the conventionnal memory size\n");
    printf(" /VM    Display only present video mode\n");
    printf(" /E     Display the extended description\n");
    printf("\n");
    exit(0);
   }
    else
   {
    printf("Op‚rateur Malte, R‚gion BIOS, Version 1.01\n");
    printf("\n");
    printf("Usage : BIOSAREA [/FR|/SP][/E]");
    printf("\n\n");
    printf(" /?     Information d'aide\n");
    printf(" /FR    Affiche les messages en francais (par d‚faut)\n");
    printf(" /SP    Affiche les messages en anglais\n");
    printf(" /CM    Affiche seulement la taille de la m‚moire conventionnel\n");
    printf(" /VM    Affiche seulement le mode vid‚o courant\n");
    printf(" /E     Affiche les descriptions ‚tendues\n");
    printf("\n");
    exit(0);
   }
  }
  if((strcmp(Valeur,"EXTENDED") == 0)||
     (strcmp(Valeur,"EXT") == 0)||
     (strcmp(Valeur,"ETENDU") == 0)||
     (strcmp(Valeur,"E") == 0))
  {
   if(SelEtd == 0)
   {
    SelEtd = 1;
    Etendu = 1;
   }
    else
   {
    if(Langue == 1) printf("Error : Parameters duplicate!\n");
	       else printf("Erreur : Duplication de paramŠtre de mˆme type!\n");
    exit(0);
   }
  }
  if((strcmp(Valeur,"FR") == 0)||
     (strcmp(Valeur,"FRA") == 0))
  {
   if(SelLan == 0)
   {
    Langue = 0;
    SelLan = 1;
   }
    else
   {
    printf("Erreur : Duplication de paramŠtre de mˆme type!\n");
    exit(0);
   }
  }
  if(strcmp(Valeur,"SP") == 0)
  {
   if(SelLan == 0)
   {
    Langue = 1;
    SelLan = 1;
   }
    else
   {
    printf("Erreur : Duplication de paramŠtre de mˆme type!\n");
    exit(0);
   }
  }
 }
 EnteteDescription(Langue);
 for(I = 0;I <= 87; I++)
 {
  Ofs = ConstBIOSArea[I];
  Len = (ConstBIOSArea[I+1] - Ofs);
  for(J = 0;J <= Len; J++)
  {
   Byte Val = peekb(0x0040,Ofs + (J-1));
   Valeur[(Len-J)*2]     = Hex[Val >> 4];
   Valeur[((Len-J)*2)+1] = Hex[Val & 15];
  }
  Valeur[(Len)*2] = 0;
  if(Langue == 1) StrMemSp(Ofs,&Buffer);
	     else StrMemFra(Ofs,&Buffer);
  if(Ofs < 15)
  {
   printf("0040h:000%xh,  %d, %sh, %s\n",Ofs,Len,Valeur,Buffer);
  }
   else
  if(Len > 9) printf("0040h:00%xh, %d, %sh, %s\n",Ofs,Len,Valeur,Buffer);
   else
  {
   if(Len == 1) printf("0040h:00%xh,  %d, %sh,   %s\n",Ofs,Len,Valeur,Buffer);
	   else printf("0040h:00%xh,  %d, %sh, %s\n",Ofs,Len,Valeur,Buffer);
  }
  if(Etendu == 1)
  {
   if(Ofs == 0x13) ConMem(Langue);
   if(Ofs == 0x17)
   {
    printfSpace(NumSpc);
    if(Langue == 1)
    {
     printf("0, 1 bit, %d right Shift flag\n",(peekb(0x0040,Ofs) & 1));
     printfSpace(NumSpc);
     printf("1, 1 bit, %d left Shift flag\n",((peekb(0x0040,Ofs) >> 1) & 1));
     printfSpace(NumSpc);
     printf("2, 1 bit, %d Ctrl flag\n",((peekb(0x0040,Ofs) >> 2) & 1));
     printfSpace(NumSpc);
     printf("3, 1 bit, %d Alt flag\n",((peekb(0x0040,Ofs) >> 3) & 1));
     printfSpace(NumSpc);
     printf("4, 1 bit, %d Scroll Lock flag\n",((peekb(0x0040,Ofs) >> 4) & 1));
     printfSpace(NumSpc);
     printf("5, 1 bit, %d Num Lock flag\n",((peekb(0x0040,Ofs) >> 5) & 1));
     printfSpace(NumSpc);
     printf("6, 1 bit, %d Caps Lock flag\n",((peekb(0x0040,Ofs) >> 6) & 1));
     printfSpace(NumSpc);
     printf("7, 1 bit, %d Insert flag\n",((peekb(0x0040,Ofs) >> 7) & 1));
    }
     else
    {
     printf("0, 1 bit, %d drapeau Shift droit\n",((peekb(0x0040,Ofs) >> 0) & 1));
     printfSpace(NumSpc);
     printf("1, 1 bit, %d drapeau Shift gauche\n",((peekb(0x0040,Ofs) >> 1) & 1));
     printfSpace(NumSpc);
     printf("2, 1 bit, %d drapeau Ctrl\n",((peekb(0x0040,Ofs) >> 2) & 1));
     printfSpace(NumSpc);
     printf("3, 1 bit, %d drapeau Alt\n",((peekb(0x0040,Ofs) >> 3) & 1));
     printfSpace(NumSpc);
     printf("4, 1 bit, %d drapeau Scroll Lock\n",((peekb(0x0040,Ofs) >> 4) & 1));
     printfSpace(NumSpc);
     printf("5, 1 bit, %d drapeau Num Lock\n",((peekb(0x0040,Ofs) >> 5) & 1));
     printfSpace(NumSpc);
     printf("6, 1 bit, %d drapeau Caps Lock\n",((peekb(0x0040,Ofs) >> 6) & 1));
     printfSpace(NumSpc);
     printf("7, 1 bit, %d drapeau Insert\n",((peekb(0x0040,Ofs) >> 7) & 1));
    }
   }
   if(Ofs == 0x18)
   {
    if(Langue == 1)
    {
     printf("0, 1 bit, %d Ctrl flag\n",((peekb(0x0040,Ofs) >> 0) & 1));
     printfSpace(NumSpc);
     printf("1, 1 bit, %d Alt flag\n",((peekb(0x0040,Ofs) >> 1) & 1));
     printfSpace(NumSpc);
     printf("2, 1 bit, %d SysReq flag\n",((peekb(0x0040,Ofs) >> 2) & 1));
     printfSpace(NumSpc);
     printf("3, 1 bit, %d Pause flag\n",((peekb(0x0040,Ofs) >> 3) & 1));
     printfSpace(NumSpc);
     printf("4, 1 bit, %d Scroll Lock flag\n",((peekb(0x0040,Ofs) >> 4) & 1));
     printfSpace(NumSpc);
     printf("5, 1 bit, %d Num Lock flag\n",((peekb(0x0040,Ofs) >> 5) & 1));
     printfSpace(NumSpc);
     printf("6, 1 bit, %d Caps Lock flag\n",((peekb(0x0040,Ofs) >> 6) & 1));
     printfSpace(NumSpc);
     printf("7, 1 bit, %d Insert flag\n",((peekb(0x0040,Ofs) >> 7) & 1));
    }
     else
    {
     printf("0, 1 bit, %d drapeau Ctrl\n",(peekb(0x0040,Ofs) & 1));
     printfSpace(NumSpc);
     printf("1, 1 bit, %d drapeau Alt\n",((peekb(0x0040,Ofs) >> 1) & 1));
     printfSpace(NumSpc);
     printf("2, 1 bit, %d drapeau SysReq\n",((peekb(0x0040,Ofs) >> 2) & 1));
     printfSpace(NumSpc);
     printf("3, 1 bit, %d drapeau Pause\n",((peekb(0x0040,Ofs) >> 3) & 1));
     printfSpace(NumSpc);
     printf("4, 1 bit, %d drapeau Scroll Lock\n",((peekb(0x0040,Ofs) >> 4) & 1));
     printfSpace(NumSpc);
     printf("5, 1 bit, %d drapeau Num Lock\n",((peekb(0x0040,Ofs) >> 5) & 1));
     printfSpace(NumSpc);
     printf("6, 1 bit, %d drapeau Caps Lock\n",((peekb(0x0040,Ofs) >> 6) & 1));
     printfSpace(NumSpc);
     printf("7, 1 bit, %d drapeau Insert\n",((peekb(0x0040,Ofs) >> 7) & 1));
    }
   }
   if(Ofs == 0x49) VideoMode(Langue);
  }
 }
 printf("\n");
}