 // D‚finition des fonctions ext‚rieur … inclure

#include <CTYPE.H>
#include <DOS.H>
#include <PROCESS.H>
#include <NUMERIC.H>
#include <TRANSLTR.H>
#include <DISK\HANDLE.H>
#include <KEYBOARD\BIOS_KEY.H>
#include <VIDEO\TEXT\BIOS.H>
#include <VIDEO\TEXT\DIRECT.H>
#include <VIDEO\TEXT\TEXT.H>

 // D‚finition des variables ext‚rieur

extern Byte DataHex[16];
extern Byte VID;

 // D‚finition des variables g‚n‚ral

Byte VwrEdtMerge = 3;

void PutViewEditBinary(Byte XHex, Byte XAsc, Byte Y, Byte *Buffer)
{
  // D‚finition des variables locals
 Byte I, J;
  // D‚finition de la sous-routine
 if(VID == 0)
 {
  for(J = 0; J <= 15; J++)
  {
   Byte TY = J + Y, TBJ = J * 16;
   for(I = 0; I <= 15; I++)
   {
    Byte TBuf = Buffer[I + TBJ],
	 THex = I * VwrEdtMerge + XHex;
    MEM_SetChar(THex,   TY, DataHex[TBuf >> 4]);
    MEM_SetChar(THex+1, TY, DataHex[TBuf & 0x0F]);
    MEM_SetChar(XAsc+I, TY, TBuf);
   }
  }
 }
  else
 {
  for(J = 0; J <= 15; J++)
  {
   Byte TY = J + Y, TBJ = J * 16;
   for(I = 0; I <= 15; I++)
   {
    Byte TBuf = Buffer[I + TBJ],
	 THex = I * VwrEdtMerge + XHex;
    BIOS_SetChar(THex,   TY, DataHex[TBuf >> 4]);
    BIOS_SetChar(THex+1, TY, DataHex[TBuf & 0x0F]);
    BIOS_SetChar(XAsc+I, TY, TBuf);
   }
  }
 }
}

Word ViewEditFile(Byte XV1, Byte XV2, Byte YV, Byte *FileName, Word kbSwitch)
{
 Byte     Buffer[256], Ok, FlgEdt, FlgTab, FlgChg, XP, YP, Bi;
 Word     Handle = Open(FileName,0), K;
 LongWord Pos, S;
 CloseCursor();
 if(Handle == 0xFFFF) return(0xF000);
 S = NumRecordInFile(Handle,256);
 for(Ok=0,Pos=0,FlgEdt=0,FlgTab=0,FlgChg=0,XP=0,YP=0,Bi=0; Ok == 0;)
 {
  if(FlgEdt == 0)
  {
   Word I;
   if(S == Pos) for(I = 0; I < 256; I++) Buffer[I] = 0;
   GetRecord_(Handle,Pos,256,Buffer);
   PutViewEditBinary(XV1,XV2,YV,Buffer);
  }
  K = BIOS_ReadKey(); Ok = 1;
  if(K == kbPgDn) if(FlgEdt == 0) { Ok = 0; if(S > Pos) Pos++; }
  if(K == kbPgUp) if(FlgEdt == 0) { Ok = 0; if(Pos > 0) Pos--; }
  if(K == kbEnd)
  {
   if(FlgEdt == 0) { Ok = 0; Pos = S; }
    else
   {
    Ok = 0; XP = 15; YP = 15;
    if(FlgTab == 0) SetPosCursor(XV1+XP*3+Bi, YV+YP);
	       else SetPosCursor(XV2+XP,      YV+YP);
   }
  }
  if(K == kbHome)
  {
   if(FlgEdt == 0)
   {
    Ok = 0; Pos = 0;
   }
    else
   {
    Ok = 0; XP = 0; YP = 0;
    if(FlgTab == 0) SetPosCursor(XV1+XP*3+Bi, YV+YP);
	       else SetPosCursor(XV2+XP,      YV+YP);
   }
  }
  if((K == kbSwitch)&&(FlgChg == 0))
  {
   Ok = 0;
   if(FlgEdt == 1)
   {
    CloseCursor();
    FlgEdt = 0;
   }
    else
   {
    Close(Handle);
    Handle = Open(FileName,2);
    if(Handle != 0xFFFF)
    {
     FlgEdt = 1;
     SetCursor(7,8);
     if(FlgTab == 0) SetPosCursor(XV1+XP*3+Bi, YV+YP);
		else SetPosCursor(XV2+XP,      YV+YP);
    }
     else
    {
     Handle = Open(FileName,0);
     if(Handle == 0xFFFF) return(0xF000);
    }
   }
  }
  if(K == kbTab)   if(FlgEdt == 1)
		   {
		    Ok = 0; FlgTab = (FlgTab + 1) & 0x01;
		    if(FlgTab == 0) SetPosCursor(XV1+XP*3+Bi, YV+YP);
			       else SetPosCursor(XV2+XP,      YV+YP);
		   }
  if(K == kbUp)    if(FlgEdt == 1)
		   {
		    Ok = 0; YP = (YP - 1) & 0x0F;
		    if(FlgTab == 0) SetPosCursor(XV1+XP*3+Bi, YV+YP);
			       else SetPosCursor(XV2+XP,      YV+YP);
		   }
  if(K == kbDown)  if(FlgEdt == 1)
		   {
		    Ok = 0; YP = (YP + 1) & 0x0F;
		    if(FlgTab == 0) SetPosCursor(XV1+XP*3+Bi, YV+YP);
			       else SetPosCursor(XV2+XP,      YV+YP);
		   }
  if(K == kbLeft)  if(FlgEdt == 1)
		   {
		    Ok = 0;
		    if(FlgTab == 0)
		    {
		     Bi = (Bi + 1) & 0x01;
		     if(Bi == 1) XP = (XP - 1) & 0x0F;
		    }
		     else
		    XP = (XP + 1) & 0x0F;
		    if(FlgTab == 0) SetPosCursor(XV1+XP*3+Bi, YV+YP);
			       else SetPosCursor(XV2+XP,      YV+YP);
		   }
  if(K == kbRight) if(FlgEdt == 1)
		   {
		    Ok = 0;
		    if(FlgTab == 0)
		    {
		     Bi = (Bi + 1) & 0x01;
		     if(Bi == 0) XP = (XP + 1) & 0x0F;
		    }
		     else
		    XP = (XP + 1) & 0x0F;
		    if(FlgTab == 0) SetPosCursor(XV1+XP*3+Bi, YV+YP);
			       else SetPosCursor(XV2+XP,      YV+YP);
		   }
 }
 if((Ok == 1)&&(FlgEdt == 1)&&(Lo(K) != 0))
 {
  if(FlgTab == 0)
  {
   if(isxdigit(Lo(K)))
   {
    Byte Char = toupper(Lo(K)), Chr = Char - '0', Alpha = Char - 'A';
    Ok = 0;
    if(Char <= '9')
    {
     if(Bi == 0) Buffer[XP+YP*16] = (Buffer[XP+YP*16] & 0xF) + (Chr << 4);
	    else Buffer[XP+YP*16] = (Buffer[XP+YP*16] & 0xF0) + Chr;
    }
     else
    {
     if(Bi == 0) Buffer[XP+YP*16] = (Buffer[XP+YP*16] & 0xF) + (Alpha << 4);
	    else Buffer[XP+YP*16] = (Buffer[XP+YP*16] & 0xF0) + Alpha;
    }
    SetChar(XV1+XP*3,YV+YP,DataHex[Buffer[XP+YP*16] >> 4]);
    SetChar(XV1+XP*3+1,YV+YP,DataHex[Buffer[XP+YP*16] & 0x0F]);
    Bi = (Bi + 1) & 0x01;
    if(Bi == 0) XP = (XP + 1) & 0x0F;
    SetPosCursor(XV1+XP*3+Bi,YV+YP);
    FlgChg = 1;
   }
  }
   else
  {
   Ok = 0;
   Buffer[XP+YP*16] = Lo(K);
   SetChar(XV2+XP,YV+YP,Lo(K));
   XP = (XP + 1) & 0x0F;
   SetPosCursor(XV2+XP,YV+YP);
   FlgChg = 1;
  }
 }
 Close(Handle);
 return(K);
}

void main(void)
{
 ViewEditFile(5,55,3,"TCDEF.DSK",kbF6);
}