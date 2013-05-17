#ifndef __UNFALLHERGANG_H_INCLUDED__
#define __UNFALLHERGANG_H_INCLUDED__

#define UnfallhergangST Unfallhergang::Instance()

#include "BlueScreen.h"
#include "TextBox.h"

//####################################################################
//####################################################################
//####             Unfallhergang Klassendefinition


class Unfallhergang : public BlueScreen
{
	public:
		static Unfallhergang* Instance(); //Singleton getter
		TextBox* text;
		TextBox* notiz;
		int warning;
		static int OnButton(int id);
		void show();
	protected:
		Unfallhergang(); //Konstruktor
	private:
		static Unfallhergang* _instance;
};


//####################################################################
//####################################################################
#endif // __UNFALLHERGANG_H_INCLUDED__