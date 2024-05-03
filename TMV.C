/*******************************************************************/
/*                                                                 */
/*                  Malte System/Check Video Mode                  */
/*                            1992/06/13                           */
/*                                                                 */
/*          Copyright (C) par les Chevaliers de Malte              */
/*                                                                 */
/*  Description : þ Cette unit‚ teste les modes vid‚os disponible  */
/*                  sur l'ordinateur en cours d'utilisation.       */
/*                                                                 */
/*******************************************************************/

#ifndef __Malte_Teste_Mode_Video__
 #define __Malte_Teste_Mode_Video__

 #include <time.h>
 #include <mem.h>

 #define True                 1
 #define False                0

 #define NoError              0
 #define InvalidVideoMode     1
 #define InvalidColonneVideo  2
 #define InvalidPageVideo     3

 extern unsigned char CheckVideoLogic(void)
 extern unsigned char IsTextMode(void)
 extern double        CheckSpeedScrollUp(Word TauxRepetition)
 extern double        CheckSpeedPut(Word TauxRepetition)
 extern double        CheckSpeedDirect(Word TauxRepetition)

 unsigned char CheckVideoLogic(void)
 {
  if(GetVideoMode() != peekb(0x0040,0x49)) return(1); else
  if(GetColonne()   != peek(0x0040,0x4A))  return(2); else
  if(GetPage()      != peekb(0x0040,0x62)) return(3);
				      else return(0);
 }

 unsigned char CheckVideoMode(void)
 {
   // Local variable //
  unsigned char AX,AY;
  unsigned char AC;
  unsigned char T;
   // Sous-programme de d‚tection //
  GetPosCursor(AX,AY,0);
  AncienCaractere = BIOS_GetChar(0,0,0);
  BIOS_PutChar(!AncienCaractere);
  if(peekb(SegmentVideoTexte(),peek(0x0040,0x4E)) == !AC) T = 1;
						     else T = 0;
  BIOS_SetPosCursor(0,0,0);
  PutChar(AncienCaractere);
  BIOS_SetPosCursor(AncienX,AncienY);
  return(T);
 }

 double CheckSpeedScrollUp(unsigned int TauxRepetition)
 {
   // Local variable //
  unsigned int I;
  time_t First;
  time_t Second;
   /* Sous-programme de teste */
  SetPosCursor(0,0);
  First = time(NULL);
  for(I = 1;I <= TauxRepetition;I++)
  {
   PutStringLn("Teste la vitesse de mont‚ d''‚cran en cours...");
  }
  Second = time(NULL);
  return difftime(Second,First);
 }

 double CheckSpeedPut(Word TauxRepetition)
 {
   /* Local variable */
  Word   I;
  time_t First;
  time_t Second;
  Byte   Ligne;
   /* Sous-programme de teste */
  First = time(NULL);
  for(I = 1; I <= (TauxRepetition/(NombreTexteY()-1));I++)
  {
   PutBoxSpace(0,0,(NombreTexteX()-1),(NombreTexteY()-1),7);
   for(Ligne = 0;(NombreTexteY()-2);Ligne++)
   {
    SetPosCursor(0,Ligne);
    PutStringLn("Teste la vitesse affichage en cours...");
   }
  }
  Second = time(NULL);
  return(difftime(Second,First));
 }

 double CheckSpeedDirect(Word TauxRepetition)
 {
   /* Local variable */
  Word   I;
  Word   CE;
  Byte   Valeur;
  Word   Segm;
  time_t First;
  time_t Second;
   /* Sous-programme de teste */
  Segm    = SegmentVideoTexte();
  Valeur  = 0;
  First   = time(NULL);
  SetPosCursor(0,0);
  for(I = 1;I <= TauxRepetition;I++)
  {
   for(CE = 0;peek(0x0040,0x4C)-1;CE++) pokeb(Segm,CE*2,Valeur);
   Valeur = Valeur & 255;
  }
  Second = time(NULL);
  return (difftime(Second,First));
 }

#endif