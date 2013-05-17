#include "IhreDaten.h"

#include "DragonFireSDK.h"
#include "Ressources.h"
#include "Unfallgegner.h"
#include "Unfallhergang.h"
#include <string>


//####################################################################
//####################################################################
//####             IhreDaten Implementation


IhreDaten* IhreDaten::_instance = 0;


IhreDaten* IhreDaten::Instance()
{
	if(_instance == 0){
		_instance = new IhreDaten;
	}
	return _instance;
}


IhreDaten::IhreDaten() : BlueScreen("Schritt 2/3 - Ihre Daten")
{
	TextAdd(self, 10, top, "Eigene Daten eingeben:", BlackFont);
	top += 14+10;
	
	name = AddEditBox("Vor- und Nachname", 0);
	tel = AddEditBox("Telefonnummer", 1);
	email = AddEditBox("E-Mail (optional)", 2);
	versicherung = AddEditBox("KFZ-Versicherung", 0);
	kennzeichen = AddHalfEditBox("KFZ-Kennzeichen", 0);

	warning = TextAdd(self, 10, top, "Geben Sie alle benötigten Felder ein!", RedFont);
	TextSetVisible(warning, 0);

	//Zurueck
	ButtonAdd(self, "Buttons/back", 10, sheight-10-35, IhreDaten::OnButton, 0);

	//Vor
	ButtonAdd(self, "Buttons/next", swidth-10-145, sheight-10-35, IhreDaten::OnButton, 1);

}


int IhreDaten::OnButton(int id){
	if(id == 0)
	{
		IhreDatenST->hide();
		UnfallgegnerST->show();
	}
	else if(id == 1)
	{
		if(
			strcmp("",IhreDatenST->name->Text()) != 0 
			&& strcmp("",IhreDatenST->tel->Text()) != 0 
			&& strcmp("",IhreDatenST->kennzeichen->Text()) != 0
			&& strcmp("",IhreDatenST->versicherung->Text()) != 0
			)
		{
			IhreDatenST->hide();
			UnfallhergangST->show();
		}
		else{
			TextSetVisible(IhreDatenST->warning, 1);
			Vibrate();
		}
	}
	return id;
}


void IhreDaten::show()
{
	TextSetVisible(warning, 0);
	Screen::show();
}

