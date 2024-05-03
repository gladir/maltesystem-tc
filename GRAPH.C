/****************************************************************/
/*                                                              */
/*                  Malte System/Graphics Environment           */
/*                           1992/08/02                         */
/*                                                              */
/*           Copyright (C) par les Chevaliers de Malte          */
/*                                                              */
/****************************************************************/

#ifndef __Malte_Gadget_Graph_Environment__
 #define __Malte_Gadget_Graph_Environment__

 #include <MEM.H>
 #include <STDLIB.H>
 #include <STRING.H>
 #include <DISK\HANDLE.H>
 #include <KEYBOARD\BIOS_KEY.H>
 #include <MOUSE\MOUSE.H>
 #include <VIDEO\INPUT.H>
 #include <VIDEO\TEXT.H>
 #include <VIDEO\REPEAT.H>
 #include <VIDEO\BOARD.H>
 #include <GADGET\GRAPH.H>

 extern Word XMouse;
 extern Word YMouse;
 extern Word ButtonMouse;

 Byte VerCompiler             = 1;
 Byte SubVerCompiler          = 1;
 Word YearCreateCompiler      = 1992;
 Byte MonthCreateCompiler     = 7;
 Byte DayCreateCompiler       = 11;
 Byte *CIECompilerPalette     = "Les Chevaliers de Malte";

 void InitializeStubborn(struct FileStubborn *Stubborn)
 {
  memset(Stubborn,0,sizeof(Stubborn));
  (*Stubborn).VersionCompile     = VerCompiler;
  (*Stubborn).SubVersionCompile  = SubVerCompiler;
  (*Stubborn).YearCreateCompile  = YearCreateCompiler;
  (*Stubborn).MonthCreateCompile = MonthCreateCompiler;
  (*Stubborn).DayCreateCompile   = DayCreateCompiler;
  strcpy((*Stubborn).CIECompilePalette,CIECompilerPalette);
  strcpy((*Stubborn).LanguageProgrammingCompiler,"Turbo C++ Version 1.01, Copyright (C) 1990 by Borland International, Inc.");
 }

 Word SaveStubborn(struct FileStubborn *Stubborn)
 {
  if(strlen((*Stubborn).Description) < 1023) strcat((*Stubborn).Description,"\x1B");
  return(_SetFileFirstRecord_((*Stubborn).FileCodeSrc,sizeof(Stubborn),&Stubborn));
 }

 Word GetStubborn(Byte *FileName, struct FileStubborn *Stubborn)
 {
  return(_GetFileFirstRecord_(FileName,sizeof(Stubborn),&Stubborn));
 }

 void PutParametersEditor(Byte Langue, Byte X, Byte Y, Byte *Tl, Byte CB, Byte CT, Byte CM, Byte CE1, Byte CE2)
 {
  Byte *Serie[] = {
		   "C^o^mpagnie",
		   "^A^uthor",
		   "^P^assword",
		   "^C^reate Year/Month/Day",
		   "^M^odify Year/Month/Day",
		   "^W^idth char",
		   "^L^ine char",
		   "^S^ource file",
		   "^D^escription",
		   NULL
		  };
  Byte *Fra[] = {
		 "C^o^mpagnie",
		 "^A^uteur",
		 "^M^ots de passe",
		 "^C^r‚‚ AA/MM/JJ",
		 "^M^odifie AA/MM/JJ",
		 "^C^olonne par caractŠre",
		 "^L^igne par caractŠre",
		 "Fichier ^s^ource",
		 "^D^escription",
		 NULL
		};
  PutFillBorder(X,Y,X+50,Y+12,CB);
  BarTextHori(X,Y,X+50,' ',CT);
  BarTextHori(X,Y+1,X+50,' ',CM);
  WriteText(X+((50-strlen(Tl))/2),Y,Tl,CT);
  if(Langue == 1) WriteRepeatTypingXYBicolor(X+2,Y+3,Serie,CE1,CE2);
	     else WriteRepeatTypingXYBicolor(X+2,Y+3,Fra,CE1,CE2);
 }

 Word SetParametersEditor(Byte X, Byte Y, Byte *Tl, Byte CB, Byte CT, Byte CM, Byte CE1, Byte CE2, Byte CQ, Byte CC, Word kbCursorLeft, Word kbCursorRight,Word kbCursorHome,Word kbCursorEnd,Word kbDelChar,Word kbBackChar,Word kbClearLine, Word kbClearWord, Byte Mark, Byte ModeleDate, Byte SepDate, struct FileStubborn *Stubborn)
 {

   // D‚finition des variables locals //

  Word Reponse,PassWordVerify;
  Byte PosInp;
  Byte XMs;
  Byte Tmp[10];

   // Initialise les variables locals //

  PosInp         = 0;
  PassWordVerify = 0;

   // Initialise l'‚cran //

  PutParametersEditor(0,X,Y,Tl,CB,CT,CM,CE1,CE2);

   // Remplit le questionnaire //

  L20:
  Reponse = InputXYMouse__(X+26,Y+3,&PosInp,(*Stubborn).CIEPalette, 23, kbCursorLeft, kbCursorRight, kbCursorHome, kbCursorEnd, kbDelChar, kbBackChar, kbClearLine, CQ);
  BarSelectHori(X+26,Y+3,X+48,CC);
  PosInp  = 0;
  if(Reponse > 0xFFF0)
  {
   XMs = ((XMouse/8) - X);
   if((XMs >= 26)&&(XMs <= 48))
   {
    PosInp = XMs;
    switch ((YMouse / 8) - Y)
    {
     case 4  : goto L40;
     case 5  : goto L60;
     case 6  : goto L80;
     case 7  : goto L100;
     case 8  : goto L120;
     case 9  : goto L140;
     case 10 : goto L160;
     case 11 : goto L180;
     default : ;
    }
   }
  };
  switch (Reponse)
  {
   case kbUp  : goto L180;
   case kbEsc : return(kbEsc);
   default    : ;
  };
  L40:
  Reponse = InputXYMouse__(X+26,Y+4,&PosInp,(*Stubborn).AuthorPalette, 20, kbCursorLeft, kbCursorRight, kbCursorHome, kbCursorEnd, kbDelChar, kbBackChar, kbClearLine, CQ);
  BarSelectHori(X+26,Y+4,X+48,CC);
  PosInp = 0;
  if(Reponse > 0xFFF0)
  {
   XMs = ((XMouse/8) - X);
   if((XMs >= 26)&&(XMs <= 48))
   {
    PosInp = XMs;
    switch ((YMouse/8) - Y)
    {
     case 3  : goto L20;
     case 5  : goto L60;
     case 6  : goto L80;
     case 7  : goto L100;
     case 8  : goto L120;
     case 9  : goto L140;
     case 10 : goto L160;
     case 11 : goto L180;
     default : ;
    }
   }
  };
  switch (Reponse)
  {
   kbUp    : goto L20;
   kbEsc   : return(kbEsc);
   default : ;
  };
  L60:
  {
   unsigned True;
   do
    {
     Byte TmpPW[49];
     True = 0;
     strcpy(TmpPW,(*Stubborn).PassWord);
     Reponse = PasswordXYMouse(X+26,Y+5,PosInp,TmpPW,14,Mark,CQ);
     PosInp = 0;
     if(Reponse > 0xFFF0)
     {
      XMs = ((XMouse/8) - X);
      if((XMs >= 26)&&(XMs <= 48))
      {
       BarSelectHori(X+26,Y+5,X+48,CC);
       PosInp = XMs;
       switch ((YMouse/8) - Y)
       {
	case 3  : goto L20;
	case 4  : goto L40;
	case 6  : goto L80;
	case 7  : goto L100;
	case 8  : goto L120;
	case 9  : goto L140;
	case 10 : goto L160;
	case 11 : goto L180;
       }
      }
     }
     if(Reponse == kbClearLine)
     {
      True           = 1;
      PassWordVerify = 0;
      strcpy(TmpPW,"");
     }
     if(strcmp(TmpPW,(*Stubborn).PassWord) != 0)
     {
      strcpy((*Stubborn).PassWord,TmpPW);
      PassWordVerify = 0;
     }
     if((Reponse == kbCtrlLeft)||(Reponse > 0xFFF0)) True = 1;
    }
   while(True == 1);
  }
  BarSelectHori(X+26,Y+5,X+48,CC);
  switch (Reponse)
  {
   case kbUp    : goto L40;
   case kbEsc   : return(kbEsc);
   case kbEnter : if((*Stubborn).PassWord[0] != 0)&&(PassWordVerify == 0))
   {
L70:{
     unsigned True;
     do
      {
       Byte TmpPW[49];
       True = 0;
       WriteText(X+26+14+1,Y+5,"Verify",CE2);
       strcpy(TmpPW,"");
       Reponse = PasswordXYMouse(X+26,Y+5,PosInp,TmpPW,14,Mark,CQ);
       PosInp  = 0;
       if(Reponse > 0xFFF0)
       {
	XMs = ((XMouse/8) - X);
	if((XMs >= 26)&&(XMs <= 48))
	{
	 BarSpaceHori(X+26+14+1,Y+5,X+48,CC);
	 PosInp = XMs;
	 switch ((YMouse/8) - Y)
	 {
	  case 3  : goto L20;
	  case 4  : goto L40;
	  case 6  : goto L80;
	  case 7  : goto L100;
	  case 8  : goto L120;
	  case 9  : goto L140;
	  case 10 : goto L160;
	  case 11 : goto L180;
	 }
	}
       }
       if(Reponse == kbClearLine)
       {
	True           = 1;
	PassWordVerify = 0;
	strcpy(TmpPW,"");
       }
       if(strcmp(TmpPW,(*Stubborn).PassWord) != 0)
       {
	BarSpaceHori(X+26+14+1,Y+5,X+48,CC);
	strcpy((*Stubborn).PassWord,TmpPW);
	PassWordVerify = 0;
	goto L60;
       }
	else
       PassWordVerify = 1;
       if((Reponse == kbCtrlLeft)||(Reponse > 0xFFF0)) True = 1;
      }
     while(True == 1);
    }
   }
  }
  BarSpaceHori(X+26+14+1,Y+5,X+48,CC);
  BarSelectHori(X+26,Y+5,X+48,CC);
  switch (Reponse)
  {
   kbUp  : goto L40;
   kbEsc : return(kbEsc);
  }
L80:
  {
   Word Year;
   Byte Month;
   Byte Day;
   Year    = (*Stubborn).YearCreatePalette;
   Month   = (*Stubborn).MonthCreatePalette;
   Day     = (*Stubborn).DayCreatePalette;
   Reponse = InputDateExitEndXYMouse__(X+26,Y+6,ModeleDate,SepDate,CQ,CC,CE2,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearLine,kbClearWord,&Year,&Month,&Day);
   PosInp  = 0;
   if(Reponse > 0xFFF0)
   {
    XMs = ((XMouse/8) - X);
    if((XMs >= 26)&&(XMs <= 48))
    {
     PosInp = XMs;
     switch ((YMouse/8) - Y)
     {
      case 3  : goto L20;
      case 4  : goto L40;
      case 5  : goto L60;
      case 7  : goto L100;
      case 8  : goto L120;
      case 9  : goto L140;
      case 10 : goto L160;
      case 11 : goto L180;
     }
    }
   }
   (*Stubborn).YearCreatePalette  = Year;
   (*Stubborn).MonthCreatePalette = Month;
   (*Stubborn).DayCreatePalette   = Day;
  }
  switch (Reponse)
  {
   case kbUp   : goto L60;
   case kbLeft : goto L60;
   case kbEsc  : return(kbEsc);
  }
  L100:
  {
   Word Year;
   Byte Month;
   Byte Day;
   Year    = (*Stubborn).YearModifyPalette;
   Month   = (*Stubborn).MonthModifyPalette;
   Day     = (*Stubborn).DayModifyPalette;
   Reponse = InputDateExitEndXYMouse__(X+26,Y+7,ModeleDate,SepDate,CQ,CC,CE2,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearLine,kbClearWord,&Year,&Month,&Day);
   if(Reponse > 0xFFF0)
   {
    XMs = ((XMouse/8) - X);
    if((XMs >= 26)&&(XMs <= 48))
    {
     PosInp = XMs;
     switch ((YMouse/8) - Y)
     {
      case 3  : goto L20;
      case 4  : goto L40;
      case 5  : goto L60;
      case 6  : goto L80;
      case 8  : goto L120;
      case 9  : goto L140;
      case 10 : goto L160;
      case 11 : goto L180;
     }
    }
   }
   PosInp  = 0;
   (*Stubborn).YearModifyPalette  = Year;
   (*Stubborn).MonthModifyPalette = Month;
   (*Stubborn).DayModifyPalette   = Day;
  }
  switch (Reponse)
  {
   case kbUp   : goto L80;
   case kbLeft : goto L80;
   case kbEsc  : return(kbEsc);
  }
  L120:
  if((*Stubborn).WidthChar != 0) itoa((*Stubborn).WidthChar,Tmp,10);
			    else Tmp[0] = 0;
  Reponse = InputXYMouse__(X+26,Y+8,&PosInp,Tmp,5,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearLine,CQ);
  BarSelectHori(X+26,Y+8,X+48,CC);
  if(Reponse > 0xFFF0)
  {
   XMs = ((XMouse/8) - X);
   if((XMs >= 26)&&(XMs <= 48))
   {
    PosInp = XMs;
    switch ((YMouse/8) - Y)
    {
     case 3  : goto L20;
     case 4  : goto L40;
     case 5  : goto L60;
     case 6  : goto L80;
     case 7  : goto L100;
     case 9  : goto L140;
     case 10 : goto L160;
     case 11 : goto L180;
    }
   }
  }
  PosInp = 0;
  (*Stubborn).WidthChar = atoi(Tmp);
  switch (Reponse)
  {
   kbUp  : goto L100;
   kbEsc : return(kbEsc);
  }
L140:
  if((*Stubborn).LineChar != 0) itoa((*Stubborn).LineChar,Tmp,10);
			   else Tmp[0] = 0;
  Reponse = InputXYMouse__(X+26,Y+9,&PosInp,Tmp,5,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearLine,CQ);
  BarSelectHori(X+26,Y+9,X+48,CC);
  PosInp  = 0;
  if(Reponse > 0xFFF0)
  {
   XMs = ((XMouse/8) - X)
   if((XMs >= 26)&&(XMs <= 48))
   {
    PosInp = XMs;
    switch ((YMouse/8)-Y)
    case 3  : goto L20;
    case 4  : goto L40;
    case 5  : goto L60;
    case 6  : goto L80;
    case 7  : goto L100;
    case 8  : goto L120;
    case 10 : goto L160;
    case 11 : goto L180;
   }
  }
  (*Stubborn).LineChar = atoi(Tmp);
  switch (Reponse)
  {
   kbUp  : goto L120;
   kbEsc : return(kbEsc);
  }
  L160:
  Reponse = InputXYMouse__(X+26,Y+10,&PosInp,(*Stubborn).FileCodeSrc,12,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearLine,CQ);
  BarSelectHori(X+26,Y+10,X+48,CC);
  PosInp  = 0;
  if(Reponse > 0xFFF0)
  {
   XMs = ((XMouse/8) - X);
   if((XMs >= 26)&&(XMs <= 48))
   {
    PosInp = XMs;
    switch ((YMouse/8) - Y)
    {
     case 3  : goto L20;
     case 4  : goto L40;
     case 5  : goto L60;
     case 6  : goto L80;
     case 7  : goto L100;
     case 8  : goto L120;
     case 9  : goto L140;
     case 11 : goto L180;
    }
   }
  }
  switch (Reponse)
  {
   kbUp  : goto L140;
   kbEsc : return(kbEsc);
  }
  L180:
  Reponse = InputXYMouse__(X+26,Y+11,&PosInp,(*Stubborn).Description,23,kbCursorLeft,kbCursorRight,kbCursorHome,kbCursorEnd,kbDelChar,kbBackChar,kbClearLine,CQ);
  BarSelectHori(X+26,Y+11,X+48,CC);
  PosInp  = 0;
  if(Reponse > 0xFFF0)
  {
   XMs = (XMouse / 8) - X;
   if((XMs >= 26)&&(XMs <= 48))
   {
    PosInp = XMs;
    switch ((YMouse/8) - Y)
    {
     case  3 : goto L20;
     case  4 : goto L40;
     case  5 : goto L60;
     case  6 : goto L80;
     case  7 : goto L100;
     case  8 : goto L120;
     case  9 : goto L140;
     case 10 : goto L160;
    }
   }
  }
  switch (Reponse)
  {
   kbUp          : goto L160;
   kbDown, kbTab : goto L20;
   kbEsc         : return(kbEsc);
  }
  if(((*Stubborn).PassWord[0] != 0)&&(PassWordVerify == 0)) goto L70;
  if((*Stubborn).AuthorPalette[0] == 0) goto L40;
  if((*Stubborn).FileCodeSrc[0] == 0)   goto L160;
  return(Reponse);
 }

#endif