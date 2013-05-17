#include "Zusammenfassung.h"

#include "DragonFireSDK.h"
#include "Ressources.h"
#include "TouchButton.h"
#include "SQLite.h"
#include "MeineUnfaelle.h"
#include "base64.h"
#include <String>


//####################################################################
//####################################################################
//####             Zusammenfassung Implementation


Zusammenfassung* Zusammenfassung::_instance = 0;


Zusammenfassung* Zusammenfassung::Instance()
{
	if(_instance == 0){
		_instance = new Zusammenfassung;
	}
	return _instance;
}


bool Zusammenfassung::isWaiting(){return waiting;}


int Zusammenfassung::BtnAdd(char* name)
{
	TextAdd(self, 15, top, name, SmallFont);
	int tmp = TextAdd(self, 100, top, "unknown", SmallFont);
	top += 12+5;
	return tmp;
}


Zusammenfassung::Zusammenfassung() : BlueScreen("Zusammenfassung")
{
	TouchAdd(self, 0, top-10, swidth, sheight-top+10, Zusammenfassung::OnTouchArea, 0);
	
	top += 10;
	
	TextAdd(self, 10, top, "Unfallgegner:", Font);
	top += 14+5;
	this->g_name = BtnAdd("Name:");
	this->g_tel = BtnAdd("Telefon:");
	this->g_email = BtnAdd("E-Mail:");
	this->g_kennzeichen = BtnAdd("Kennzeichen:");
	this->g_versicherung = BtnAdd("Versicherung:");

	top += 10;

	TextAdd(self, 10, top, "Ihre Daten:", Font);
	top += 14+5;
	this->u_name = BtnAdd("Name:");
	this->u_tel = BtnAdd("Telefon:");
	this->u_email = BtnAdd("E-Mail:");
	this->u_kennzeichen = BtnAdd("Kennzeichen:");
	this->u_versicherung = BtnAdd("Versicherung:");

	top += 10;

	TextAdd(self, 10, top, "Unfallhergang:", Font);
	top += 14+5;
	this->u_text = TextAdd(self, 15, top, "unknown", SmallFont);

	top += 60;

	TextAdd(self, 10, top, "Notiz:", Font);
	top += 14+5;
	this->u_notiz = TextAdd(self, 15, top, "unknown", SmallFont);

	btn_del = ButtonAdd(self, "Buttons/delete", 10, sheight-10-35, Zusammenfassung::OnButton, 2);
	btn_back = ButtonAdd(self, "Buttons/back", 10, sheight-10-35, Zusammenfassung::OnButton, 0);
	ButtonSetVisible(btn_back,0);
	btn_send = ButtonAdd(self, "Buttons/send", swidth-10-145, sheight-10-35, Zusammenfassung::OnButton, 1);
	state_ok = ViewAdd(self, Img_Ok, swidth-10-ImageGetWidth(Img_Ok), sheight-10-ImageGetHeight(Img_Ok));
	ViewSetVisible(state_ok,0);
	state_wait = ViewAdd(self, Img_Wait, swidth-10-ImageGetWidth(Img_Wait), sheight-10-ImageGetHeight(Img_Wait));
	ViewSetVisible(state_wait,0);
	state_error = ViewAdd(self, Img_Error, swidth-10-ImageGetWidth(Img_Error), sheight-10-ImageGetHeight(Img_Error));
	ViewSetVisible(state_error,0);

}


int Zusammenfassung::OnButton(int id){
	Unfall* u = ZusammenfassungST->unfall;
	
	if(id == 0) //zurueck
	{
		ZusammenfassungST->hide();
		UnfaelleST->show();
	}
	else if(id == 1)//senden
	{
		if(u->ID() != 0)
		{
			ZusammenfassungST->unfall->changeState(1);
			ButtonSetVisible(ZusammenfassungST->btn_send, 0);
			ButtonSetVisible(ZusammenfassungST->btn_del, 0);
			ViewSetVisible(ZusammenfassungST->state_wait, 1);

			char url[9700]; // 45 + 106 + 20+30+40+20+1360+4000+7+4000 = 9628
			char tmp[800];
			strcpy_s(url, "http://blastwave.blackpinguin.de/apptest.php?"); //45
			sprintf_s(tmp, "date=%s&id=%i", u->Date(), u->ID()); //9+20+30
			strcat_s(url, tmp);
			
			//unique Device ID
			int ret = DeviceGetUDID(tmp, 50); //40
			if(ret != 0)
			{
				strcat_s(url, "&udid="); //6
				strcat_s(url, tmp);
			}
			
			//gps-koordinaten
			float lat, lng = 0.0f;
			ret = LocationGet(lat, lng);
			if(ret != 0)
			{
				sprintf_s(tmp, "&lat=%f&lng=%f", lat, lng); //10+10+10
				strcat_s(url, tmp);
			}
			
			//Unfallgegner
			sprintf_s(tmp, "&gname=%s&gtel=%s&gemail=%s&gkennz=%s&gvers=%s", u->Gegner()->name, u->Gegner()->tel, u->Gegner()->email, u->Gegner()->kennzeichen, u->Gegner()->versicherung);  
			strcat_s(url, tmp); //36 + 5*136 = 716
			
			//Ihre Daten
			sprintf_s(tmp, "&uname=%s&utel=%s&uemail=%s&ukennz=%s&uvers=%s", u->User()->name, u->User()->tel, u->User()->email, u->User()->kennzeichen, u->User()->versicherung);  
			strcat_s(url, tmp); //36 + 5*136 = 716
			
			//Unfallhergang
			strcat_s(url, "&hergang="); //9 + 4000
			strcat_s(url, u->Hergang());

			//Notiz
			strcat_s(url, "&notiz="); //7 + 4000
			strcat_s(url, u->Hergang());

			//url abspeichern
			/*
			FileDelete("url.txt");
			int fh = FileCreate("url.txt");
			FileWrite(fh, url, strlen(url));
			*/

			ZusammenfassungST->waiting = true;

			//abschicken
			NetSend(url, Zusammenfassung::OnResponse);
		}
	}
	else if(id == 2) //loeschen
	{
		if(u->ID() != 0)
		{
			SQL->DeleteUnfall(u);
			SQL->UnfallRefresh();
			ZusammenfassungST->hide();
			UnfaelleST->show();
		}
	}
	
	return id;
}


int Zusammenfassung::OnResponse(int event, char *response, int length)
{
	ZusammenfassungST->waiting = false;
	//printf("[%s]",response);
	if(response[0] == '0')
	{
		ViewSetVisible(ZusammenfassungST->state_wait, 0);
		ViewSetVisible(ZusammenfassungST->state_error, 1);
		ButtonSetVisible(ZusammenfassungST->btn_back, 1);
	}
	else if(response[0] == '1')
	{
		ViewSetVisible(ZusammenfassungST->state_wait, 0);
		ViewSetVisible(ZusammenfassungST->state_ok, 1);
		ButtonSetVisible(ZusammenfassungST->btn_back, 1);
		ZusammenfassungST->unfall->changeState(2);
		SQL->UnfallRefresh();
	}

	return event;
}

char b64_buffer[4000];
char* from64(char* text){
	strcpy_s(b64_buffer, base64_decode(text).c_str());
	return b64_buffer;
}

void setBase64Text(int tx, char* text){
	TextSetText(tx,  from64(text));
}


void Zusammenfassung::LoadUnfall(Unfall* u)
{
	this->unfall = u;
	
	setBase64Text(this->g_name,  u->Gegner()->name);
	setBase64Text(this->g_tel,   u->Gegner()->tel);
	setBase64Text(this->g_email, u->Gegner()->email);
	setBase64Text(this->g_kennzeichen,  u->Gegner()->kennzeichen);
	setBase64Text(this->g_versicherung, u->Gegner()->versicherung);

	setBase64Text(this->u_name,  u->User()->name);
	setBase64Text(this->u_tel,   u->User()->tel);
	setBase64Text(this->u_email, u->User()->email);
	setBase64Text(this->u_kennzeichen,  u->User()->kennzeichen);
	setBase64Text(this->u_versicherung, u->User()->versicherung);

	setBase64Text(this->u_text,  u->Hergang());
	setBase64Text(this->u_notiz,  u->Notiz());

	char buffer[40]; //10+20=30
	sprintf_s(buffer, "Unfall am %s", u->Date());
	ZusammenfassungST->SetTitle(buffer);

	waiting = false;

	if(u->State() == 0){
		ButtonSetVisible(ZusammenfassungST->btn_send, 1);
		ButtonSetVisible(ZusammenfassungST->btn_del, 1);
		ButtonSetVisible(ZusammenfassungST->btn_back, 0);
		ViewSetVisible(ZusammenfassungST->state_ok, 0);
		ViewSetVisible(ZusammenfassungST->state_wait, 0);
		ViewSetVisible(ZusammenfassungST->state_error, 0);
	}
	else if(u->State() == 1){
		ButtonSetVisible(ZusammenfassungST->btn_send, 1);
		ButtonSetVisible(ZusammenfassungST->btn_del, 0);
		ButtonSetVisible(ZusammenfassungST->btn_back, 1);
		ViewSetVisible(ZusammenfassungST->state_ok, 0);
		ViewSetVisible(ZusammenfassungST->state_wait, 0);
		ViewSetVisible(ZusammenfassungST->state_error, 0);
	}
	else if(u->State() == 2){
		ButtonSetVisible(ZusammenfassungST->btn_send, 0);
		ButtonSetVisible(ZusammenfassungST->btn_del, 0);
		ButtonSetVisible(ZusammenfassungST->btn_back, 1);
		ViewSetVisible(ZusammenfassungST->state_ok, 1);
		ViewSetVisible(ZusammenfassungST->state_wait, 0);
		ViewSetVisible(ZusammenfassungST->state_error, 0);
	}
}
