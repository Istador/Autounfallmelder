#ifndef __TOUCHBUTTON_H_INCLUDED__
#define __TOUCHBUTTON_H_INCLUDED__

#include <Map>

//####################################################################
//####################################################################
//####             TouchButton Klassendefinition


class TouchButton
{
	public:
		TouchButton();
		TouchButton(int cntn, int left, int top, char* label, int (*click)(int id), int (*outertouch)(int id, int event, int x, int y), int id);
		TouchButton(int cntn, int left, int top, char* label, int (*click)(int id), int (*outertouch)(int id, int event, int x, int y), int id, int rows);
		static int OnTouchArea(int id, int event, int x, int y);
		int OnTouchButton(int id, int event, int x, int y);
		void HakenAdd();
		int ID();
		int Left();
		int Top();
		int Width();
		int Height();
		static std::map<int,TouchButton> TBMap;
	private:
		int left, top, width, height, rows;
		int image_up, image_down;
		int self, id, overlay;
		int touch_state, touch_sx, touch_sy;
		int (*outertouch)(int id, int event, int x, int y);
		int (*click)(int id);
		void init(int cntn, int left, int top, char* label, int (*click)(int id), int (*outertouch)(int id, int event, int x, int y), int id, int rows);
};


//####################################################################
//####################################################################
#endif // __TOUCHBUTTON_H_INCLUDED__