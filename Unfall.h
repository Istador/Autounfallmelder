#ifndef __UNFALL_H_INCLUDED__
#define __UNFALL_H_INCLUDED__

#include <Map>


//####################################################################
//####################################################################
//####             Unfall Klassendefinition

struct Person {
	char name[136];
	char tel[136];
	char email[136];
	char kennzeichen[136];
	char versicherung[136];
};

class Unfall
{
	public:
		static std::map<int,Unfall> UnfallMap;
		Unfall();
		Unfall::Unfall(int id, char* date);
		Unfall(int id, int state, char* date, struct Person gegner, struct Person user, char* hergang, char* notiz);
		int ID();
		int State();
		char* Date();
		struct Person* Gegner();
		struct Person* User();
		char* Hergang();
		char* Notiz();
		void changeState(int state);
	private:
		int id;
		int state;
		char date[20];
		struct Person gegner, user;
		char hergang[4000];
		char notiz[4000];
};


//####################################################################
//####################################################################
#endif // __UNFALL_H_INCLUDED__