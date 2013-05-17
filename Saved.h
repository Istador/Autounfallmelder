#ifndef __SAVED_H_INCLUDED__
#define __SAVED_H_INCLUDED__

#define SavedST Saved::Instance()

#include "BlueScreen.h"


//####################################################################
//####################################################################
//####             Saved Klassendefinition


class Saved : public BlueScreen
{
	public:
		static Saved* Instance(); //Singleton getter
		static int OnButton(int id);
		static int OnTouchArea(int id, int event, int x, int y);
	protected:
		Saved(); //Konstruktor
	private:
		static Saved* _instance;
};


//####################################################################
//####################################################################
#endif // __SAVED_H_INCLUDED__