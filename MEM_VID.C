/*******************************************************************/
/*                                                                 */
/*                   Malte System/Direct Video                     */
/*                          1992/05/27                             */
/*                                                                 */
/*            Copyright (C) par les Chevaliers de Malte            */
/*                                                                 */
/*******************************************************************/

#ifndef __Malte_Video_Memory__
 #define __Malte_Video_Memory__

 #include <VIDEO\MEM_VID.H>

 #ifndef __PASCAL__
  Byte HauteurTexte(void)
 #else
  Byte TextHeight(void)
 #endif
 {
  Byte Tmp = *(Byte *far) 0x00400085;
  return(Tmp == 0 ? 8 : Tmp);
 }

 #ifndef __PASCAL__
  Word NombreTexteX(void)
 #else
  Word XTextNum(void)
 #endif
 {
  return(*(Byte *far) 0x0040004A);
 }

 #ifndef __PASCAL__
  Byte NombreTexteY(void)
 #else
  Byte YTextNum(void)
 #endif
 {
  Byte Tmp = *(Byte *far) 0x00400084;
  return(Tmp == 0 ? 25 : Tmp+1);
 }

 #ifndef __PASCAL__
  Word NombrePixelX(void) { return(NombreTexteX() << 3); }
 #else
  Word XPixelNum(void) { return(XTextNum() << 3); }
 #endif

 #ifndef __PASCAL__
  Word NombrePixelY(void) { return(NombreTexteY() * HauteurTexte()); }
 #else
  Word YPixelNum(void) { return(YTextNum() * TextHeight()); }
 #endif

 #ifndef __PASCAL__
  Word SegmentVideoTexte(void)
 #else
  Word TextSegment(void)
 #endif
  {
   return(((*(Word *far) 0x00400063) == 0x3B4) ? 0xB000 : 0xB800);
  }

 Byte MEM_GetVideoMode(void) { return(*(Byte *far) 0x00400049); }
 Byte MEM_GetPage(void) { return(*(Byte *far) 0x00400062); } 
 Word MEM_SizePageVideo(void) { return(*(Word *far) 0x0040004C); }
 Word MEM_PortVideo(void) { return(*(Word *far) 0x00400063); }

#endif