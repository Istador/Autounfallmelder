#include "SQLite.h"

#include "DragonFireSDK.h"
#include "Ressources.h"
#include "Screen.h"
#include "Unfall.h"
#include "Unfallhergang.h"
#include "Saved.h"
#include "MeineUnfaelle.h"
#include "Zusammenfassung.h"
#include <String>
#include <algorithm>
#include "base64.h"


//####################################################################
//####################################################################
//####             SQLite Implementation


SQLite* SQLite::_instance = 0;


SQLite* SQLite::Instance()
{
	if(_instance == 0){
		_instance = new SQLite;
	}
	return _instance;
}


SQLite::SQLite()
{
	// Create or open the database:
	SQLiteOpen("SQLite.db");

	// Set up the OnColumn callback:
	SQLiteSetOnColumn(OnColumn);
	
	// Set up the OnRow callback:
	SQLiteSetOnRow(OnRow);
	
	// Create tables
	SQLiteExec("create table if not exists `editboxes` (`id` integer primary key, `value` varchar(136));");
	SQLiteExec("create table if not exists `textboxes` (`id` integer primary key, `value` varchar(4000));");
	SQLiteExec("create table if not exists `unfaelle` (`id` integer primary key, `state` integer, `date` datetime, `g_name` varchar(136), `g_tel` varchar(136), `g_email` varchar(136), `g_kennzeichen` varchar(136), `g_versicherung` varchar(136), `u_name` varchar(136), `u_tel` varchar(136), `u_email` varchar(136), `u_kennzeichen` varchar(136), `u_versicherung` varchar(136), `hergang` varchar(4000), `notiz` varchar(4000) );");

	//responsible for EditBox changes
	EditSetOnDone(SQLite::OnEditDone);

	//responsible for TextBox changes
	NoteSetOnDone(SQLite::OnTextDone);

}


bool SQLite::DeleteUnfall(Unfall* u)
{
	if(u->State() == 0){
		char buffer[100]; //39+30
		sprintf_s(buffer, "delete from `unfaelle` where `id` = '%i';",u->ID());
		SQLiteExec(buffer);
		//printf("\n[%s]\n",buffer);
		return true;
	}
	return false;
}

void SQLite::SaveUnfall(Unfall* u)
{
	char buffer[9700];  //198 + ?id,state,date? + 2*(5*(136+4)) + 4 + 2*4000 = >9602
	char tmp[750];     //5*(136+4) = 700

	strcpy_s(buffer, "replace into `unfaelle` (");
	if(u->ID() != 0) strcat_s(buffer, "`id`, ");
	strcat_s(buffer, "`state`, `date`,`g_name`, `g_tel`, `g_email`, `g_kennzeichen`, `g_versicherung`, ");
	strcat_s(buffer, "`u_name`, `u_tel`, `u_email`, `u_kennzeichen`, `u_versicherung`, `hergang`, `notiz`");
	strcat_s(buffer, ") values (");
	if(u->ID() != 0){
		sprintf_s(tmp, "'%i', ",u->ID());
		strcat_s(buffer, tmp);
	}
	sprintf_s(tmp, "'%i', ", u->State());
	strcat_s(buffer, tmp);
	if(u->ID() != 0)
	{
		sprintf_s(tmp, "'%s', ",u->Date());
		strcat_s(buffer, tmp);
	}
	else
	{
		strcat_s(buffer, "datetime('now','localtime'), ");
	}
	sprintf_s(tmp, "'%s', '%s', '%s', '%s', '%s', ", u->Gegner()->name, u->Gegner()->tel, u->Gegner()->email, u->Gegner()->kennzeichen, u->Gegner()->versicherung);
	strcat_s(buffer, tmp);
	sprintf_s(tmp, "'%s', '%s', '%s', '%s', '%s', ", u->User()->name, u->User()->tel, u->User()->email, u->User()->kennzeichen, u->User()->versicherung);
	strcat_s(buffer, tmp);
	strcat_s(buffer, "'");
	strcat_s(buffer, u->Hergang());
	strcat_s(buffer,"', ");

	strcat_s(buffer, "'");
	strcat_s(buffer, u->Notiz());
	strcat_s(buffer,"');");

	SQLiteExec(buffer);
	//printf("\n[%s]\n",buffer);
}

void SQLite::UnfallChangeState(Unfall* u){
	char buffer[100]; // 51+1+30 = 82
	sprintf_s(buffer, "update `unfaelle` set `state` = '%i' where `id` = '%i';", u->State(), u->ID());
	SQLiteExec(buffer);
	//printf("\n[%s]\n",buffer);
}


void SQLite::SaveEditBox(EditBox* eb)
{
	char buffer[250]; // 57+30+136 = 223
	sprintf_s(buffer, "replace into `editboxes` (`id`, `value`) values ('%i', '%s');", eb->ID(), eb->Text());
	SQLiteExec(buffer);
	//printf("\n[%s]\n",buffer);
}


void SQLite::SaveTextBox(TextBox* tb)
{
	char buffer[4100]; //57+30+4000 = 4087
	sprintf_s(buffer, "replace into `textboxes` (`id`, `value`) values ('%i', '%s');", tb->ID(), tb->Text());
	SQLiteExec(buffer);
	//printf("\n[%s]\n",buffer);
}


void SQLite::UnfallRefresh()
{
	UnfaelleST->Refresh();
	SQLiteExec("select 'unfall_', `id`, `state`, strftime('%d.%m.%Y %H:%M:%S',`date`), `g_name`, `g_tel`, `g_email`, `g_kennzeichen`, `g_versicherung`, `u_name`, `u_tel`, `u_email`, `u_kennzeichen`, `u_versicherung`, `hergang`, `notiz` from `unfaelle` order by `date` DESC");
}


void SQLite::LoadUI()
{
	SQLiteExec("select 'editbox', * from `editboxes`");
	SQLiteExec("select 'textbox', * from `textboxes`");
	SQL->UnfallRefresh();
}


bool SQLite::_loadNextUnfall = false;
void SQLite::LoadNextUnfall()
{
	_loadNextUnfall = true;
}


int SQLite::OnEditDone()
{
	std::map<int,EditBox> m = Screen::EditMap;
	for(std::map<int,EditBox>::iterator it = m.begin(); it != m.end(); ++it)
	{
		SQL->SaveEditBox(&(it->second));
	}
	return 0;
}


int SQLite::OnTextDone()
{
	std::map<int,TextBox> m = Screen::TextMap;
	for(std::map<int,TextBox>::iterator it = m.begin(); it != m.end(); ++it)
	{
		SQL->SaveTextBox(&(it->second));
	}
	return 0;
}


int SQLite::OnColumn(char* value, char* name)
{
	//printf("OnColumn(%s,%s);", value, name);
	return 1;
}


int SQLite::OnRow(char* value)
{
	//printf("OnRow(%s);", value);

	char typ[8];
	strncpy_s(typ, value, 7);
	typ[7] = '\0';

	if(strcmp("editbox",typ) == 0)
	{	
		int id = 0;
		char text[136];
		char tmp[200]; //9+30+136 = 175
		
		strcpy_s(tmp, value+8); //string ohne "editbox"
		char* pchr = strchr(tmp, ','); //wo ist das erste komma?
		
		strcpy_s(text, pchr+1); // text = alles nach dem ersten komma
		
		tmp[(pchr-tmp)] = '\0'; // tmp = alles vor dem ersten komma
		id = atoi(tmp); // id = StrToInt(tmp)

		//Setze Text der EditBox
		strcpy_s(text, base64_decode(text).c_str());
		EditSetText(id,text);
	}
	else if(strcmp("textbox",typ) == 0)
	{
		int id = 0;
		char text[4000];
		char tmp[4050]; // 9+30+4000= 4039
		
		strcpy_s(tmp, value+8); //string ohne "textbox"
		char* pchr = strchr(tmp, ','); //wo ist das erste komma?
		
		strcpy_s(text, pchr+1); // text = alles nach dem ersten komma
		
		tmp[(pchr-tmp)] = '\0'; // tmp = alles vor dem ersten komma
		id = atoi(tmp); // id = StrToInt(tmp)

		//Setze Text der TextBox
		strcpy_s(text, base64_decode(text).c_str());
		NoteSetText(id,text);
	}
	else if(strcmp("unfall_",typ) == 0)
	{
		int id = 0;
		int state = 0;
		char date[20];
		char hergang[4000];
		char notiz[4000];

		struct Person gegner;
		struct Person user;

		char tmp[9500]; //10*(136+1)+2*(4000+1) = 9372
		
		strcpy_s(tmp, value+8); //string ohne "unfall_"
		char* pchr1 = strchr(tmp, ','); //wo ist das erste komma?
		
		// 12-45-7890 23:56:89  19 chars
		//strncpy_s(date, pchr1+1, 19); // date = alles nach dem ersten komma
		
		//ID
		char idtmp[30];
		strncpy_s(idtmp, tmp, (pchr1-tmp));
		id = atoi(idtmp); // id = StrToInt(idtmp)

		//State
		char statetmp[10];
		char *pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(statetmp, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;
		state = atoi(statetmp); // state = StrToInt(statetmp)

		//Date
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(date, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;

		//g_Name
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(gegner.name, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;
		
		//g_Tel
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(gegner.tel, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;

		//g_E-Mail
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(gegner.email, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;

		//g_Kennzeichen
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(gegner.kennzeichen, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;

		//g_Versicherung
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(gegner.versicherung, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;
		
		//u_Name
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(user.name, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;
		
		//u_Tel
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(user.tel, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;

		//u_E-Mail
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(user.email, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;

		//u_Kennzeichen
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(user.kennzeichen, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;

		//u_Versicherung
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(user.versicherung, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;
		
		//Hergang
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(hergang, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;

		//Notiz
		pchr2 = strchr(pchr1+1, ','); //wo ist das naechste komma?
		strncpy_s(notiz, pchr1+1, (pchr2-pchr1-1));
		pchr1 = pchr2;

		
		Unfall::UnfallMap[id] = Unfall(id, state, date, gegner, user, hergang, notiz);
		UnfaelleST->AddUnfall(&(Unfall::UnfallMap[id]));
		
		if(Instance()->_loadNextUnfall){
			SQL->_loadNextUnfall = false;
			ZusammenfassungST->LoadUnfall(&(Unfall::UnfallMap[id]));
			UnfallhergangST->hide();
			//ZusammenfassungST->show();
			SavedST->show();
		}
	}

	return 1;
}

