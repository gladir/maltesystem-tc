/**********************************************************************/
/*                                                                    */
/*                         Malte System/Level                         */
/*                            1992/07/08                              */
/*                                                                    */
/*             Copyright (C) par les Chevaliers de Malte              */
/*                                                                    */
/**********************************************************************/

#ifndef __Malte_Video_Level__
 #define __Malte_Video_Level__

 #include <VIDEO\LEVEL.H>

 unsigned char Security = 0;
 unsigned char Level    = 0;

 unsigned char GetLevel(void)
 {
  return(Level);
 }

 unsigned char GetSecurity(void)
 {
  return(Security);
 }

 void SetLevel(unsigned char L)
 {
  Level = L;
 }

 void SetSecurity(unsigned char S)
 {
  Security = S;
 }

#endif