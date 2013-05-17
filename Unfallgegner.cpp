#include "Unfallgegner.h"

#include "DragonFireSDK.h"
#include "Ressources.h"
#include "IhreDaten.h"
#include <string>


//####################################################################
//####################################################################
//####             Unfallgegner Implementation


Unfallgegner* Unfallgegner::_instance = 0;


Unfallgegner* Unfallgegner::Instance()
{
	if(_instance == 0){
		_instance = new Unfallgegner;
	}
	return _instance;
}


Unfallgegner::Unfallgegner() : BlueScreen("Schritt 1/3 - Unfallgegner")
{
	TextAdd(self, 10, top, "Daten des Unfallgegners eingeben:", BlackFont);
	top += 14+10;

	top += 20;

	name = AddEditBox("Vor- und Nachname", 0);
	tel = AddEditBox("Telefonnummer (optional)", 1);
	email = AddEditBox("E-Mail (optional)", 2);
	versicherung = AddEditBox("KFZ-Versicherung", 0);
	kennzeichen = AddHalfEditBox("KFZ-Kennzeichen", 0);

	top += 20;

	//Bitte machen Sie außerdem einige Bilder
	TextAdd(self, 10, top, "Bitte machen Sie außerdem einige Bilder", BlackFont);
	top += 14+10;

	//des Unfallortes und des Unfallautos!
	TextAdd(self, 10, top, "des Unfallortes und des Unfallautos!", BlackFont);
	top += 14+10;

	top += 20;

	warning = TextAdd(self, 10, top, "Geben Sie alle benötigten Felder ein!", RedFont);
	TextSetVisible(warning, 0);

	//Zurueck
	//ButtonAdd(self, "Buttons/back", 10, sheight-10-35, Unfallgegner::OnButton, 0);

	//Vor
	ButtonAdd(self, "Buttons/next", swidth-10-145, sheight-10-35, Unfallgegner::OnButton, 1);
}


int Unfallgegner::OnButton(int id){
	if(id == 1)
	{
		if(
			strcmp("",UnfallgegnerST->name->Text()) != 0 
			&& strcmp("",UnfallgegnerST->kennzeichen->Text()) != 0
			&& strcmp("",UnfallgegnerST->versicherung->Text()) != 0
			)
		{
			UnfallgegnerST->hide();
			IhreDatenST->show();
		}
		else{
			TextSetVisible(UnfallgegnerST->warning, 1);
			Vibrate();
		}
	}
	return id;
}


void Unfallgegner::show()
{
	TextSetVisible(warning, 0);
	Screen::show();
}


