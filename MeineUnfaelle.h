#ifndef __MEINEUNFAELLE_H_INCLUDED__
#define __MEINEUNFAELLE_H_INCLUDED__

#define UnfaelleST MeineUnfaelle::Instance()

#include "BlueScreen.h"
#include "Unfall.h"
#include <Map>


//####################################################################
//####################################################################
//####             MeineUnfaelle Klassendefinition


class MeineUnfaelle : public BlueScreen
{
	public:
		static MeineUnfaelle* Instance(); //Singleton getter
		static int OnButton(int id);
		static int OnTouchArea(int id, int event, int x, int y);
		void Refresh();
		void AddUnfall(Unfall* u);
	protected:
		MeineUnfaelle(); //Konstruktor
	private:
		static MeineUnfaelle* _instance;
		int btncnt; //Container der die Buttons der Unfaelle enthaelt
		int btntop;
};


//####################################################################
//####################################################################
#endif // __MEINEUNFAELLE_H_INCLUDED__