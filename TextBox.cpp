#include "TextBox.h"

#include "DragonFireSDK.h"
#include "Ressources.h"
#include <algorithm>
#include "base64.h"

//####################################################################
//####################################################################
//####             TextBox Implementation


TextBox::TextBox(){}


TextBox::TextBox(int container, int left, int top, int rows)
{
	text[0] = '\0';

	int self = ContainerAdd(container, left, top);
	this->left = left;
	this->top = top;
	this->rows = rows--;

	//abgerundete obere haelfte zeichnen
	top = 0;
	ViewAdd(self, Img_TextBox_Oben, 0, top);
	top += ImageGetHeight(Img_TextBox_Oben);

	//bei mehr als 1 Zeilen Mittelteile zeichnen
	for( ; rows>0 ; rows-- )
	{
		ViewAdd(self, Img_TextBox_Mitte, 0, top);
		top += ImageGetHeight(Img_TextBox_Mitte);
	}

	//abgerundete untere haelfte zeichnen
	ViewAdd(self, Img_TextBox_Unten, 0, top);
	top += ImageGetHeight(Img_TextBox_Unten);

	this->width = ImageGetWidth(Img_TextBox_Mitte); 
	this->height = top; 
	this->id = NoteAdd(self, 6, 3, width-6, height-6);
}

int TextBox::ID(){return id;}


int TextBox::Left(){return left;}


int TextBox::Top(){return top;}


int TextBox::Width(){return width;}


int TextBox::Height(){return height;}


int TextBox::Rows(){return rows;}


char* TextBox::Text()
{
	NoteGetText(id, text);
	strcpy_s(text, base64_encode(reinterpret_cast<const unsigned char*>(text), strlen(text)).c_str());
	return text;
}


void TextBox::SetText(char* text){
	strcpy_s(this->text, base64_decode(text).c_str());
	NoteSetText(id, this->text);
}

