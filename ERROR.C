/*****************************************************************/
/*                                                               */
/*                    Malte System/Gadget Error                  */
/*                           1992/08/01                          */
/*                                                               */
/*           Copyright (C) par les Chevaliers de Malte           */
/*                                                               */
/*****************************************************************/

#ifndef __Gadget_Error__
 #define __Gadget_Error__

 #include <STRING.H>
 #include <TRANSLTR.H>
 #include <VIDEO\WINDOW.H>
 #include <GADGET\ERROR.H>

 void StrErrorMessage(Byte Langue, Word Error, Byte *Phr)
 {
  if(Langue == 1)
  {
   switch(Error)
   {
    case 0x00 : *Phr = "No error";
    case 0x01 : *Phr = "Invalid function number";
    case 0x02 : *Phr = "File not found";
    case 0x03 : *Phr = "Path not found";
    case 0x04 : *Phr = "Too many open file";
    case 0x05 : *Phr = "Access denied";
    case 0x06 : *Phr = "Invalid handle";
    case 0x07 : *Phr = "Memory block destroyed";
    case 0x08 : *Phr = "Out of memory";
    case 0x09 : *Phr = "Invalid memory block address";
    case 0x0A : *Phr = "Invalid environnement";
    case 0x0B : *Phr = "Invalid format";
    case 0x0C : *Phr = "Invalid access code";
    case 0x0D : *Phr = "Invalid data";
    case 0x0E : *Phr = "Unknown error";
    case 0x0F : *Phr = "Invalid drive";
    case 0x10 : strcpy(Phr,"Attempt to remove this path");
    case 0x11 : strcpy(Phr,"No-compatible support");
    case 0x12 : strcpy(Phr,"Not next file");
    case 0x13 : strcpy(Phr,"Drive is write-protect");
    case 0x14 : strcpy(Phr,"Unknown unit");
    case 0x15 : strcpy(Phr,"Disk not-ready");
    case 0x16 : strcpy(Phr,"Invalid command");
    case 0x17 : strcpy(Phr,"CRC error");
    case 0x18 : strcpy(Phr,"Invalid length data");
    case 0x19 : strcpy(Phr,"Seek error");
    case 0x1A : strcpy(Phr,"Disk non-DOS");
    case 0x1B : strcpy(Phr,"Sector not found");
    case 0x1C : strcpy(Phr,"Out of paper");
    case 0x1D : strcpy(Phr,"Write error");
    case 0x1E : strcpy(Phr,"Read error");
    case 0x1F : strcpy(Phr,"General Error");
    case 0x20 : strcpy(Phr,"Common resource violation");
    case 0x21 : strcpy(Phr,"Protect zone violation");
    case 0x22 : strcpy(Phr,"Invalid change disk");
    case 0x23 : strcpy(Phr,"Too many FCB");
    case 0x24 : strcpy(Phr,"Commun buffer domaged");
    case 0x32 : strcpy(Phr,"Network not support option");
    case 0x33 : strcpy(Phr,"Time-out Network");
    case 0x34 : strcpy(Phr,"Duplication NetWork name");
    case 0x35 : strcpy(Phr,"Network not found");
    case 0x36 : strcpy(Phr,"Network busy");
    case 0x37 : strcpy(Phr,"Streamer not found in Network");
    case 0x38 : strcpy(Phr,"BIOS Command domaged in Network");
    case 0x39 : strcpy(Phr,"Connect error Network");
    case 0x3A : strcpy(Phr,"Answer error Network");
    case 0x3B : strcpy(Phr,"Network error");
    case 0x3C : strcpy(Phr,"File creation error");
    case 0x3D : strcpy(Phr,"Spooler is full");
    case 0x3E : strcpy(Phr,"Spooler not full");
    case 0x3F : strcpy(Phr,"Spooler in disk is full");
    case 0x40 : strcpy(Phr,"Network name is erased");
    case 0x41 : strcpy(Phr,"Network access denied");
    case 0x42 : strcpy(Phr,"Invalid Network streamer");
    case 0x43 : strcpy(Phr,"Network name not found");
    case 0x44 : strcpy(Phr,"Network name not Update");
    case 0x45 : strcpy(Phr,"Network name breath out");
    case 0x46 : strcpy(Phr,"Tempory wait");
    case 0x47 : strcpy(Phr,"Request denied");
    case 0x48 : strcpy(Phr,"Spooler tempory wait");
    case 0x50 : strcpy(Phr,"File exist");
    case 0x52 : strcpy(Phr,"Creation path error");
    case 0x53 : strcpy(Phr,"Interrupt 24h error");
    case 0x54 : strcpy(Phr,"Domaged struct");
    case 0x55 : strcpy(Phr,"File already");
    case 0x56 : strcpy(Phr,"Invalid password");
    case 0x57 : strcpy(Phr,"Invalid Parameters");
    case 0x58 : strcpy(Phr,"Write error in Network");
    default   : strcpy(Phr,"Unknown error");
   }
  }
   else
  {
   switch (Error)
   {
    case 0x00 : strcpy(Phr,"Il n'y a pas d'erreur");
    case 0x01 : strcpy(Phr,"Num‚ro fonction inconnu");
    case 0x02 : strcpy(Phr,"Fichier non-trouv‚");
    case 0x03 : strcpy(Phr,"Chemin non-trouv‚");
    case 0x04 : strcpy(Phr,"Plus de handle disponible");
    case 0x05 : strcpy(Phr,"AccŠs refus‚");
    case 0x06 : strcpy(Phr,"Handle inconnu");
    case 0x07 : strcpy(Phr,"Bloc de contr“le de la m‚moire d‚truit");
    case 0x08 : strcpy(Phr,"M‚moire disponible insuffisante");
    case 0x09 : strcpy(Phr,"Adresse m‚moire incorrecte");
    case 0x0A : strcpy(Phr,"Environnement incorrect");
    case 0x0B : strcpy(Phr,"Format incorrect");
    case 0x0C : strcpy(Phr,"Code accŠs incorrect");
    case 0x0D : strcpy(Phr,"Donn‚es incorrectes");
    case 0x0E : strcpy(Phr,"Erreur inconnu");
    case 0x0F : strcpy(Phr,"Lecteur inconnu");
    case 0x10 : strcpy(Phr,"Tentative de destruction ce r‚pertoire");
    case 0x11 : strcpy(Phr,"P‚riph‚riques diff‚rents");
    case 0x12 : strcpy(Phr,"Plus d'autre fichier");
    case 0x13 : strcpy(Phr,"Support prot‚g‚ contre ‚criture");
    case 0x14 : strcpy(Phr,"P‚riph‚rique inconnu");
    case 0x15 : strcpy(Phr,"P‚riph‚rique n'est pas prˆt");
    case 0x16 : strcpy(Phr,"Instruction inconnue");
    case 0x17 : strcpy(Phr,"Erreur CRC");
    case 0x18 : strcpy(Phr,"Largeur de donn‚es incorrecte");
    case 0x19 : strcpy(Phr,"Recherche infructueuse");
    case 0x1A : strcpy(Phr,"Disque incompatible au DOS");
    case 0x1B : strcpy(Phr,"Secteur non-trouv‚");
    case 0x1C : strcpy(Phr,"Plus de papier dans l'imprimante");
    case 0x1D : strcpy(Phr,"Erreur d'‚criture");
    case 0x1E : strcpy(Phr,"Erreur de lecture");
    case 0x1F : strcpy(Phr,"Erreur g‚n‚rale");
    case 0x20 : strcpy(Phr,"Violation d'une ressource commune");
    case 0x21 : strcpy(Phr,"Violation d'une zone prot‚g‚e");
    case 0x22 : strcpy(Phr,"Changement de disque non-autoris‚");
    case 0x23 : strcpy(Phr,"FCB indisponible");
    case 0x24 : strcpy(Phr,"Saturation du buffer commun");
    case 0x32 : strcpy(Phr,"Demande non-support‚ par le r‚seau local");
    case 0x33 : strcpy(Phr,"Pas de r‚ponse du r‚seau");
    case 0x34 : strcpy(Phr,"Nom dupliqu‚ sur le r‚seau");
    case 0x35 : strcpy(Phr,"Nom du r‚seau non-trouv‚");
    case 0x36 : strcpy(Phr,"R‚seau occup‚");
    case 0x37 : strcpy(Phr,"P‚riph‚rique n'existe plus sur le r‚seau");
    case 0x38 : strcpy(Phr,"Saturation des commandes du BIOS du r‚seau");
    case 0x39 : strcpy(Phr,"Erreur dand le mat‚riel");
    case 0x3A : strcpy(Phr,"R‚ponse incorrecte du r‚seau");
    case 0x3B : strcpy(Phr,"Erreur de r‚seau");
    case 0x3C : strcpy(Phr,"Erreur de cr‚ation de fichier");
    case 0x3D : strcpy(Phr,"File d'impression pleine");
    case 0x3E : strcpy(Phr,"Queue d'impression non-pleine");
    case 0x3F : strcpy(Phr,"Taille du disque insuffisante pour impression");
    case 0x40 : strcpy(Phr,"Nom du r‚seau effac‚");
    case 0x41 : strcpy(Phr,"AccŠs r‚seau refus‚");
    case 0x42 : strcpy(Phr,"P‚riph‚rique de r‚seau incorrect");
    case 0x43 : strcpy(Phr,"Nom de r‚seau non-trouv‚");
    case 0x44 : strcpy(Phr,"Limite du nom de r‚seau d‚pass‚e");
    case 0x45 : strcpy(Phr,"Limite de la dur‚e d'une session d‚pass‚e");
    case 0x46 : strcpy(Phr,"Pause temporaire");
    case 0x47 : strcpy(Phr,"Demande refus‚e");
    case 0x48 : strcpy(Phr,"Impression temporairement arrˆt‚e");
    case 0x50 : strcpy(Phr,"Fichier d‚ja existant");
    case 0x51 : strcpy(Phr,"Erreur Inconnu");
    case 0x52 : strcpy(Phr,"Le r‚pertoire ne peut ˆtre cr‚‚");
    case 0x53 : strcpy(Phr,"Erreur d'interruption 24h");
    case 0x54 : strcpy(Phr,"Saturation des structures");
    case 0x55 : strcpy(Phr,"D‚j… assign‚");
    case 0x56 : strcpy(Phr,"Mots de passe incorrect");
    case 0x57 : strcpy(Phr,"ParamŠtre incorrect");
    case 0x58 : strcpy(Phr,"Erreur d'‚criture sur le r‚seau");
    default   : strcpy(Phr,"Erreur Inconnu");
   }
  }
 }

 void PutErrorLn_W(Byte Langue, Byte *Message)
 {
  if(Langue == 1) WriteText_W("Error");
	     else WriteText_W("Erreur");
  WriteText_W(" : ");
  WriteText_W(Message);
  WriteTextLn_W("!");
 }

 void PutErrorNumLn_W(Byte Langue, Word Numero, Byte *Message)
 {
  if(Langue == 1) WriteText_W("Error");
	     else WriteText_W("Erreur");
  WriteText_W(" ");
  {
   Byte Chn[10];
   Hex65535Chn(Numero,Chn);
   WriteText_W(Chn);
  }
  WriteText_W("h : ");
  WriteText_W(Message);
  WriteTextLn_W("!");
 }

 void PutErrorMsgLn_W(Byte Langue, Word Error)
 {
  Byte Chn[80];
  StrErrorMessage(Langue,Error,Chn);
  PutErrorNumLn_W(Langue,Error,Chn);
 }

#endif