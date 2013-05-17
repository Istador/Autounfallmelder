#ifndef __KONTAKT_H_INCLUDED__
#define __KONTAKT_H_INCLUDED__

#define KontaktST Kontakt::Instance()

#include "BlueScreen.h"


//####################################################################
//####################################################################
//####             Kontakt Klassendefinition


class Kontakt : public BlueScreen
{
	public:
		static Kontakt* Instance(); //Singleton getter
		static int OnButton(int id);
		static int OnTouchArea(int id, int event, int x, int y);
	protected:
		Kontakt(); //Konstruktor
	private:
		static Kontakt* _instance;
};


//####################################################################
//####################################################################
#endif // __KONTAKT_H_INCLUDED__