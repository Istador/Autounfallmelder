#include "Kontakt.h"

#include "DragonFireSDK.h"
#include "Ressources.h"
#include "TouchButton.h"

//####################################################################
//####################################################################
//####             Kontakt Implementation


Kontakt* Kontakt::_instance = 0;


Kontakt* Kontakt::Instance()
{
	if(_instance == 0){
		_instance = new Kontakt;
	}
	return _instance;
}


Kontakt::Kontakt() : BlueScreen("Kontakt")
{	
	TouchButton tb;


	//Developer Easteregg
	char buffer[90];
	strcpy_s(buffer, "[This application was created by Robin Christopher Ladiges - https://blackpinguin.de/.]");
	printf(buffer);
	TouchAdd(self, swidth-10-20, top, 20, 20, Kontakt::OnTouchArea, -7331);


	ViewAdd(self, Img_Logo, 10, top);
	top += ImageGetHeight(Img_Logo)+10;

	//"Anerkannt, neutral und absolut
	TextAdd(self, 10, top, "\"Anerkannt, neutral und absolut", ItalicFont);
	top += 14+10;
	//versicherungsunabhängig"
	TextAdd(self, 10, top, "versicherungsunabhängig\"", ItalicFont);
	top += 14+10;

	top += 10;

	tb = TouchButton(self, 10, top, "Unfallgutachter Vito GmbH\nRalf Lothar Hess\nKielkamp 78\nD-22761 Hamburg", Kontakt::OnButton, Kontakt::OnTouchArea, -5, 4);
	top += tb.Height()+10;

	//Web
	tb = TouchButton(self, 10, top, "http://www.Auto-Unfall-Gutachter.de/", Kontakt::OnButton, Kontakt::OnTouchArea, -1);
	top += tb.Height()+10;

	//E-Mail
	tb = TouchButton(self, 10, top, "E-Mail: info@Auto-Unfall-Gutachter.de", Kontakt::OnButton, Kontakt::OnTouchArea, -2);
	top += tb.Height()+10;

	//Phone
	tb = TouchButton(self, 10, top, "Telefon: +49 (0) 40 / 8190 17 51", Kontakt::OnButton, Kontakt::OnTouchArea, -3);
	top += tb.Height()+10;

	//Mobil
	tb = TouchButton(self, 10, top, "Mobil: +49 (0) 172 / 4002835", Kontakt::OnButton, Kontakt::OnTouchArea, -4);
	top += tb.Height()+10;

	//Telefax
	TextAdd(self, 16, top+6, "Telefax: +49 (0) 40 / 8190 17 55", BlackFont);
	top += tb.Height()+10;

}


int Kontakt::OnTouchArea(int id, int event, int x, int y)
{
	if( event == 3 && id == -7331) BrowserLaunch("https://blackpinguin.de/");
	return id;
}


int Kontakt::OnButton(int id){
	
	if(id == -1) BrowserLaunch("http://auto-unfall-gutachter.de/");
	else if(id == -2) BrowserLaunch("mailto:info@auto-unfall-gutachter.de");
	else if(id == -3) BrowserLaunch("tel://+494081901751");
	else if(id == -4) BrowserLaunch("tel://+491724002835");
	else if(id == -5)
	{
		//BrowserLaunch("http://maps.google.com/maps?q=53.573117,9.894129+%28Kielkamp 78, 22761 Hamburg%29&iwloc=A");
		BrowserLaunch("http://maps.google.com/maps?q=Autounfallgutachter+Vito+GmbH");
	}
	return id;
}
