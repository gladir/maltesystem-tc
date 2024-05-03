/*****************************************************************/
/*                                                               */
/*                    Malte System/Disk Command                  */
/*                           1992/08/01                          */
/*                                                               */
/*           Copyright (C) par les Chevaliers de Malte           */
/*                                                               */
/*****************************************************************/

#ifndef __Disk_Command__
 #define __Disk_Command__

 #include <DOS.H>
 #include <CTYPE.H>
 #include <STRING.H>
 #include <DISK\COMMAND.H>

 Word GetCurrentDirectory(Byte *Path)
 {
  Word Sortie;
  Word Drapeau;
  _DS = FP_SEG(Path);
  _SI = FP_OFF(Path);
  _DL = 0;
  _AH = 0x47;
  asm INT 0x21;
  Sortie  = _AX;
  Drapeau = _FLAGS;
  if((Drapeau & 0x01) == 1) return(Sortie);
		       else return(0);
 }

 Word GetDirectory(Byte Drive, Byte *Path)
 {
  Word Sortie;
  Word Drapeau;
  _DS = FP_SEG(Path);
  _SI = FP_OFF(Path);
  _DL = Drive - ('A' - 1);
  _AH = 0x47;
  asm INT 0x21;
  Sortie  = _AX;
  Drapeau = _FLAGS;
  if((Drapeau & 0x01) == 1) return(Sortie);
		       else return(0);
 }

 Word ChangeDirectory(Byte *Path)
 {
  Word Sortie;
  Word Drapeau;
  _DS = FP_SEG(Path);
  _DX = FP_OFF(Path);
  _AH = 0x3B;
  asm INT 0x21;
  Sortie  = _AX;
  Drapeau = _FLAGS;
  if((Drapeau & 0x01) == 1) return(Sortie);
		       else return(0);
 }

 Word ChangeParentDirectory(void)
 {
  return(ChangeDirectory(".."));
 }

 Word ChangeRootDirectory(void)
 {
  return(ChangeDirectory("\\"));
 }

 Word MakeDirectory(Byte *Path)
 {
  Word Sortie;
  Word Drapeau;
  _DS = FP_SEG(Path);
  _DX = FP_OFF(Path);
  _AH = 0x39;
  asm INT 0x21;
  Sortie  = _AX;
  Drapeau = _FLAGS;
  if((Drapeau & 0x01) == 1) return(Sortie);
		       else return(0);
 }

 Word RemoveDirectory(Byte *Path)
 {
  Word Sortie;
  Word Drapeau;
  _DS = FP_SEG(Path);
  _DX = FP_OFF(Path);
  _AH = 0x3A;
  asm INT 0x21;
  Sortie  = _AX;
  Drapeau = _FLAGS;
  if((Drapeau & 0x01) == 1) return(Sortie);
		       else return(0);
 }

 Word RenameDirectory(Byte *Source, Byte *Target)
 {
  Byte Path[80];
  Byte Buffer[0x24];
  Byte *Ptr;
  {
   Word Temp;
   Temp = GetCurrentDirectory(Path);
   if(Temp != 0) return(Temp);
  }
  Buffer[0] = Path[0];
  {
   Byte I;
   for(I = 1;I <= 0x24;I++) Buffer[I] = 0;
   for(I = 0;I <= 11;I++)
   {
    Buffer[0x01+I] = Source[I];
    Buffer[0x11+I] = Target[I];
   }
  }
  Ptr = Buffer;
  _DS = FP_SEG(Ptr);
  _DX = FP_OFF(Ptr);
  _AH = 0x17;
  asm INT 0x21;
  return(_AL+0L);
 }

  // Le paramŠtre "Drive" doit recevoir la lettre du drive a tester.
  // Si "DriveValid" retourne 1 c'est que le drive existe sinon il
  // retournera 0.

 Byte DriveValid(Byte Drive)
 {
  asm MOV DL,Drive;
  asm MOV AH,0x36;
  asm SUB DL,'A' - 1;
  asm INT 0x21;
  asm INC AX;
  asm JE  L2;
  asm MOV AL,1;
  L2: return(_AL);
 }

  // Cette fonction retourne 1 s'il y a d‚finit de multiple fichier
  // et 0 si ces un seul fichier qui est consern‚.

 Byte IsWild(Byte *S)
 {
  return((strchr(S,'?') > 0)||(strchr(S,'*') > 0));
 }

#endif