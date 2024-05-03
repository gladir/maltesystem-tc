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

void HlpCmdChDir(Byte Langue)
{
 if(Langue == 1)
 {
  WriteTextLn_W("Display or change the current directory.");
  WriteTextLn_W("");
  WriteTextLn_W("CD [drive:][path]");
  WriteTextLn_W("CD [..]");
  WriteTextLn_W("CHDIR [drive:][path]");
  WriteTextLn_W("CHDIR [..]");
  WriteTextLn_W("");
  WriteTextLn_W(".. (two dots) changes to the parent directory.");
  WriteTextLn_W("");
  WriteTextLn_W("CD by itself or with just drive: displays the current directory.");
  WriteTextLn_W("");
  WriteTextLn_W("CD and CHDIR are the same command.");
 }
  else
 {
  WriteTextLn_W("Change le r‚pertoire en cours ou affiche son nom.");
  WriteTextLn_W("");
  WriteTextLn_W("CHDIR [unit‚:][chemin]");
  WriteTextLn_W("CHDIR [..]");
  WriteTextLn_W("CD [unit‚:][chemin]");
  WriteTextLn_W("CD [..]");
  WriteTextLn_W("");
  WriteTextLn_W(".. indique que vous voulez remonter au r‚pertoire parent.");
  WriteTextLn_W("");
  WriteTextLn_W("CD unit‚: affiche le r‚pertoire en cours sur l'unit‚ sp‚cifi‚.");
  WriteTextLn_W("CD sans paramŠtre affiche l'unit‚ et le r‚pertoire en cours.");
  WriteTextLn_W("");
  WriteTextLn_W("CD et CHDIR sont les mˆmes commandes.");
 }
}

void HlpCmdPath(Byte Langue)
{
 if(Langue == 1)
 {
  WriteTextLn_W("Set or display the directory to search for executable files.");
  WriteTextLn_W("");
  WriteTextLn_W("PATH [drive:]path1[;[[drive:]path2]...]");
  WriteTextLn_W("PATH [;]");
  WriteTextLn_W("");
  WriteTextLn_W("When searching for an external command, your system");
  WriteTextLn_W("searches the current directory first, then the directory");
  WriteTextLn_W("specified in the path in the order listed.");
  WriteTextLn_W("");
  WriteTextLn_W("PATH with no parameters displays the current search path.");
  WriteTextLn_W("PATH with just a semicolon clears the search path.");
 }
  else
 {
  WriteTextLn_W("Affiche ou d‚finit le chemin de recherche des fichiers ex‚cutables.");
  WriteTextLn_W("");
  WriteTextLn_W("PATH [[unit‚:]chemin[;...]]");
  WriteTextLn_W("PATH ;");
  WriteTextLn_W("");
  WriteTextLn_W("Taper PATH ; pour effacer le chemin de recherche et indiquer");
  WriteTextLn_W("au systŠme de ne chercher que dans le r‚pertoire en cours.");
  WriteTextLn_W("PATH sans paramŠtre affiche le chremin de recherche en cours.");
 }
}

void HlpCmdSet(Byte Langue)
{
 if(Langue == 1)
 {
  WriteTextLn_W("Display, create, modify or delete environnement variables.");
  WriteTextLn_W("");
  WriteTextLn_W("SET [variable[=[chaŒne]]]");
  WriteTextLn_W("");
  WriteTextLn_W(" variable  Environment variable name.");
  WriteTextLn_W(" value     String.");
  WriteTextLn_W("");
  WriteTextLn_W("SET with no parameters displays the current environment.");
  WriteTextLn_W("SET variable= with clears the variable from the environment.");
 }
  else
 {
  WriteTextLn_W("Affiche, d‚finit ou supprime une variable d'environnement.");
  WriteTextLn_W("");
  WriteTextLn_W("SET [variable[=[chaŒne]]]");
  WriteTextLn_W("");
  WriteTextLn_W(" variable   nom de la variable d'environnement.");
  WriteTextLn_W(" chaŒne     chaŒne de caractŠres … affecter … la variable.");
  WriteTextLn_W("");
  WriteTextLn_W("SET sans paramŠtre affiche les variables d'environnement d‚finies.");
  WriteTextLn_W("SET variable= efface la variable de l'environnement.");
 }
}

void HlpCmdVer(Byte Langue)
{
 if(Langue == 1)
 {
  WriteTextLn_W("Display the current DOS version.");
  WriteTextLn_W("");
  WriteTextLn_W("VERSION");
  WriteTextLn_W("VER");
  WriteTextLn_W("");
  WriteTextLn_W("VER and VERSION are the same command.");
 }
  else
 {
  WriteTextLn_W("Affiche le num‚ro de version du DOS.");
  WriteTextLn_W("");
  WriteTextLn_W("VERSION");
  WriteTextLn_W("VER");
  WriteTextLn_W("");
  WriteTextLn_W("VER et VERSION sont les mˆmes commandes.");
 }
}

void HelpCommand(Byte Niveau)
{
 if(Niveau == Level_OldSystem)
 {
  WriteTextLn_W("?              CD             CHDIR          CLS");
  WriteTextLn_W("COPY           DATE           DEL            DIR");
  WriteTextLn_W("ECHO           ERASE          EXIT           HELP");
  WriteTextLn_W("MD             MKDIR          PATH           PROMPT");
  WriteTextLn_W("RD             REM            REN            RENAME");
  WriteTextLn_W("RMDIR          SET            TIME           VER");
 }
  else
 if((Niveau == Level_Beginner_NotKey)||
    (Niveau == Level_Beginner)||
    (Niveau == Level_Beginner_Windows))
 {
  WriteTextLn_W("?              CHDIR          CLS            COPY");
  WriteTextLn_W("DATE           DELETE         DIR            ERASE");
  WriteTextLn_W("EXIT           HELP           MKDIR          MOVE");
  WriteTextLn_W("REM            RENAME         RMDIR          TIME");
 }
  else
 if((Niveau == Level_Intermediate_NotKey)||
    (Niveau == Level_Intermediate)||
    (Niveau == Level_Intermediate_Windows))
 {
  WriteTextLn_W("?              CD             CDD            CHDIR");
  WriteTextLn_W("CLS            COPY           CPY            DATE");
  WriteTextLn_W("DEL            DELETE         DIR            ERASE");
  WriteTextLn_W("EXIT           FREE           HELP           HLP");
  WriteTextLn_W("MD             MKDIR          MOV            MOVE");
  WriteTextLn_W("PATH           RD             REM            REN");
  WriteTextLn_W("RENAME         RENDIR         RMDIR          SET");
  WriteTextLn_W("TIME           VER            VERSION");
 }
  else
 if((Niveau == Level_Advanced_NotKey)||
    (Niveau == Level_Advanced)||
    (Niveau == Level_Advanced_Windows))
 {
  WriteTextLn_W("?              BEEP           CD             CDD");
  WriteTextLn_W("CHDIR          CLS            COPY           CPY");
  WriteTextLn_W("DATE           DEL            DELETE         DIR");
  WriteTextLn_W("ECHO           EPATH          ERASE          ESET");
  WriteTextLn_W("EXIT           FIND           FREE           FRE");
  WriteTextLn_W("HELP           HLP            LOG            MD");
  WriteTextLn_W("MKDIR          MOV            MOVE           PATH");
  WriteTextLn_W("PROMPT         RD             REM            REN");
  WriteTextLn_W("RENAME         RENDIR         RMDIR          SET");
  WriteTextLn_W("TIME           VER            VERSION        WHERE");
 }
}

Word ExecuteCommand(Byte Langue, Byte Niveau, Byte *Cmd, Byte *Param)
{
  // Definit les niveaux //
 Byte Level;
 Level = 3;
 if(Niveau == Level_OldSystem) Level = 0;
 if((Niveau == Level_Beginner)||
    (Niveau == Level_Beginner_NotKey)||
    (Niveau == Level_Beginner_Windows)) Level = 1;
 if((Niveau == Level_Intermediate)||
    (Niveau == Level_Intermediate_NotKey)||
    (Niveau == Level_Intermediate_Windows)) Level = 2;
  // Test le type de commande //
 if((strcmp(Cmd,"?"))||(strcmp(Cmd,"/?"))||(strcmp(Cmd,"-?")))
 {
  HelpCommand(Niveau);
  return(0);
 }
 if(strcmp(Cmd,"HELP"))
 {
  if(((strcmp(Cmd,"CD"))&&(Level != 1))||(strcmp(Cmd,"CHDIR")))
  {
   HlpCmdChDir(Langue);
   return(0);
  }
  if((strcmp(Cmd,"PATH"))&&(Level != 1))
  {
   HlpCmdPath(Langue);
   return(0);
  }
  if((strcmp(Cmd,"SET"))&&(Level != 1))
  {
   HlpCmdSet(Langue);
   return(0);
  }
  if(((strcmp(Cmd,"VER"))&&(Level != 1))||
     ((strcmp(Cmd,"VERSION"))&&(Level != 0)&&(Level != 1)))
  {
   HlpCmdVer(Langue);
   return(0);
  }
  if(Langue == 1) PutErrorNumLn_W(Langue,0xFFFC,"Not help information for this command.");
	     else PutErrorNumLn_W(Langue,0xFFFC,"Aide non-disponible pour cette commande.");
  return(0xFFFC);
 }
 if(((strcmp(Cmd,"CD"))&&(Level != 1))||(strcmp(Cmd,"CHDIR")))
 {
  if(Param[0] == 0) // Put Path ?
  {
   Word Error;
   Byte Path[80];
   Path[0] = 0;
   Error = GetCurrentDirectory(Path);
   if(Error == 0)
   {
    WriteTextLn_W(Path);
    return(0);
   }
    else
   {
    PutErrorMsgLn_W(Langue,Error);
    return(Error);
   }
  }
   else
  if((strcmp(Param,"/?"))||(strcmp(Param,"?")))
  {
   HlpCmdChDir(Langue);
   return(0);
  }
   else
  if((Param[1] == ':')&&(Param[2] == 0)) // Get Path in disk ?
  {
   if(isalpha(Param[0])) // Logic letter drive ?
   {
    Word Error;
    Byte Path[80];
    Path[0] = 0;
    Error = GetDirectory(Param[0],Path);
    if(Error == 0)
    {
     WriteTextLn_W(Path);
     return(0);
    }
     else
    {
     PutErrorMsgLn_W(Langue,Error);
     return(Error);
    }
   }
    else
   {
    if(Langue == 1) PutErrorNumLn_W(Langue,0xFFFF,"Invalid symbol drive");
	       else PutErrorNumLn_W(Langue,0xFFFF,"Symbole de disque inconnu");
    return(0xFFFF);
   }
  }
  if(Cmd[1] == ':') // Change disk ?
  {
   if(isalpha(Param[0])) // Logic letter drive ?
   {
    if(Langue == 1) PutErrorNumLn_W(Langue,0xFFFE,"Drive is not valid for command ChDir");
	       else PutErrorNumLn_W(Langue,0xFFFE,"La sp‚cification du disque est interdit pour la command ChDir");
    return(0xFFFE);
   }
    else
   {
    if(Langue == 1) PutErrorNumLn_W(Langue,0xFFFF,"Invalid symbol drive");
	       else PutErrorNumLn_W(Langue,0xFFFF,"Symbole de disque inconnu");
    return(0xFFFF);
   }
  }
   else // C'est logiquement pour changer de r‚pertoire...
  {
   Word Error;
   Error = ChangeDirectory(Param);
   if(Error != 0)
   {
    PutErrorMsgLn_W(Langue,Error);
    return(Error);
   }
    else
   return(0);
  }
 }
 return(0xFFFD);
}