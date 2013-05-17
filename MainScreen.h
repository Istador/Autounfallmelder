#ifndef __MAINSCREEN_H_INCLUDED__
#define __MAINSCREEN_H_INCLUDED__

#define MainST MainScreen::Instance()

#include "WhiteScreen.h"


//####################################################################
//####################################################################
//####             Main Screen Klassendefinition


class MainScreen : public WhiteScreen
{
	public:
		static MainScreen* Instance(); //Singleton getter
		static int OnButton(int id);
	protected:
		MainScreen(); //Konstruktor
	private:
		static MainScreen* _instance;
};


//####################################################################
//####################################################################
#endif // __MAINSCREEN_H_INCLUDED__