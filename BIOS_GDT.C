/**********************************************************************/
/*                                                                    */
/*                     Malte System/BIOS Gadget                       */
/*                            1992/06/30                              */
/*                                                                    */
/*              Copyright (C) par les Chevaliers de Malte             */
/*                                                                    */
/**********************************************************************/

#ifndef __Malte_BIOS_Video_Text_Gadget__
 #define __Malte_BIOS_Video_Text_Gadget__

 #include <VIDEO\TEXT\BIOS.H>
 #include <NUMERIC.H>
 #include <VIDEO\BIOS_VID.H>
 #include <VIDEO\CURSOR\BIOS.H>

 extern struct {
                Byte Shade;
                Byte SpaceBorde;
                TypeCadre Borde;
                Word ColnDouble;
                Byte Coln;
                Byte Line;
                Byte MaxX;
                Byte MaxY;
                Byte HalfMaxX;
                Byte RX;
                Byte RY;
                Byte ColorNor;
                Byte LastColor;
               }
               VB;

 #ifdef __PASCAL__

 void BIOS_WriteOP(void)
 {
  BIOS_WriteTyping_("\x02 (");
 }

 void BIOS_WriteCP(void)
 {
  BIOS_WriteTyping_("\x02h)");
 }

 void BIOS_WriteDescrLn(String Chn, Byte Sep, Word Value)
 {
  Byte Tmp[10];
  BIOS_WriteTyping_(Chn);
  Tmp[0] = 3; 
  Tmp[1] = ' ';
  Tmp[2] = Sep;
  Tmp[3] = ' ';
  BIOS_WriteTyping_(Tmp);
  _DecWordChn_(Value,Tmp);
  BIOS_WriteTyping_(Tmp);
  BIOS_WriteOP();
  HexWordChn(Value,Tmp);
  BIOS_WriteTyping_(Tmp);
  BIOS_WriteCP();
  VB.RX = 0; VB.RY++;
 }

 void BIOS_BiWriteDescrLn(Byte Langue, String Chn0, String Chn1, Byte Sep, Word Value)
 {
  if(Langue == 0) BIOS_WriteDescrLn(Chn0,Sep,Value);
             else BIOS_WriteDescrLn(Chn1,Sep,Value);
 }

 void BIOS_WriteDescrLnB(String Chn, Byte Sep, Byte Value)
 {
  Byte Tmp[10];
  BIOS_WriteTyping_(Chn);
  Tmp[0] = 3; 
  Tmp[1] = ' ';
  Tmp[2] = Sep;
  Tmp[3] = ' ';
  BIOS_WriteTyping_(Tmp);
  _DecByteChn_(Value,Tmp);
  BIOS_WriteTyping_(Tmp);
  BIOS_WriteOP();
  HexByteChn(Value,Tmp);
  BIOS_WriteTyping_(Tmp);
  BIOS_WriteCP();
  VB.RX = 0; VB.RY++;
 }

 void BIOS_BiWriteDescrLnB(Byte Langue, String Chn0, String Chn1, Byte Sep, Byte Value)
 {
  if(Langue == 0) BIOS_WriteDescrLnB(Chn0,Sep,Value);
             else BIOS_WriteDescrLnB(Chn1,Sep,Value);
 }

 void BIOS_WriteDescr_(String Chn, Byte Num, Byte Sep, Word Value)
 {
  Byte Tmp[10];
  BIOS_WriteTyping_(Chn);
  VB.RX += (Num-Chn[0]);
  Tmp[0] = 3; 
  Tmp[1] = ' ';
  Tmp[2] = Sep;
  Tmp[3] = ' ';
  BIOS_WriteTyping_(Tmp);
  _DecWordChn_(Value,Tmp);
  BIOS_WriteTyping_(Tmp);
  BIOS_WriteOP();
  HexWordChn(Value,Tmp);
  BIOS_WriteTyping_(Tmp);
  BIOS_WriteCP();
 }

 void BIOS_BiWriteDescr_(Byte Langue, String Chn0, String Chn1, Byte Num, Byte Sep, Word Value)
 {
  if(Langue == 0) BIOS_WriteDescr_(Chn0,Num,Sep,Value);
             else BIOS_WriteDescr_(Chn1,Num,Sep,Value);
 }

 void BIOS_WriteDescrLn_(String Chn, Byte Num, Byte Sep, Word Value)
 {
  BIOS_WriteDescr_(Chn,Num,Sep,Value);
  VB.RX = 0; VB.RY++;
 }

 void BIOS_BiWriteDescrLn_(Byte Langue, String Chn0, String Chn1, Byte Num, Byte Sep, Word Value)
 {
  if(Langue == 0) BIOS_WriteDescrLn_(Chn0,Num,Sep,Value);
             else BIOS_WriteDescrLn_(Chn1,Num,Sep,Value);
 }

 void BIOS_WriteDescrLnH_(String Chn, Byte Num, Byte Sep, Word Value)
 {
  Byte Tmp[10];
  BIOS_WriteTyping_(Chn);
  VB.RX += (Num-Chn[0]);
  Tmp[0] = 3; 
  Tmp[1] = ' ';
  Tmp[2] = Sep;
  Tmp[3] = ' ';
  BIOS_WriteTyping_(Tmp);
  HexWordChn(Value,Tmp);
  BIOS_WriteTyping_(Tmp);
  BIOS_WriteTypingLn("\x01h");
 }

 void BIOS_BiWriteDescrLnH_(Byte Langue, String Chn0, String Chn1, Byte Num, Byte Sep, Word Value)
 {
  if(Langue == 0) BIOS_WriteDescrLnH_(Chn0,Num,Sep,Value);
             else BIOS_WriteDescrLnH_(Chn1,Num,Sep,Value);
 }

 void BIOS_WriteDescrB_(String Chn, Byte Num, Byte Sep, Byte Value)
 {
  Byte Tmp[10];
  BIOS_WriteTyping_(Chn);
  VB.RX += (Num-Chn[0]);
  Tmp[0] = 3; 
  Tmp[1] = ' ';
  Tmp[2] = Sep;
  Tmp[3] = ' ';
  BIOS_WriteTyping_(Tmp);
  _DecByteChn_(Value,Tmp);
  BIOS_WriteTyping_(Tmp);
  BIOS_WriteOP();
  HexByteChn(Value,Tmp);
  BIOS_WriteTyping_(Tmp);
  BIOS_WriteCP();
 }

 void BIOS_BiWriteDescrB_(Byte Langue, String Chn0, String Chn1, Byte Num, Byte Sep, Byte Value)
 {
  if(Langue == 0) BIOS_WriteDescrB_(Chn0,Num,Sep,Value);
             else BIOS_WriteDescrB_(Chn1,Num,Sep,Value);
 }

 void BIOS_WriteDescrLnB_(String Chn, Byte Num, Byte Sep, Byte Value)
 {
  BIOS_WriteDescrB_(Chn,Num,Sep,Value);
  VB.RX = 0; VB.RY++;
 }

 void BIOS_BiWriteDescrLnB_(Byte Langue, String Chn0, String Chn1, Byte Num, Byte Sep, Byte Value)
 {
  if(Langue == 0) BIOS_WriteDescrLnB_(Chn0,Num,Sep,Value);
             else BIOS_WriteDescrLnB_(Chn1,Num,Sep,Value);
 }

 void BIOS_BiWriteTextLn(Byte Langue, String Chn0, String Chn1) 
 {
  if(Langue == 0) BIOS_WriteTypingLn(Chn0);
             else BIOS_WriteTypingLn(Chn1);
 }

 void BIOS_BiWriteText(Byte Langue, String Chn0, String Chn1)
 {
  if(Langue == 0) BIOS_WriteTyping_(Chn0);
             else BIOS_WriteTyping_(Chn1);
 }

 void BIOS_BiWriteDcr(Byte Langue, String Chn0, String Chn1, Byte Num, Byte Sep)
 {
  Byte Tmp[10];
  if(Langue == 0)
  {
   BIOS_WriteTyping_(Chn0);
   VB.RX += (Num-Chn0[0]);
  }
   else
  {
   BIOS_WriteTyping_(Chn1);
   VB.RX += (Num-Chn1[0]);
  }
  Tmp[0] = 3;
  Tmp[1] = ' ';
  Tmp[2] = Sep;
  Tmp[3] = ' ';
  BIOS_WriteTyping_(Tmp);
 }

 #endif

#endif
