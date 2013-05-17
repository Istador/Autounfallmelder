#include "MainScreen.h"

#include "DragonFireSDK.h"
#include "Ressources.h"
#include "Unfallgegner.h"
#include "MeineUnfaelle.h"
#include "Kontakt.h"


//####################################################################
//####################################################################
//####             MainScreen Implementation

MainScreen* MainScreen::_instance = 0;
MainScreen* MainScreen::Instance()
{
	if(_instance == 0){
		_instance = new MainScreen;
	}
	return _instance;
}
MainScreen::MainScreen() : WhiteScreen()
{
	top += 10; //aktuelle position - veraendert sich
	
	//Logo
	//ViewAdd(self, Img_Logo, (int)((swidth-ImageGetWidth(Img_Logo))/2), top);
	ViewAdd(self, Img_Logo, 10, top);
	top += ImageGetHeight(Img_Logo)+10;

	//Sie haben oder hatten einen Unfall? (etwa 228px breit)
	//TextAdd(self, (int)((swidth-228)/2), top, "Sie haben oder hatten einen Unfall?", Font);
	//top += 14+10;

	//Bei einem Autounfall sind wir ihr (etwa 202px breit)
	TextAdd(self, 100, top, "Bei einem Autounfall sind wir ihr", Font);
	top += 14+10;

	//Ansprechpartner! (etwa 112px breit)
	TextAdd(self, 100+202-112, top, "Ansprechpartner!", Font);
	top += 14+10;

	top += 40;


	//int btnleft = (int)((swidth-180)/2);
	int btnleft = 30;

	//Neuer Unfall
	ButtonAdd(self, "Buttons/neuerunfall", btnleft, top, MainScreen::OnButton, 1);
	top += 31+10;

	//Mein Unfall
	ButtonAdd(self, "Buttons/meineunfaelle", btnleft, top, MainScreen::OnButton, 2);
	top += 31+10;

	//Kontakt
	ButtonAdd(self, "Buttons/kontakt", btnleft, top, MainScreen::OnButton, 3);
	top += 31+10;


	top += 40;

	/*
	//Unfalldaten eingeben
	TextAdd(self, (int)((swidth-138)/2), top, "Unfalldaten eingeben.", Font);
	top += 14+10;
	
	//Formular abschicken
	TextAdd(self, (int)((swidth-136)/2), top, "Formular abschicken.", Font);
	top += 14+10;
	
	//Formular abschicken
	TextAdd(self, (int)((swidth-152)/2), top, "Der Fall wird bearbeitet!", Font);
	top += 14+10;
	*/

	//Diese App hilft Ihnen dabei
	TextAdd(self, btnleft, top, "Diese App hilft Ihnen dabei", Font);
	top += 14+10;

	//einen Unfall, in wenigen
	TextAdd(self, btnleft, top, "einen Unfall, in wenigen", Font);
	top += 14+10;

	//Schritten, fachgerecht zu
	TextAdd(self, btnleft, top, "Schritten, fachgerecht zu", Font);
	top += 14+10;

	//dokumentieren.
	TextAdd(self, btnleft, top, "dokumentieren.", Font);
	top += 14+10;


	//Felgen-Logo

	ViewAdd(self, Img_Flagge, swidth-ImageGetWidth(Img_Flagge)-10, sheight-ImageGetHeight(Img_Flagge)-10);
}
int MainScreen::OnButton(int id){
	switch(id){
		case 1: Instance()->hide(); UnfallgegnerST->show(); break;
		case 2: Instance()->hide(); UnfaelleST->show(); break;
		case 3: Instance()->hide(); KontaktST->show(); break;
	}
	return id;
}

