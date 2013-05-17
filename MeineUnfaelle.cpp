#include "MeineUnfaelle.h"

#include "DragonFireSDK.h"
#include "Ressources.h"
#include "TouchButton.h"
#include "Zusammenfassung.h"
#include "SQLite.h"

//####################################################################
//####################################################################
//####             Meine Unfaelle Implementation


MeineUnfaelle* MeineUnfaelle::_instance = 0;


MeineUnfaelle* MeineUnfaelle::Instance()
{
	if(_instance == 0){
		_instance = new MeineUnfaelle;
	}
	return _instance;
}


MeineUnfaelle::MeineUnfaelle() : BlueScreen("Meine Unfälle")
{
	TouchAdd(self, 0, top-10, swidth, sheight-top+10, MeineUnfaelle::OnTouchArea, 0);
	
	top += 10;

	btncnt = 0;
}


int MeineUnfaelle::OnButton(int id){
	UnfaelleST->hide();
	ZusammenfassungST->LoadUnfall(&(Unfall::UnfallMap[id]));
	ZusammenfassungST->show();
	return id;
}


int lasty = -1;
int MeineUnfaelle::OnTouchArea(int id, int event, int x, int y)
{
	if(event == 1)
	{
		lasty = y;
	}
	else if(event == 2)
	{
		if(lasty != -1)
		{
			int move = ContainerGety(UnfaelleST->btncnt) - (lasty - y);
			lasty = y;

			int max = UnfaelleST->top;
			int min = -UnfaelleST->btntop + UnfaelleST->sheight - 20;

			if(UnfaelleST->sheight - UnfaelleST->top > UnfaelleST->btntop){
				return id;
			}

			if(move > max){ move = max; }
			else if(move < min){ move = min; }
			ContainerSety(UnfaelleST->btncnt, move);
		}
	}
	else if(event == 3)
	{
		lasty = -1;
	}
	return id;
}


void MeineUnfaelle::Refresh(){
	if(btncnt != 0)
		ContainerSetVisible(btncnt,0);
	btncnt = ContainerAdd(self, 10, top);
	btntop = 0;
}

//#include <algorithm>
//#include <regex>
void MeineUnfaelle::AddUnfall(Unfall* u)
{
	char text[70]; // 12+30+20 = 62
	/*
	char date[23];
	strcpy_s(date, u->Date());
	std::string d = std::regex_replace(date,std::regex(" ")," um ");
	sprintf_s(text, "Unfall #%i am %s", u->ID(), d.c_str());
	*/
	sprintf_s(text, "Unfall #%i am %s", u->ID(), u->Date());

	TouchButton tb = TouchButton(btncnt, 0, btntop, text, MeineUnfaelle::OnButton, MeineUnfaelle::OnTouchArea, u->ID());
	if(u->State() == 2) tb.HakenAdd();

	btntop += tb.Height()+10;
}
