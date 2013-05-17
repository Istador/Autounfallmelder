#include "WhiteScreen.h"

#include "DragonFireSDK.h"
#include "Ressources.h"


//####################################################################
//####################################################################
//####             WhiteScreen Implementation


WhiteScreen::WhiteScreen() : Screen()
{
	//Hintergrundbild
	ViewAdd(self, Img_WhiteBG, 0, 0); 
	swidth = ImageGetWidth(Img_WhiteBG);
	sheight = ImageGetHeight(Img_WhiteBG);
	top = 0;
}
