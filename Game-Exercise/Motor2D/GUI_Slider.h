#ifndef _GUI_SLIDER_H__ 
#define _GUI_SLIDER_H__

#include "GUI.h"
#include "GUI_button.h"


class Gui_Slider : public GUI
{
private:
	SDL_Rect bar;
	
	SDL_Rect select;
	GUI_Button* slider_btn = nullptr;

public:
	Gui_Slider(int x, int y, j1Module* callback, UI type, GUI* parent);
	int SetNumStart(int num, GUI_Button* button);
	void MoveButton(GUI_Button* button);
	int UpadateNumStart(int num,GUI_Button* button);
public:
	p2SString text;
	uint value;
};
#endif //_GUI_SLIDER_H_