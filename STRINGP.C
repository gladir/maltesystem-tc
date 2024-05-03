/*******************************************************************/
/*                                                                 */
/*                Malte System/String (Only Pascal)                */
/*                          1992/10/18                             */
/*                                                                 */
/*           Copyright (C) par les Chevaliers de Malte             */
/*                                                                 */
/*******************************************************************/

//
//      *** Summary information ***
//
//  The file name is        : STRINGP.C
//  The header file name is : no file (Pascal only)
//  Created the             : 1992/10/18
//  Author is               : Sylvain Maltais
//

/**********************************************************************/
/*                           Pascal -- Zone                           */
/**********************************************************************/

#ifdef __PASCAL__

 typedef unsigned char Byte;

 Byte IsASCII(Byte Char)
 {
  return((Char < 128) ? 1 : 0);
 }

 Byte IsAlpha(Byte Char)
 {
  if((Char >= 'A')&&(Char <= 'Z')) return(1);
  if((Char >= 'a')&&(Char <= 'b')) return(1);
  return(0);
 }

 Byte IsCntrl(Byte Char)
 {
  if(Char == 0x7F) return(1);
  if(Char < ' ') return(1);
  return(0);
 }

 Byte IsDigit(Byte Char)
 {
  return(((Char >= '0')&&(Char <= '9')) ? 1 : 0);
 }

 Byte IsLower(Byte Char)
 {
  return(((Char >= 'a')&&(Char <= 'z')) ? 1 : 0);
 }

 Byte IsPrint(Byte Char)
 {
  return(((Char >= ' ')&&(Char <= 0x7E)) ? 1 : 0);
 }

 Byte IsSpace(Byte Char)
 {
  return((Char == ' ') ? 1 : 0);
 }

 Byte IsUpper(Byte Char)
 {
  return(((Char >= 'A')&&(Char <= 'Z')) ? 1 : 0);
 }

 Byte IsXDigit(Byte Char)
 {
  if((Char >= '0')&&(Char <= '9')) return(1);
  if((Char >= 'A')&&(Char <= 'F')) return(1);
  if((Char >= 'a')&&(Char <= 'f')) return(1);
  return(0);
 }

#endif