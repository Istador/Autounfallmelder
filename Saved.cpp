#include "Saved.h"

#include "DragonFireSDK.h"
#include "Ressources.h"
#include "Zusammenfassung.h"
#include "TouchButton.h"
#include <string>


//####################################################################
//####################################################################
//####             Saved Implementation


Saved* Saved::_instance = 0;


Saved* Saved::Instance()
{
	if(_instance == 0){
		_instance = new Saved;
	}
	return _instance;
}


Saved::Saved() : BlueScreen("Unfall gespeichert")
{
	//Logo
	ViewAdd(self, Img_Logo, 10, top);
	top += ImageGetHeight(Img_Logo)+10;

	//Ihr Unfall wurde gespeichert
	ViewAdd(self, Img_Haken, 10, top);
	TextAdd(self, 10+30+10, top+5, "Ihr Unfall wurde gespeichert!", BlackFont);
	top += 30+10;

	//BOLD Wichtig noch zu beachten:
	TextAdd(self, 10, top, "Wichtig noch zu beachten:", BlackFont);
	top += 14+10;

	//Bitte machen Sie zu guter letzt noch einige
	TextAdd(self, 10, top, "Bitte machen Sie zu guter letzt noch einige", Font);
	top += 14+10;

	//aussagekräftige Fotos vom Unfallort und
	TextAdd(self, 10, top, "aussagekräftige Fotos vom Unfallort und", Font);
	top += 14+10;

	//den Fahrzeugen, so dass die eventuellen
	TextAdd(self, 10, top, "den Fahrzeugen, so dass die eventuellen", Font);
	top += 14+10;

	//Beschädigungen gut sichtbar sind, und
	TextAdd(self, 10, top, "Beschädigungen gut sichtbar sind, und", Font);
	top += 14+10;

	//senden Sie uns diese bitte per E-Mail an:
	TextAdd(self, 10, top, "und senden Sie uns diese bitte per E-Mail an:", Font);
	top += 14+10;
	
	top += 20;

	//BOLD info@Auto-Unfall-Gutachter.de
	TouchButton tb = TouchButton(self, 10, top, "info@Auto-Unfall-Gutachter.de", Saved::OnButton, Saved::OnTouchArea, -337);
	top += tb.Height()+10;
	
	top += 20;

	TextAdd(self, 10, top, "Überprüfen Sie ihre Daten auf der nächs-", BlackFont);
	top += 14+10;
	
	TextAdd(self, 10, top, "ten Seite und schicken Sie sie dann ab!", BlackFont);
	top += 14+10;

	//Zurueck
	//ButtonAdd(self, "Buttons/back", 10, sheight-10-35, Saved::OnButton, 0);

	//Vor
	ButtonAdd(self, "Buttons/next", swidth-10-145, sheight-10-35, Saved::OnButton, 1);
}


int Saved::OnButton(int id){
	if(id == 1)
	{
		SavedST->hide();
		ZusammenfassungST->show();
	}
	else if(id == -337)
	{
		BrowserLaunch("mailto:info@auto-unfall-gutachter.de");
	}
	return id;
}

int Saved::OnTouchArea(int id, int event, int x, int y)
{
	return id;
}

