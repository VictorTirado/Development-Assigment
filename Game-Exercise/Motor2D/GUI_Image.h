#ifndef _GUI_IMAGE_H__ 
#define _GUI_IMAGE_H__

#include "GUI.h"


class GUI_Image : public GUI
{
private:
	SDL_Rect img_normal;
	Animation anim;

public:
	GUI_Image(int x, int y, SDL_Rect rect, UI type);

};
#endif //_GUI_IMAGE_H__