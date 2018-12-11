#ifndef _GUI_BUTTON_H__ 
#define _GUI_BUTTON_H__

#include "GUI.h"


class GUI_Button : public GUI
{
private:
	SDL_Rect normal;
	SDL_Rect mouse_in;
	SDL_Rect clicked;

public:
	GUI_Button(int x, int y, SDL_Rect rect, SDL_Rect rect2, SDL_Rect rect3, UI type,GUI* parent);
	void setAnimation(int state);

};
#endif //_GUI_BUTTON_H__