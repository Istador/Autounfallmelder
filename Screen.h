#ifndef __SCREEN_H_INCLUDED__
#define __SCREEN_H_INCLUDED__

#include "EditBox.h"
#include "TextBox.h"
#include <Map>

//####################################################################
//####################################################################
//####             Screen Klassendefinition

class Screen
{
	public:
		static std::map<int,EditBox> EditMap;
		static std::map<int,TextBox> TextMap;
		void hide(); //Screen ausblenden
		void show(); //Screen einblenden
		void view(); //Screen einblenden
	private:
		int maincontainer; //container in dem self und overlay liegen
	protected:
		Screen(); //Konstruktor
		int self; //ID des Containers innerhalb des SDK
		int overlay; //Container der ueber self liegt
		int top; //unterste freie Y-Koordinate
		int swidth; //Screen Width
		int sheight; //Screen Height

		EditBox* AddEditBox(char* label, int keyboard);
		EditBox* AddHalfEditBox(char* label, int keyboard);
		TextBox* AddTextBox(int rows);
};


//####################################################################
//####################################################################
#endif // __SCREEN_H_INCLUDED__