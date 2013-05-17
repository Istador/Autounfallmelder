#include "Unfallhergang.h"

#include "DragonFireSDK.h"
#include "Ressources.h"
#include "Unfallgegner.h"
#include "IhreDaten.h"
#include "MeineUnfaelle.h"
#include "Zusammenfassung.h"
#include "Unfall.h"
#include "SQLite.h"
#include <string>
#include <iostream>


//####################################################################
//####################################################################
//####             Unfallhergang Implementation


Unfallhergang* Unfallhergang::_instance = 0;


Unfallhergang* Unfallhergang::Instance()
{
	if(_instance == 0){
		_instance = new Unfallhergang;
	}
	return _instance;
}


Unfallhergang::Unfallhergang() : BlueScreen("Schritt 3/3 - Unfallhergang")
{
	TextAdd(self, 10, top, "Bitte beschreiben Sie in einigen Sätzen den", Font);
	top += 14+10;
	
	TextAdd(self, 10, top, "Unfallhergang:", Font);
	top += 14+10;
	

	text = AddTextBox(7);

	TextAdd(self, 10, top, "Sonstige Notizen:", Font);
	top += 14+10;

	notiz = AddTextBox(4);


	warning = TextAdd(self, 10, top, "Geben Sie alle benötigten Felder ein!", RedFont);
	TextSetVisible(warning, 0);

	//Zurueck
	ButtonAdd(self, "Buttons/back", 10, sheight-10-35, Unfallhergang::OnButton, 0);

	//Speichern
	ButtonAdd(self, "Buttons/save", swidth-10-145, sheight-10-35, Unfallhergang::OnButton, 1);
}


int Unfallhergang::OnButton(int id){
	if(id == 0)
	{
		UnfallhergangST->hide();
		IhreDatenST->show();
	}
	else if(id == 1)
	{
		if(
			strcmp("",UnfallhergangST->text->Text()) != 0 
			) //wenn TextBox nicht leer
		{
			//Unfallgegner
			struct Person gegner;
			strcpy_s(gegner.name, UnfallgegnerST->name->Text());
			strcpy_s(gegner.tel, UnfallgegnerST->tel->Text());
			strcpy_s(gegner.email, UnfallgegnerST->email->Text());
			strcpy_s(gegner.kennzeichen, UnfallgegnerST->kennzeichen->Text());
			strcpy_s(gegner.versicherung, UnfallgegnerST->versicherung->Text());

			//Benutzer der App
			struct Person user;
			strcpy_s(user.name, IhreDatenST->name->Text());
			strcpy_s(user.tel, IhreDatenST->tel->Text());
			strcpy_s(user.email, IhreDatenST->email->Text());
			strcpy_s(user.kennzeichen, IhreDatenST->kennzeichen->Text());
			strcpy_s(user.versicherung, IhreDatenST->versicherung->Text());

			Unfall u = Unfall(0, 0, "", gegner, user, UnfallhergangST->text->Text(), UnfallhergangST->notiz->Text());


			//neuen Unfall anzeigen sobald geladen
			SQL->LoadNextUnfall();

			//neuen Unfall in Datenbank eintragen
			SQL->SaveUnfall(&u);

			//Unfaelle neu abrufen und UI neu aufbauen
			SQL->UnfallRefresh();
			
			//alte Daten loeschen
			UnfallgegnerST->name->SetText("");
			UnfallgegnerST->tel->SetText("");
			UnfallgegnerST->email->SetText("");
			UnfallgegnerST->kennzeichen->SetText("");
			UnfallgegnerST->versicherung->SetText("");
			UnfallhergangST->text->SetText("");
			UnfallhergangST->notiz->SetText("");
			//auch in der Datenbank loeschen
			SQL->OnEditDone();
			SQL->OnTextDone();

		}
		else{ // falls TextBox leer ist
			TextSetVisible(UnfallhergangST->warning, 1); //warnung zeigen
			Vibrate();
		}
	}
	return id;
}


void Unfallhergang::show()
{
	TextSetVisible(warning, 0);
	Screen::show();
}

