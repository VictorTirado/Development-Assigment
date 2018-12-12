#include "j1App.h"
#include "j1Fonts.h"
#include "GUI_button.h"
#include "GUI_Label.h"
#include "p2Log.h"
#include "j1Scene.h"


GUI_Button::GUI_Button(int x, int y, SDL_Rect rect, SDL_Rect rec2, SDL_Rect rect3, UI type, GUI* parent) : GUI(x, y, parent)
{

	position.x = x;
	position.y = y;
	this->type = type;
	this->normal = rect;
	this->mouse_in = rec2;
	this->clicked = rect3;
	this->animation = normal;

}

void GUI_Button::setAnimation(int state)
{
	if (state == 1)
		animation = normal;

	else if (state == 2)
		animation = mouse_in;

	else if (state == 3)
		animation = clicked;
}

void GUI_Button::SetText(Gui_Label* text)
{
	this->text = text;
	text->position.x = this->position.x + animation.w/2 - text->animation.w/2 ;
	text->position.y = this->position.y + animation.h/2 - text->animation.h/2;
}