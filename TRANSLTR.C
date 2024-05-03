/**********************************************************************/
/*                                                                    */
/*                     Malte System/Transltor Numeric                 */
/*                             1992/07/07                             */
/*                                                                    */
/*              Copyright (C) par les Chevaliers de Malte             */
/*                                                                    */
/**********************************************************************/

#ifndef __Malte_Data_Transltor__
 #define __Malte_Data_Transltor__

 #include <TRANSLTR.H>

 #ifndef __PASCAL__

  Byte DataHex[16] = {"0123456789ABCDEF"};
  Byte BaseChar    = 48;

  void Bin15Chn(Byte N, Byte *Chn)
  {
   Byte J;
   for(J = 0; J <= 3; J++) Chn[3-J] = BaseChar + ((N >> J) & 1);
   Chn[4] = 0;
  }

  void Bin15Chn_(Byte N, Byte *Chn)
  {
   Byte J;
   for(J = 0; J <= 3; J++) Chn[3-J] = 48 + ((N >> J) & 1);
   Chn[4] = 0;
  }

  void Bin255Chn(Byte N, Byte *Chn)
  {
   Byte J;
   for(J = 0; J <= 7; J++) Chn[7-J] = BaseChar + ((N >> J) & 1);
   Chn[8] = 0;
  }

  void Bin255Chn_(Byte N, Byte *Chn)
  {
   Byte J;
   for(J = 0; J <= 7; J++) Chn[7-J] = 48 + ((N >> J) & 1);
   Chn[8] = 0;
  }

  void Bin65535Chn(Word N, Byte *Chn)
  {
   Byte J;
   for(J = 0; J <= 15; J++) Chn[15-J] = BaseChar + ((N >> J) & 1);
   Chn[16] = 0;
  }

  void Bin65535Chn_(Word N, Byte *Chn)
  {
   Byte J;
   for(J = 0; J <= 15; J++) Chn[15-J] = 48 + ((N >> J) & 1);
   Chn[16] = 0;
  }

  void _Dec15Chn(Byte I, Byte *Chn)
  {
   if(I > 9)
   {
    Chn[0] = BaseChar + 1;
    Chn[1] = BaseChar - 10 + I;
    Chn[2] = 0;
   }
    else
   {
    Chn[0] = BaseChar + I;
    Chn[1] = 0;
   }
  }

  void _Dec15Chn_(Byte I, Byte *Chn)
  {
   if(I > 9)
   {
    Chn[0] = 49;
    Chn[1] = 38 + I;
    Chn[2] = 0;
   }
    else
   {
    Chn[0] = 48 + I;
    Chn[1] = 0;
   }
  }

  void Dec255Chn(Byte I, Byte *Chn)
  {
   Chn[0] = BaseChar + (I / 100);
   Chn[1] = BaseChar + ((I / 10) % 10);
   Chn[2] = BaseChar + ((I % 100) % 10);
   Chn[3] = 0;
  }

  void Dec65535Chn(Word I, Byte *Chn)
  {
   Chn[0] = BaseChar + (I / 10000);
   Chn[1] = BaseChar + ((I / 1000) % 10);
   Chn[2] = BaseChar + ((I / 100) % 10);
   Chn[3] = BaseChar + ((I / 10) % 10);
   Chn[4] = BaseChar + ((I % 100) % 10);
   Chn[5] = 0;
  }

  void Dec255Chn_(Byte I, Byte *Chn)
  {
   Chn[0] = 48 + (I / 100);
   Chn[1] = 48 + ((I / 10) % 10);
   Chn[2] = 48 + ((I % 100) % 10);
   Chn[3] = 0;
  }

  void _Dec255Chn(Byte I, Byte *Chn)
  {
   if(I > 99)
   {
    Chn[0] = BaseChar + (I / 100);
    Chn[1] = BaseChar + ((I / 10) % 10);
    Chn[2] = BaseChar + ((I % 100) % 10);
    Chn[3] = 0;
   }
    else
   if(I > 9)
   {
    Chn[0] = BaseChar + (I / 10);
    Chn[1] = BaseChar + ((I % 10) % 10);
    Chn[2] = 0;
   }
    else
   {
    Chn[0] = BaseChar + I;
    Chn[1] = 0;
   }
  }

  void _Dec255Chn_(Byte I, Byte *Chn)
  {
   if(I > 99)
   {
    Chn[0] = 48 + (I / 100);
    Chn[1] = 48 + ((I / 10) % 10);
    Chn[2] = 48 + ((I % 100) % 10);
    Chn[3] = 0;
   }
    else
   if(I > 9)
   {
    Chn[0] = 48 + (I / 10);
    Chn[1] = 48 + ((I % 10) % 10);
    Chn[2] = 0;
   }
    else
   {
    Chn[0] = 48 + I;
    Chn[1] = 0;
   }
  }

  Byte GetBaseNumeric(void)
  {
   return(BaseChar);
  }

  void Hex255Chn(Byte N, Byte *Chn)
  {
   Chn[0] = DataHex[N >> 4];
   Chn[1] = DataHex[N & 0x0F];
   Chn[2] = 0;
  }

  void Hex65535Chn(Word N, Byte *Chn)
  {
   Chn[0] = DataHex[N >> 12];
   Chn[1] = DataHex[(N >> 8) & 0x0F];
   Chn[2] = DataHex[(N >> 4) & 0x0F];
   Chn[3] = DataHex[N & 0x0F];
   Chn[4] = 0;
  }

  void Oct255Chn(Byte N, Byte *Chn)
  {
   Chn[0] = BaseChar + ((N & 448) >> 6);
   Chn[1] = BaseChar + ((N & 56) >> 3);
   Chn[2] = BaseChar + (N & 7);
   Chn[3] = 0;
  }

  void Oct255Chn_(Byte N, Byte *Chn)
  {
   Chn[0] = 48 + ((N & 448) >> 6);
   Chn[1] = 48 + ((N & 56) >> 3);
   Chn[2] = 48 + (N & 7);
   Chn[3] = 0;
  }

  void SetBaseNumeric(Byte Nombre)
  {
   Byte I;
   BaseChar = Nombre;
   for(I = 0; I <= 9; I++) DataHex[I] = Nombre + I;
  }

  void SetBaseHex(Byte Nombre)
  {
   Byte I;
   for(I=0;I<=5;I++) DataHex[0x0A+I] = Nombre + I;
  }

 #else

  extern Byte DataHex[15];
  extern Byte BaseChar;

  void Bin15Chn(Byte N, Byte *Chn)
  {
   Byte J;
   for(J = 0; J <= 3; J++) Chn[4-J] = BaseChar + ((N >> J) & 1);
   Chn[0] = 4;
  }

  void Bin15Chn_(Byte N, Byte *Chn)
  {
   Byte J;
   for(J = 0; J <= 3; J++) Chn[4-J] = 48 + ((N >> J) & 1);
   Chn[0] = 4;
  }

  void BinByteChn(Byte N, Byte *Chn)
  {
   Byte J;
   for(J = 0; J <= 7; J++) Chn[8-J] = BaseChar + ((N >> J) & 1);
   Chn[0] = 8;
  }

  void BinByteChn_(Byte N, Byte *Chn)
  {
   Byte J;
   for(J = 0; J <= 7; J++) Chn[8-J] = 48 + ((N >> J) & 1);
   Chn[0] = 8;
  }

  void BinWordChn(Word N, Byte *Chn)
  {
   Byte J;
   for(J = 0; J <= 15; J++) Chn[16-J] = BaseChar + ((N >> J) & 1);
   Chn[0] = 16;
  }

  void BinWordChn_(Word N, Byte *Chn)
  {
   Byte J;
   for(J = 0; J <= 15; J++) Chn[16-J] = 48 + ((N >> J) & 1);
   Chn[0] = 16;
  }

  void _Dec15Chn(Byte I, Byte *Chn)
  {
   if(I > 9)
   {
    Chn[1] = BaseChar + 1;
    Chn[2] = BaseChar - 10 + I;
    Chn[0] = 2;
   }
    else
   {
    Chn[1] = BaseChar + I;
    Chn[0] = 1;
   }
  }

  void _Dec15Chn_(Byte I, Byte *Chn)
  {
   if(I > 9)
   {
    Chn[1] = 49;
    Chn[2] = 38 + I;
    Chn[0] = 2;
   }
    else
   {
    Chn[1] = 48 + I;
    Chn[0] = 1;
   }
  }

  void DecByteChn(Byte I, Byte *Chn)
  {
   Chn[1] = BaseChar + (I / 100);
   Chn[2] = BaseChar + ((I / 10) % 10);
   Chn[3] = BaseChar + ((I % 100) % 10);
   Chn[0] = 3;
  }

  void DecWordChn(Word I, Byte *Chn)
  {
   Chn[1] = BaseChar + (I / 10000);
   Chn[2] = BaseChar + ((I / 1000) % 10);
   Chn[3] = BaseChar + ((I / 100) % 10);
   Chn[4] = BaseChar + ((I / 10) % 10);
   Chn[5] = BaseChar + ((I % 100) % 10);
   Chn[0] = 5;
  }

  void DecByteChn_(Byte I, Byte *Chn)
  {
   Chn[1] = 48 + (I / 100);
   Chn[2] = 48 + ((I / 10) % 10);
   Chn[3] = 48 + ((I % 100) % 10);
   Chn[0] = 3;
  }

  void _DecByteChn(Byte I, Byte *Chn)
  {
   if(I > 99)
   {
    Chn[1] = BaseChar + (I / 100);
    Chn[2] = BaseChar + ((I / 10) % 10);
    Chn[3] = BaseChar + ((I % 100) % 10);
    Chn[0] = 3;
   }
    else
   if(I > 9)
   {
    Chn[1] = BaseChar + (I / 10);
    Chn[2] = BaseChar + ((I % 10) % 10);
    Chn[0] = 2;
   }
    else
   {
    Chn[1] = BaseChar + I;
    Chn[0] = 1;
   }
  }

  void _DecByteChn_(Byte I, Byte *Chn)
  {
   if(I > 99)
   {
    Chn[1] = 48 + (I / 100);
    Chn[2] = 48 + ((I / 10) % 10);
    Chn[3] = 48 + ((I % 100) % 10);
    Chn[0] = 3;
   }
    else
   if(I > 9)
   {
    Chn[1] = 48 + (I / 10);
    Chn[2] = 48 + ((I % 10) % 10);
    Chn[0] = 2;
   }
    else
   {
    Chn[1] = 48 + I;
    Chn[0] = 1;
   }
  }

  void _DecWordChn(Word I, Byte *Chn)
  {
   if(I > 9999)
   {
    Chn[1] = BaseChar + (I / 10000);
    Chn[2] = BaseChar + ((I / 1000) % 10);
    Chn[3] = BaseChar + ((I / 100) % 10);
    Chn[4] = BaseChar + ((I / 10) % 10);
    Chn[5] = BaseChar + ((I % 100) % 10);
    Chn[0] = 5;
   }
    else
   if(I > 999)
   {
    Chn[1] = BaseChar + ((I / 1000) % 10);
    Chn[2] = BaseChar + ((I / 100) % 10);
    Chn[3] = BaseChar + ((I / 10) % 10);
    Chn[4] = BaseChar + ((I % 100) % 10);
    Chn[0] = 4;
   }
    else
   if(I > 99)
   {
    Chn[1] = BaseChar + (I / 100);
    Chn[2] = BaseChar + ((I / 10) % 10);
    Chn[3] = BaseChar + ((I % 100) % 10);
    Chn[0] = 3;
   }
    else
   if(I > 9)
   {
    Chn[1] = BaseChar + (I / 10);
    Chn[2] = BaseChar + ((I % 10) % 10);
    Chn[0] = 2;
   }
    else
   {
    Chn[1] = BaseChar + I;
    Chn[0] = 1;
   }
  }

  void _DecWordChn_(Word I, Byte *Chn)
  {
   if(I > 9999)
   {
    Chn[1] = 48 + (I / 10000);
    Chn[2] = 48 + ((I / 1000) % 10);
    Chn[3] = 48 + ((I / 100) % 10);
    Chn[4] = 48 + ((I / 10) % 10);
    Chn[5] = 48 + ((I % 100) % 10);
    Chn[0] = 5;
   }
    else
   if(I > 999)
   {
    Chn[1] = 48 + ((I / 1000) % 10);
    Chn[2] = 48 + ((I / 100) % 10);
    Chn[3] = 48 + ((I / 10) % 10);
    Chn[4] = 48 + ((I % 100) % 10);
    Chn[0] = 4;
   }
    else
   if(I > 99)
   {
    Chn[1] = 48 + (I / 100);
    Chn[2] = 48 + ((I / 10) % 10);
    Chn[3] = 48 + ((I % 100) % 10);
    Chn[0] = 3;
   }
    else
   if(I > 9)
   {
    Chn[1] = 48 + (I / 10);
    Chn[2] = 48 + ((I % 10) % 10);
    Chn[0] = 2;
   }
    else
   {
    Chn[1] = 48 + I;
    Chn[0] = 1;
   }
  }

  Byte GetBaseNumeric(void)
  {
   return(BaseChar);
  }

  void HexByteChn(Byte N, Byte *Chn)
  {
   Chn[1] = DataHex[N >> 4];
   Chn[2] = DataHex[N & 0x0F];
   Chn[0] = 2;
  }

  void HexWordChn(Word N, Byte *Chn)
  {
   Chn[1] = DataHex[N >> 12];
   Chn[2] = DataHex[(N >> 8) & 0x0F];
   Chn[3] = DataHex[(N >> 4) & 0x0F];
   Chn[4] = DataHex[N & 0x0F];
   Chn[0] = 4;
  }

  void OctByteChn(Byte N, Byte *Chn)
  {
   Chn[1] = BaseChar + ((N & 448) >> 6);
   Chn[2] = BaseChar + ((N & 56) >> 3);
   Chn[3] = BaseChar + (N & 7);
   Chn[0] = 3;
  }

  void OctByteChn_(Byte N, Byte *Chn)
  {
   Chn[1] = 48 + ((N & 448) >> 6);
   Chn[2] = 48 + ((N & 56) >> 3);
   Chn[3] = 48 + (N & 7);
   Chn[0] = 3;
  }

  void SetBaseNumeric(Byte Nombre)
  {
   Byte I;
   BaseChar = Nombre;
   for(I = 0; I <= 9; I++) DataHex[I] = Nombre + I;
  }

  void SetBaseHex(Byte Nombre)
  {
   Byte I;
   for(I=0;I<=5;I++) DataHex[0x0A+I] = Nombre + I;
  }

 #endif

 void SetHexDownCase(void)
 {
  DataHex[0x0A] = 'a';
  DataHex[0x0B] = 'b';
  DataHex[0x0C] = 'c';
  DataHex[0x0D] = 'd';
  DataHex[0x0E] = 'e';
  DataHex[0x0F] = 'f';
 }

 void SetHexUpCase(void)
 {
  DataHex[0x0A] = 'A';
  DataHex[0x0B] = 'B';
  DataHex[0x0C] = 'C';
  DataHex[0x0D] = 'D';
  DataHex[0x0E] = 'E';
  DataHex[0x0F] = 'F';
 }

#endif
