#ifndef _GUI_BUTTON_H__ 
#define _GUI_BUTTON_H__

#include "GUI.h"
#include "GUI_Label.h"


class GUI_Button : public GUI
{
private:
	SDL_Rect normal;
	SDL_Rect mouse_in;
	SDL_Rect clicked;
	Gui_Label* text = nullptr;

public:
	GUI_Button(int x, int y, SDL_Rect rect, SDL_Rect rect2, SDL_Rect rect3, UI type,GUI* parent);
	~GUI_Button();
	void setAnimation(int state);
	void SetText(Gui_Label* text);
};
#endif //_GUI_BUTTON_H__