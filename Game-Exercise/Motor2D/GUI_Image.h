#ifndef _GUI_IMAGE_H__ 
#define _GUI_IMAGE_H__

#include "GUI.h"
#include "p2Defs.h"


class GUI_Image : public GUI
{
private:
	SDL_Rect img_normal;
	Animation anim;

public:
	GUI_Image(int x, int y, UI type, GUI* parent, Animation* anim , j1Module* callback, SDL_Rect* rect = NULL);

};
#endif //_GUI_IMAGE_H__