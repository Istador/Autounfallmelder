//====================================================
// App.cpp
//====================================================
#include "DragonFireSDK.h"
#include "Ressources.h"
#include "MainScreen.h"
#include "Unfallgegner.h"
#include "IhreDaten.h"
#include "Unfallhergang.h"
#include "MeineUnfaelle.h"
#include "Zusammenfassung.h"
#include "Kontakt.h"
#include "SQLite.h"


/*
  Application initialization code goes here.  Create the items / objects / etc.
  that your app will need while it is running.
*/
void AppMain()
{
	//Bilder und Fonts laden
	load_ressources(); 

	//SQLite Datenbank anlegen/laden
	SQLite::Instance();
	
	//Screens im Speicher erstellen
	MainScreen::Instance();
	Unfallgegner::Instance();
	IhreDaten::Instance();
	Unfallhergang::Instance();
	MeineUnfaelle::Instance();
	Kontakt::Instance();


	//Formulardaten und Unfaelle laden
	SQLite::Instance()->LoadUI();

	//Main Screen anzeigen
	MainScreen::Instance()->show();
}


/*
  Application exit code goes here.  Perform any clean up your app might 
  need to do in the event of interruption by a phone call or the user
  pressing the Home button, or some other event that would cause your
  application to terminate.
*/
void AppExit()
{
	SQLiteClose();
}


// Main loop code goes here.  OnTimer() is called 30 times per second.
long waitstarted = -1;
void OnTimer()
{
	if(Zusammenfassung::Instance()->isWaiting())
	{
		long now = TimerGetMs();
		if(waitstarted == -1)
		{
			waitstarted = now;
		}
		else if(waitstarted + 5000 <= now)
		{
			Zusammenfassung::OnResponse(0, "0", 1);
		}
	}
	else
	{
		waitstarted = -1;
	}
}