#include "Ressources.h"

#include "DragonFireSDK.h"


//####################################################################
//####################################################################


int Font, ItalicFont, WhiteFont, RedFont, BlackFont, SmallFont = 0;

int Img_WhiteBG, Img_BlueBG, Img_Logo, Img_Flagge, Img_Top, Img_EditFeld, Img_EditFeldHalf = 0;

int Img_TextBox_Oben, Img_TextBox_Unten, Img_TextBox_Mitte = 0;

int Img_TouchBtn_Oben1, Img_TouchBtn_Unten1, Img_TouchBtn_Mitte1, Img_Haken = 0;
int Img_TouchBtn_Oben2, Img_TouchBtn_Unten2, Img_TouchBtn_Mitte2 = 0;

int Img_Error, Img_Ok, Img_Wait = 0;


void load_images()
{
	Img_WhiteBG = ImageAdd("Images/caro_bg.png"); 
	Img_BlueBG = ImageAdd("Images/caro_bg.png"); 
	Img_Logo = ImageAdd("Images/logo.png"); 
	Img_Flagge = ImageAdd("Images/flagge_felge.png");
	Img_Top = ImageAdd("Images/top_leiste.png");
	Img_EditFeld = ImageAdd("Images/EditFeld.png");
	Img_EditFeldHalf = ImageAdd("Images/EditFeld_half.png");
	
	Img_TouchBtn_Oben1 = ImageAdd("Buttons/TBtn_Oben1.png");
	Img_TouchBtn_Unten1 = ImageAdd("Buttons/TBtn_Unten1.png");
	Img_TouchBtn_Mitte1 = ImageAdd("Buttons/TBtn_Mitte1.png");
	Img_TouchBtn_Oben2 = ImageAdd("Buttons/TBtn_Oben2.png");
	Img_TouchBtn_Unten2 = ImageAdd("Buttons/TBtn_Unten2.png");
	Img_TouchBtn_Mitte2 = ImageAdd("Buttons/TBtn_Mitte2.png");

	Img_TextBox_Oben = Img_TouchBtn_Oben1;
	Img_TextBox_Unten = Img_TouchBtn_Unten1;
	Img_TextBox_Mitte = Img_TouchBtn_Mitte1;

	Img_Haken = ImageAdd("Images/haken.png");
	Img_Error = ImageAdd("Buttons/error.png");
	Img_Ok = ImageAdd("Buttons/abgeschickt.png");
	Img_Wait = ImageAdd("Buttons/wait.png");
}


void load_fonts()
{
	char* font = "Helvetica";
	int bs = 14;
	Font = FontAdd(font, "Regular", bs, 0x000000);
	ItalicFont = FontAdd(font, "BoldItalic", bs+2, 0x000000);
	WhiteFont = FontAdd(font, "Bold", bs+2, 0xffffff);
	RedFont = FontAdd(font, "Bold", bs+2, 0xff0000);
	BlackFont = FontAdd(font, "Bold", bs+2, 0x000000);
	SmallFont = FontAdd(font, "Regular", bs-2, 0x000000);
}


void load_ressources()
{
	load_images();
	load_fonts();
}