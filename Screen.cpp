#include "Screen.h"

#include "DragonFireSDK.h"
#include "SQLite.h"
#include "Ressources.h"

//####################################################################
//####################################################################
//####             Screen Implementation


std::map<int,EditBox> Screen::EditMap;


std::map<int,TextBox> Screen::TextMap;


void Screen::hide(){ ContainerSetVisible(maincontainer, 0); } //Screen ausblenden


void Screen::show(){ ContainerSetVisible(maincontainer, 1); } //Screen einblenden


void Screen::view(){ show(); } //Screen einblenden


Screen::Screen() //Konstruktor
{
	maincontainer = ContainerAdd(0,0,0);
	self = ContainerAdd(maincontainer, 0, 0);
	overlay = ContainerAdd(maincontainer, 0, 0);
	this->hide();
}


EditBox* Screen::AddEditBox(char* label, int keyboard)
{
	EditBox eb = EditBox(self, 10, top, label, keyboard);
	top += eb.Height() + 10;
	EditMap[eb.ID()] = eb;
	return &(EditMap[eb.ID()]);
}


EditBox* Screen::AddHalfEditBox(char* label, int keyboard)
{
	EditBox eb = EditBox(self, 10, top, label, keyboard, Img_EditFeldHalf);
	top += eb.Height() + 10;
	EditMap[eb.ID()] = eb;
	return &(EditMap[eb.ID()]);
}


TextBox* Screen::AddTextBox(int rows)
{
	TextBox tb = TextBox(self, 10, top, rows);
	top += tb.Height() + 10;
	TextMap[tb.ID()] = tb;
	return &(TextMap[tb.ID()]);
}