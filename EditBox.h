#ifndef __EDITBOX_H_INCLUDED__
#define __EDITBOX_H_INCLUDED__


//####################################################################
//####################################################################
//####             EditBox Klassendefinition


class EditBox
{
	public:
		EditBox();
		EditBox(int container, int left, int top, char* label, int keyboard, int image);
		EditBox(int container, int left, int top, char* label, int keyboard);
		int ID();
		int Left();
		int Top();
		int Width();
		int Height();
		char* Text();
		void SetText(char* text);
	private:
		int id;
		int left, top, width, height;
		char text[136];
		void eb_init(int container, int left, int top, char* label, int keyboard, int image);
};


//####################################################################
//####################################################################
#endif // __EDITBOX_H_INCLUDED__