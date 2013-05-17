#ifndef __TEXTBOX_H_INCLUDED__
#define __TEXTBOX_H_INCLUDED__


//####################################################################
//####################################################################
//####             TextBox Klassendefinition


class TextBox
{
	public:
		TextBox();
		TextBox(int container, int left, int top, int rows);
		int ID();
		int Left();
		int Top();
		int Width();
		int Height();
		int Rows();
		char* Text();
		void SetText(char* text);
	private:
		int id;
		int left, top, width, height, rows;
		char text[4000];
};


//####################################################################
//####################################################################
#endif // __TEXTBOX_H_INCLUDED__