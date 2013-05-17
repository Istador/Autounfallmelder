#include "EditBox.h"

#include "DragonFireSDK.h"
#include "Ressources.h"
#include <algorithm>
#include "base64.h"


//####################################################################
//####################################################################
//####             EditBox Implementation


EditBox::EditBox(){}



EditBox::EditBox(int container, int left, int top, char* label, int keyboard)
{
	eb_init(container, left, top, label, keyboard, Img_EditFeld);
}


EditBox::EditBox(int container, int left, int top, char* label, int keyboard, int image)
{
	eb_init(container, left, top, label, keyboard, image);
}


void EditBox::eb_init(int container, int left, int top, char* label, int keyboard, int image)
{
	text[0] = '\0';

	int self = ContainerAdd(container, left, top);
	this->left = left;
	this->top = top;

	ViewAdd(self, image, 0, 0);
	this->width = ImageGetWidth(image); 
	this->height = ImageGetHeight(image); 
	this->id = EditAdd(self, 6, 3, width-6);
	EditSetLabel(this->id, label);
	EditSetKeyboard(this->id, keyboard);
}

int EditBox::ID(){return id;}


int EditBox::Left(){return left;}


int EditBox::Top(){return top;}


int EditBox::Width(){return width;}


int EditBox::Height(){return height;}


char* EditBox::Text()
{
	EditGetText(id, text);
	strcpy_s(text, base64_encode(reinterpret_cast<const unsigned char*>(text), strlen(text)).c_str());
	return text;
}


void EditBox::SetText(char* text){
	strcpy_s(this->text, base64_decode(text).c_str());
	EditSetText(id, this->text);
}

