#ifndef __BLUESCREEN_H_INCLUDED__
#define __BLUESCREEN_H_INCLUDED__

#include "Screen.h"


//####################################################################
//####################################################################
//####             BlueScreen Klassendefinition


class BlueScreen : public Screen {
	public:
		static int HomeButton(int id);
		static int OnTouchArea(int id, int event, int x, int y);
		void SetTitle(char* title);
	protected:
		BlueScreen(char* title);
		int title;
};


//####################################################################
//####################################################################
#endif // __BLUESCREEN_H_INCLUDED__
