#include "j1App.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "Settings.h"
#include "GUI_Slider.h"
#include "GUI_button.h"
#include "p2Log.h"


Gui_Slider::Gui_Slider(int x, int y, j1Module* callback, UI type, GUI* parent) : GUI(x, y,callback, parent)
{
	position.x = x;
	position.y = y;
	this->type = type;
	this->parent = parent;
	bar = { 1056,481,243,62 };

	animation = bar;
}
void Gui_Slider::SetNumStart(int num, GUI_Button * button)
{
	this->slider_btn = button;
	num = num * 243 / 100;
	this->slider_btn->position.x = position.x ;
	this->slider_btn->position.y = position.y + 2 /*+ animation.h - num - slider_btn->animation.h*/;
}

void Gui_Slider::MoveButton(GUI_Button* button)
{
	LOG("X: %d, Y:%d", slider_btn->position.x, slider_btn->position.y);
	if (slider_btn->position.x >= (this->animation.w + this->position.x - button->animation.w)) {
		slider_btn->position.x = animation.w + position.x - button->animation.w - 1;
	}
	/*if (slider_btn->position.y <= 300)
		slider_btn->position.y = 301;*/
	this->slider_btn = button;
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT /*&& App->settings->MouseIn(button) == true*/)
	{

		if (slider_btn->position.x < (this->animation.w + this->position.x - button->animation.w))
		{
			LOG("PATATTA");
			this->slider_btn->position.x = App->settings->mouse_x - slider_btn->animation.h / 2 ;
			this->slider_btn->position.y = position.y - 1;
		}
	}
}