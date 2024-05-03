/**********************************************************************/
/*                                                                    */
/*                        Malte System/File Handle                    */
/*                               1992/07/20                           */
/*                                                                    */
/*              Copyright (C) par les Chevaliers de Malte             */
/*                                                                    */
/**********************************************************************/

#include <DOS.H>
#include <DISK\HANDLE.H>

Word FileError;

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

void RealToBiWord(LongWord Nombre, Word *Grand, Word *Petit)
{
 *Grand = Nombre / 0x10000;
 *Petit = Nombre & 0xFFFF;
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

LongWord BiWordToReal(Word Grand, Word Petit)
{
 return((Grand * 0x10000) + Petit);
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word SetFilePos(Word Handle, LongWord Pos, Word Size)
{
 Word Grand,Petit;
 Word Sortie;
 Word Drapeau;
 RealToBiWord(Pos * Size,&Grand,&Petit);
 _AX = 0x4200;
 _BX = Handle;
 _CX = Grand;
 _DX = Petit;
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(0);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word SetFilePos_(Word Handle, LongWord Pos)
{
 Word Grand,Petit;
 Word Sortie;
 Word Drapeau;
 RealToBiWord(Pos,&Grand,&Petit);
 _AX = 0x4200;
 _BX = Handle;
 _CX = Grand;
 _DX = Petit;
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(0);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word SetFilePosHome(Word Handle)
{
 Word Sortie;
 Word Drapeau;
 _AX = 0x4200;
 _BX = Handle;
 _CX = 0x0000;
 _DX = 0x0000;
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(0);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

LongWord FileSize(Word Handle)
{
 Word Sortie;
 Word Drapeau;
 Word Data;
 _AX = 0x4202;
 _BX = Handle;
 _CX = 0x0000;
 _DX = 0x0000;
 asm INT 0x21;
 Sortie  = _AX;
 Data    = _DX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFFFFFF);
 }
  else
 {
  FileError = 0;
  return(BiWordToReal(Data,Sortie));
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

LongWord NumRecordInFile(Word Handle, Word Size)
{
 return(FileSize(Handle) / Size);
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word Close(Word Handle)
{
 _AX = 0x3E00;
 _BX = Handle;
 asm INT 0x21;
 asm JNC Ok;
 FileError = _AX;
 return(0xFFFF);
 Ok:
 FileError = 0x0000;
 return(0);
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word Open(Byte *Nom, Byte Mode)
{
 Word Sortie;
 Word Drapeau;
 _DS = FP_SEG(Nom);
 _DX = FP_OFF(Nom);
 _AX = 0x3D40 + Mode;
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(Sortie);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word _Open(Byte *Nom)
{
 Word Sortie;
 Word Drapeau;
 _AX = 0x3D42;
 _DS = FP_SEG(Nom);
 _DX = FP_OFF(Nom);
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(Sortie);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word _OpenPrinter(void)
{
 return(_Open("PRN"));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word _OpenNull(void)
{
 return(_Open("NUL"));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word _OpenLCDPanel(void)
{
 return(_Open("LCDDEV"));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word _OpenKeyboard(void)
{
 return(_Open("KYBD:"));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word _OpenConsole(void)
{
 return(_Open("CON"));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word _OpenAux(void)
{
 return(_Open("AUX"));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word OpenPrinter(Byte Mode)
{
 return(Open("PRN",Mode));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word OpenNull(Byte Mode)
{
 return(Open("NUL",Mode));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word OpenLCDPanel(Byte Mode)
{
 return(Open("LCDDEV",Mode));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word OpenKeyboard(Byte Mode)
{
 return(Open("KYBD:",Mode));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word OpenConsole(Byte Mode)
{
 return(Open("CON",Mode));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word OpenAux(Byte Mode)
{
 return(Open("AUX",Mode));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word New(Byte *Nom, Word Attribut)
{
 Word Sortie;
 Word Drapeau;
 _AH = 0x3C;
 _DS = FP_SEG(Nom);
 _DX = FP_OFF(Nom);
 _CX = Attribut;
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(Sortie);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word _New(Byte *Nom)
{
 Word Sortie;
 Word Drapeau;
 _AH = 0x3C;
 _DS = FP_SEG(Nom);
 _DX = FP_OFF(Nom);
 _CX = 0x0000;
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(Sortie);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word FileDelete(Byte *Nom)
{
 Word Sortie;
 Word Drapeau;
 _AX = 0x4100;
 _DS = FP_SEG(Nom);
 _DX = FP_OFF(Nom);
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(Sortie);
 }
  else
 {
  FileError = 0;
  return(0);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word DoubleHandle(Word Handle)
{
 Word Sortie;
 Word Drapeau;
 _AH = 0x45;
 _BX = Handle;
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(Sortie);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word FileRename(Byte *Source, Byte *Target)
{
 Word Sortie;
 Word Drapeau;
 _ES = FP_SEG(Target);
 _DS = FP_SEG(Source);
 _DI = FP_OFF(Target);
 _DX = FP_OFF(Source);
 _AH = 0x56;
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(0);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word GetRecord_(Word Handle, LongWord Pos, Word Size, const *Buffer)
{
 Word Sortie;
 Word Drapeau;
 SetFilePos(Handle,Pos,Size);
 _AX = 0x3F00;
 _BX = Handle;
 _CX = Size;
 _DS = FP_SEG(Buffer);
 _DX = FP_OFF(Buffer);
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(0);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word GetRecordHome_(Word Handle, Word Size, const *Buffer)
{
 Word Sortie;
 Word Drapeau;
 SetFilePos(Handle,0,Size);
 _AX = 0x3F00;
 _BX = Handle;
 _CX = Size;
 _DS = FP_SEG(Buffer);
 _DX = FP_OFF(Buffer);
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(0);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word GetRecord(Word Handle, Word Size, const *Buffer)
{
 Word Sortie;
 Word Drapeau;
 _AX = 0x3F00;
 _BX = Handle;
 _CX = Size;
 _DS = FP_SEG(Buffer);
 _DX = FP_OFF(Buffer);
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(0);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word SetRecord_(Word Handle, LongWord Pos, Word Size, const *Buffer)
{
 Word Sortie;
 Word Drapeau;
 SetFilePos(Handle,Pos,Size);
 _AX = 0x4000;
 _BX = Handle;
 _CX = Size;
 _DS = FP_SEG(Buffer);
 _DX = FP_OFF(Buffer);
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(0);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word SetRecordHome_(Word Handle, Word Size, const *Buffer)
{
 Word Sortie;
 Word Drapeau;
 SetFilePos(Handle,0,Size);
 _AX = 0x4000;
 _BX = Handle;
 _CX = Size;
 _DS = FP_SEG(Buffer);
 _DX = FP_OFF(Buffer);
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(0);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word SetRecord(Word Handle, Word Size, const *Buffer)
{
 Word Sortie;
 Word Drapeau;
 _AX = 0x4000;
 _BX = Handle;
 _CX = Size;
 _DS = FP_SEG(Buffer);
 _DX = FP_OFF(Buffer);
 asm INT 0x21;
 Sortie  = _AX;
 Drapeau = _FLAGS;
 if((Drapeau & 0x01) != 0)
 {
  FileError = Sortie;
  return(0xFFFF);
 }
  else
 {
  FileError = 0;
  return(0);
 }
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word AdditionRecord(Word Handle, Word Size, const *Buffer)
{
 return(SetRecord_(Handle,FileSize(Handle) / Size,Size,Buffer));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word _SetFileRecord_(Byte *FileName, Word Pos, Word Size, const *Buffer)
{
 Word Handle;
 Handle = _Open(FileName);
 if(Handle == 0xFFFF)
 {
  Handle = _New(FileName);
  if(Handle == 0xFFFF) return(0xFFFF);
 }
 if(SetRecord_(Handle,Pos,Size,Buffer) == 0xFFFF)
 {
  Word Error;
  Error = FileError;
  Close(Handle);
  return(Error);
 }
  else
 return(Close(Handle));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

Word _SetFileFirstRecord_(Byte *FileName, Word Size, const *Buffer)
{
 Word Handle;
 Handle = _Open(FileName);
 if(Handle == 0xFFFF)
 {
  Handle = _New(FileName);
  if(Handle == 0xFFFF) return(0xFFFF);
 }
 if(SetRecordHome_(Handle,Size,Buffer) == 0xFFFF)
 {
  Word Error;
  Error = FileError;
  Close(Handle);
  return(Error);
 }
  else
 return(Close(Handle));
}

 // 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 //

void main(void)
{
 FileError = 0;
}