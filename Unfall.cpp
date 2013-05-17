#include "Unfall.h"

#include <String>
#include "SQLite.h"

//####################################################################
//####################################################################
//####             Unfall Implementation


std::map<int,Unfall> Unfall::UnfallMap;


Unfall::Unfall(){id = 0;}


Unfall::Unfall(int id, char* date){ this->id = id; strcpy_s(this->date, date);}


Unfall::Unfall(int id, int state, char* date, struct Person gegner, struct Person user, char* hergang, char* notiz)
{
	this->id = id;
	this->state = state;
	strcpy_s(this->date, date);
	this->gegner = gegner;
	this->user = user;
	strcpy_s(this->hergang, hergang);
	strcpy_s(this->notiz, notiz);
}


void Unfall::changeState(int state)
{
	this->state = state;
	SQLite::Instance()->UnfallChangeState(this);
}


int Unfall::ID(){ return id; }
int Unfall::State(){ return state; }
char* Unfall::Date(){ return date; }
struct Person* Unfall::Gegner(){ return &gegner; }
struct Person* Unfall::User(){ return &user; }
char* Unfall::Hergang(){ return hergang; }
char* Unfall::Notiz(){ return notiz; }



