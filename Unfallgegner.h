#ifndef __UNFALLGEGNER_H_INCLUDED__
#define __UNFALLGEGNER_H_INCLUDED__

#define UnfallgegnerST Unfallgegner::Instance()

#include "BlueScreen.h"
#include "EditBox.h"


//####################################################################
//####################################################################
//####             Unfallgegner Klassendefinition


class Unfallgegner : public BlueScreen
{
	public:
		static Unfallgegner* Instance(); //Singleton getter
		EditBox* name;
		EditBox* tel;
		EditBox* email;
		EditBox* kennzeichen;
		EditBox* versicherung;
		int warning;
		static int OnButton(int id);
		void show();
	protected:
		Unfallgegner(); //Konstruktor
	private:
		static Unfallgegner* _instance;
};


//####################################################################
//####################################################################
#endif // __UNFALLGEGNER_H_INCLUDED__
