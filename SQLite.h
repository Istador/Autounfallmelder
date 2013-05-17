#ifndef __SQLITE_H_INCLUDED__
#define __SQLITE_H_INCLUDED__

#define SQL SQLite::Instance()

class EditBox;
class TextBox;
class Unfall;

#include <Map>

//####################################################################
//####################################################################
//####             SQLite Klassendefinition


class SQLite
{
	public:
		static SQLite* Instance(); //Singleton getter
		void LoadUI();
		void LoadNextUnfall();
		bool DeleteUnfall(Unfall* u);
		void SaveUnfall(Unfall* u);
		void UnfallChangeState(Unfall* u);
		void SaveEditBox(EditBox* ed);
		void SaveTextBox(TextBox* ed);
		void UnfallRefresh();
		static int OnEditDone();
		static int OnTextDone();
		static int OnColumn(char* value, char* name);
		static int OnRow(char* value);
	protected:
		SQLite(); //Konstruktor
	private:
		static SQLite* _instance;
		static bool _loadNextUnfall;
};


//####################################################################
//####################################################################
#endif // __SQLITE_H_INCLUDED__