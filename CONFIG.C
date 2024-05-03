/********************************************************************/
/*                                                                  */
/*                       Malte System/Configuration                 */
/*                             1992/06/10                           */
/*                                                                  */
/*              Copyright (C) par les Chevaliers de Malte           */
/*                                                                  */
/********************************************************************/

#ifndef __Malte_Configuration__
#define __Malte_Configuartion__

#include <io.h>
#include <stdio.h>
#include <dos.h>
#include <dir.h>
#include <string.h>
#include <c:\langage\libc\data\numeric.c>

			   /* Constante */

#define ExtAfrikaans    "AFR"
#define ExtAlbanais     "ALB"
#define ExtArabe        "ARB"
#define ExtBGI          "BGI"
#define ExtCalc         "CAL"
#define ExtConfig       "CFG"
#define ExtChinois      "CHI"
#define ExtEgyptien     "EGY"
#define ExtAnglais      "ENG"
#define ExtEspagnol     "ESP"
#define ExtEtiopien     "ETI"
#define ExtFrancais     "FRA"
#define ExtAllemand     "GER"
#define ExtGrec         "GRE"
#define ExtHebreu       "HEB"
#define ExtAide         "HLP"
#define ExtIndonesien   "IND"
#define ExtIslandais    "ISL"
#define ExtItalien      "ITA"
#define ExtJaponais     "JAP"
#define ExtKeyboard     "KND"
#define ExtLatin        "LAT"
#define ExtMacro        "MAC"
#define ExtModem        "MDM"
#define ExtMontagnais   "MON"
#define ExtPersan       "PER"
#define ExtPortugais    "POR"
#define ExtPrinter      "PRN"
#define ExtRusse        "RUS"

				  /* Type */

typedef char PathStr[79];
typedef enum LanguageType
	     {
	      Afrikaans = 1,
	      Albanais,
	      Allemand,
	      Anglais,
	      Arabe,
	      Chinois,
	      Egyptien,
	      Espagnol,
	      Etiopien,
	      Francais,
	      Grec,
	      Hebreu,
	      Indonesien,
	      Islandais,
	      Italien,
	      Japonais,
	      Latin,
	      Montagnais,
	      Persan,
	      Portugais,
	      Russe
	     };

typedef struct
	      {
	       char Brd; // Border          //
	       char IA;  // Inactif         //
	       char Nor; // Normal          //
	       char SI;  // Selecte Inactif //
	       char SA;  // Selecte Actif   //
	      }
	MenuStageType;

typedef struct
	      {
	       char Nor; // Normal          //
	       char IA;  // Inactif         //
	       char SI;  // Selecte Inactif //
	       char SA;  // Selecte Actif   //
	      }
	MenuBarType;

typedef struct
	      {
	       MenuBarType   MB; // Menu Bar  //
	       MenuStageType MM; // Main Menu //
	       MenuStageType UM; // Up Menu   //
	       MenuStageType DM; // Down Menu //
	      }
	MenuColorType;

typedef struct
	      {
	       char Brd; // Border          //
	       char Nor; // Normal          //
	       char BA;  // Button actif    //
	       char BIA; // Button Inactif  //
	       char SF;  // Sous-Fond       //
	       char CSF; // Cadre sous-fond //
	       char Inf; // Information     //
	      }
	DialogsColorType;

typedef struct
	      {
	       char Brd; // Border //
	       char Fnd; // Fond   //
	      }
	FondColorType;

typedef struct
	      {
	       FondColorType    Bse; // Base    //
	       MenuColorType    Mnu; // Menu    //
	       DialogsColorType Dgs; // Dialogs //
	      }
	ColorType;

typedef struct
	      {
	       PathStr BGI;
	       PathStr Help;
	       PathStr Library;
	       PathStr Modem;
	       PathStr NetWork;
	       PathStr Printer;
	       PathStr Utility;
	       PathStr Video;
	      }
	DirType;

typedef struct
	       {
		enum LanguageType Language;
	       }
	SystemType;

typedef struct
	       {
		char         NomCarte[1][36];
		char         Date[1][10];
		char         Version[1][12];
		int          Carte[1];
		int          Video[1];
		long         Memory[1];
		enum Binaire ROM_BIOS[1];
	       }
	VideoType;

struct ConfigType
	       {
		ColorType  Color;
		DirType    Dir;
		SystemType System;
		VideoType  Video;
	       }

/********************************************************************/
/*                                                                  */
/*                Initialisation de la configuration                */
/*                           1992/06/11                             */
/*                                                                  */
/* Description : þ Cette proc‚dure permet d'obtenir la configur-    */
/*                 ation original du systŠme (par d‚faut).          */
/*                                                                  */
/********************************************************************/

InitConfig(struct ConfigType *Config)
{
  /* D‚finit le variable local */
 PathStr    Path;
 char       Drive[1];
 int        Disk;
  /* Ajustement des r‚pertoires */
 Disk  = getdisk();
 if(Disk != 0)
 {
  Disk  = Disk + 65;
  Drive[0] = Disk;
  Drive[1] = 0;
  strcpy((*Config).Dir.BGI,Drive);
  strcpy(Path,":\\MALTE\\BGI\\");
  strcat((*Config).Dir.BGI,Path);
  strcpy((*Config).Dir.Help,Drive);
  strcpy(Path,":\\MALTE\\HELP\\");
  strcat((*Config).Dir.Help,Path);
  strcpy((*Config).Dir.Library,Drive);
  strcpy(Path,":\\MALTE\\LIBRARY\\");
  strcat((*Config).Dir.Library,Path);
  strcpy((*Config).Dir.Modem,Drive);
  strcpy(Path,":\\MALTE\\MODEM\\");
  strcat((*Config).Dir.Modem,Path);
  strcpy((*Config).Dir.NetWork,Drive);
  strcpy(Path,":\\MALTE\\NETWORK\\");
  strcat((*Config).Dir.NetWork,Path);
  strcpy((*Config).Dir.Utility,Drive);
  strcpy(Path,":\\MALTE\\");
  strcat((*Config).Dir.Utility,Path);
  strcpy((*Config).Dir.Video,Drive);
  strcpy(Path,":\\MALTE\\VIDEO\\");
  strcat((*Config).Dir.Video,Path);
 }
  else
 {
  strcpy((*Config).Dir.BGI,"A:\\BGI\\");
  strcpy((*Config).Dir.Help,"A:\\HELP\\");
  strcpy((*Config).Dir.Library,"A:\\LIBRARY\\");
  strcpy((*Config).Dir.Modem,"A:\\MODEM\\");
  strcpy((*Config).Dir.NetWork,"A:\\NETWORK\\");
  strcpy((*Config).Dir.Printer,"A:\\PRINTER\\");
  strcpy((*Config).Dir.Utility,"A:\\");
  strcpy((*Config).Dir.Video,"A:\\VIDEO\\");
 }
 return((*Config));
}

/********************************************************************/
/*                                                                  */
/*                    Lecture de la configuration                   */
/*                           1992/06/11                             */
/*                                                                  */
/* Description : þ Cette proc‚dure permet d'obtenir la configur-    */
/*                 ation souhaiter par le consultant.               */
/*                                                                  */
/********************************************************************/

GetConfig(struct ConfigType *Config)
{
 InitConfig(&Config);
}

#endif