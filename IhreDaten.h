#ifndef __IHREDATEN_H_INCLUDED__
#define __IHREDATEN_H_INCLUDED__

#define IhreDatenST IhreDaten::Instance()

#include "BlueScreen.h"

#include "EditBox.h"


//####################################################################
//####################################################################
//####             IhreDaten Klassendefinition


class IhreDaten : public BlueScreen
{
	public:
		static IhreDaten* Instance(); //Singleton getter
		EditBox* name;
		EditBox* tel;
		EditBox* email;
		EditBox* kennzeichen;
		EditBox* versicherung;
		int warning;
		static int OnButton(int id);
		void show();
	protected:
		IhreDaten(); //Konstruktor
	private:
		static IhreDaten* _instance;
};


//####################################################################
//####################################################################
#endif // __IHREDATEN_H_INCLUDED__