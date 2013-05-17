#ifndef __ZUSAMMENFASSUNG_H_INCLUDED__
#define __ZUSAMMENFASSUNG_H_INCLUDED__

#define ZusammenfassungST Zusammenfassung::Instance()

#include "BlueScreen.h"
#include "Unfall.h"
#include <Map>


//####################################################################
//####################################################################
//####             Zusammenfassung Klassendefinition


class Zusammenfassung : public BlueScreen
{
	public:
		static Zusammenfassung* Instance(); //Singleton getter
		static int OnButton(int id);
		static int OnResponse(int event, char *response, int length);
		void LoadUnfall(Unfall* u);
		bool isWaiting();
	protected:
		Zusammenfassung(); //Konstruktor
		int g_name, g_tel, g_email, g_kennzeichen, g_versicherung;
		int u_name, u_tel, u_email, u_kennzeichen, u_versicherung;
		int u_text;
		int u_notiz;
	private:
		static Zusammenfassung* _instance;
		Unfall* unfall; //aktueller Unfall
		int BtnAdd(char* name);
		bool waiting;
		int state_wait, state_ok, state_error, btn_send, btn_back, btn_del;
};


//####################################################################
//####################################################################
#endif // __ZUSAMMENFASSUNG_H_INCLUDED__