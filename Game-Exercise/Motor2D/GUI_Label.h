#ifndef _GUI_LABEL_H__ 
#define _GUI_LABEL_H__

#include "GUI.h"


class Gui_Label : public GUI
{
private:
	SDL_Rect img_normal;

public:
	Gui_Label(int x, int y, p2SString text, j1Module* callback, UI type,GUI* parent);
	~Gui_Label();
public:
	p2SString text;
};
#endif //_GUI_LABEL_H_