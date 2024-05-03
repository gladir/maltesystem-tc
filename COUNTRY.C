#include <DOS.H>
#include <TRANSLTR.H>
#include <VIDEO\TEXT.H>

Byte *StrCurrentCountry = "Pays courant";

void CheckCountry(void)
{
 const X = 2, Y = 4, XData = 26, Width = 50;
 struct COUNTRY CurCountry;
 country(0,&CurCountry);
 PutFillBorder(X,Y,X+Width,Y+15,0x9F);
 SetColor(0xF0);
 _BarTextHori(X,Y,X+Width,' ');
 _WriteText(X+((Width-strlen(StrCurrentCountry))/2),Y,StrCurrentCountry);
 SetColor(0x9F);
 _WriteText(X+2,Y+2,"Format de la date     :");
 _WriteText(X+2,Y+3,"Symbole de la monnaie :");
 _WriteText(X+2,Y+4,"S‚parateur de millier :");
 _WriteText(X+2,Y+5,"S‚parateur de d‚cimal :");
 _WriteText(X+2,Y+6,"S‚parateur de date    :");
 _WriteText(X+2,Y+7,"S‚parateur de l'heure :");
 _WriteText(X+2,Y+8,"Symbole de la monnaie :");
 _WriteText(X+2,Y+9,"Pr‚cision             :");
 _WriteText(X+2,Y+10,"Format horaire        :");
 _WriteText(X+2,Y+11,"S‚parateur de donn‚e  :");
 if(CurCountry.co_date == 0) _WriteText(X+XData,Y+2,"Etat-Unis"); else
 if(CurCountry.co_date == 1) _WriteText(X+XData,Y+2,"Europ‚en"); else
 if(CurCountry.co_date == 2) _WriteText(X+XData,Y+2,"Japonnais");
			else _WriteText(X+XData,Y+2,"Inconnu");
 _WriteText(X+XData,Y+3,CurCountry.co_curr);
 _WriteText(X+XData,Y+4,CurCountry.co_thsep);
 _WriteText(X+XData,Y+5,CurCountry.co_desep);
 _WriteText(X+XData,Y+6,CurCountry.co_dtsep);
 _WriteText(X+XData,Y+7,CurCountry.co_tmsep);
 if((CurCountry.co_currstyle & 3) == 0) _WriteText(X+XData,Y+8,"Avant & Pas espace"); else
 if((CurCountry.co_currstyle & 3) == 1) _WriteText(X+XData,Y+8,"AprŠs & Pas espace"); else
 if((CurCountry.co_currstyle & 3) == 2) _WriteText(X+XData,Y+8,"Avant & Un espace"); else
 if((CurCountry.co_currstyle & 3) == 3) _WriteText(X+XData,Y+8,"AprŠs & Un espace");
 {
  Byte Chn[10];
  _Dec255Chn(CurCountry.co_digits,Chn);
  _WriteText(X+XData,Y+9,Chn);
 }
 if((CurCountry.co_time & 1) == 0) _WriteText(X+XData,Y+10,"Horloge 12 heures"); else
 if((CurCountry.co_time & 1) == 1) _WriteText(X+XData,Y+10,"Horloge 24 heures");
 _WriteText(X+XData,Y+11,CurCountry.co_dasep);
}