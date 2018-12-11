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
	Gui_Slider(int x, int y, UI type, GUI* parent);
	void SetNumStart(int num, GUI_Button* button);
	void MoveButton(GUI_Button* button);
public:
	p2SString text;
};
#endif //_GUI_SLIDER_H_