#include "j1App.h"
#include "j1Fonts.h"
#include "GUI_button.h"
#include "p2Log.h"
#include "j1Scene.h"


GUI_Button::GUI_Button(int x, int y, SDL_Rect rect, SDL_Rect rec2, SDL_Rect rect3, UI type) : GUI(x, y)
{

	position.x = x;
	position.y = y;
	this->type = type;
	this->normal = rect;
	this->mouse_in = rec2;
	this->clicked = rect3;
	this->animation = rect;

}

void GUI_Button::setAnimation(int state)
{
	if (state == 1)
	{
		animation = normal;
	}
	else if (state == 2)
	{
		animation = mouse_in;
	}
	else if (state == 3)
	{
		animation = clicked;
	}



}