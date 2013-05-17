#include "BlueScreen.h"

#include "DragonFireSDK.h"
#include "Ressources.h"
#include "Unfallgegner.h"
#include "IhreDaten.h"
#include "Unfallhergang.h"
#include "Saved.h"
#include "MeineUnfaelle.h"
#include "Zusammenfassung.h"
#include "Kontakt.h"
#include "MainScreen.h"

//####################################################################
//####################################################################
//####             BlueScreen Implementation


void BlueScreen::SetTitle(char* title)
{
	TextSetText(this->title, title);
}


BlueScreen::BlueScreen(char* title) : Screen()
{
	//Hintergrundbild
	ViewAdd(self, Img_BlueBG, 0, 0); 
	swidth = ImageGetWidth(Img_BlueBG);
	sheight = ImageGetHeight(Img_BlueBG);
	
	int tempoverlay = ContainerAdd(overlay, 0, 0);
	overlay = ContainerAdd(tempoverlay, 0, 0);

	//Leiste Oben (TouchArea verhindert klicken auf darunterliegende objekte)
	ViewAdd(tempoverlay, Img_Top, 0, 0, BlueScreen::OnTouchArea, 0);
	top = ImageGetHeight(Img_Top)+10;
		
	//Home Button
	ButtonAdd(tempoverlay, "Buttons/home", 0, 0, BlueScreen::HomeButton, 1);

	//Ueberschrift
	this->title = TextAdd(tempoverlay, 80, 12, title, WhiteFont);
}


int BlueScreen::HomeButton(int id)
{
	UnfallgegnerST->hide();
	IhreDatenST->hide();
	UnfallhergangST->hide();
	SavedST->hide();
	UnfaelleST->hide();
	ZusammenfassungST->hide();
	KontaktST->hide();
	MainST->show();
	return id;
}


int BlueScreen::OnTouchArea(int id, int event, int x, int y)
{
	return id;
}