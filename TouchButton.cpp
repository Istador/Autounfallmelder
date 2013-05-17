#include "TouchButton.h"

#include "DragonFireSDK.h"
#include "Ressources.h"


//####################################################################
//####################################################################
//####             TouchButton Implementation


void TouchButton::init(int cntn, int left, int top, char* label, int (*click)(int id), int (*outertouch)(int id, int event, int x, int y), int id, int rows)
{
	this->id = id;
	this->click = click;
	this->outertouch = outertouch;
	this->touch_state = 0;
	this->rows = rows--;

	self = ContainerAdd(cntn, left, top);
	this->left = left;
	this->top = top;

	this->image_up = ContainerAdd(self, 0, 0);
	this->image_down = ContainerAdd(self, 0, 0);
	int tmptop = 0;

	
	ViewAdd(image_up, Img_TouchBtn_Oben1, 0, tmptop, TouchButton::OnTouchArea, id);
	ViewAdd(image_down, Img_TouchBtn_Oben2, 0, tmptop, TouchButton::OnTouchArea, id);
	
	tmptop += ImageGetHeight(Img_TouchBtn_Oben1);

	int midheight = ImageGetHeight(Img_TouchBtn_Mitte1);

	for( ; rows>0 ; rows-- )
	{
		ViewAdd(image_up, Img_TouchBtn_Mitte1, 0, tmptop, TouchButton::OnTouchArea, id);
		ViewAdd(image_down, Img_TouchBtn_Mitte2, 0, tmptop, TouchButton::OnTouchArea, id);
		tmptop += midheight-2;
	}
		
	ViewAdd(image_up, Img_TouchBtn_Unten1, 0, tmptop, TouchButton::OnTouchArea, id);
	ViewAdd(image_down, Img_TouchBtn_Unten2, 0, tmptop, TouchButton::OnTouchArea, id);
	tmptop += ImageGetHeight(Img_TouchBtn_Unten1);

	ContainerSetVisible(image_down, 0);
	
	this->width = ImageGetWidth(Img_TouchBtn_Oben1);
	this->height = tmptop;

	overlay = ContainerAdd(self, 0, 0);
	TextAdd(overlay, 6, 6, label, BlackFont);

	TBMap[id] = *this;
}


TouchButton::TouchButton(int cntn, int left, int top, char* label, int (*click)(int id), int (*outertouch)(int id, int event, int x, int y), int id, int rows)
{
	init(cntn, left, top, label, click, outertouch, id, rows);
}


TouchButton::TouchButton(int cntn, int left, int top, char* label, int (*click)(int id), int (*outertouch)(int id, int event, int x, int y), int id)
{
	init(cntn, left, top, label, click, outertouch, id, 1);
}


int TouchButton::OnTouchArea(int id, int event, int x, int y)
{
	//printf("[TB:OnTouchArea %i]", id);
	std::map<int, TouchButton>::iterator it = TBMap.find(id);
	if( it != TBMap.end() ) // wenn id existiert
	{
		(&(it->second))->OnTouchButton(id, event, x, y);
		(&(it->second))->outertouch(id, event, x, y);
	}
	return id;
}


int TouchButton::OnTouchButton(int id, int event, int x, int y)
{
	//printf("[TB:OnTouchButton %i, %i > %i]", this->id, touch_state, event);
	if(event == 1) //Maustaste gedrueckt
	{
		touch_state = 1;
		touch_sx = x;
		touch_sy = y;
		ContainerSetVisible(image_down, 1);
		ContainerSetVisible(image_up, 0);
	}
	else if(event == 2) //gedrueckte Maustaste ziehen
	{
		//wenn mehr als 2 pixel bewegt
		if(    touch_sx - x > 2 || touch_sx - y < -2
			|| touch_sy - y > 2 || touch_sy - y < -2
		) //betrachte nicht mehr als gewolltes druecken
		{
			touch_state = 2;
			//ContainerSetVisible(image_up, 1);
			//ContainerSetVisible(image_down, 0);
		}
	}
	else if(event == 3) //gedrueckte Maustaste loslassen
	{
		if(touch_state == 1) //wenn gedrueckte Maustaste nicht bewegt wurde
		{
			click(this->ID());
		}
		this->touch_state = 0;
		ContainerSetVisible(image_up, 1);
		ContainerSetVisible(image_down, 0);
	}
	return id;
}


void TouchButton::HakenAdd()
{
	ViewAdd(this->overlay, Img_Haken, this->width-ImageGetWidth(Img_Haken), 0);
}


int TouchButton::ID(){return id;}
int TouchButton::Left(){return left;}
int TouchButton::Top(){return top;}
int TouchButton::Width(){return width;}
int TouchButton::Height(){return height;}
TouchButton::TouchButton(){}
std::map<int,TouchButton> TouchButton::TBMap;