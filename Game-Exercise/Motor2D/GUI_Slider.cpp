#include "j1App.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "Settings.h"
#include "GUI_Slider.h"
#include "GUI_button.h"
#include "j1Audio.h"
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
int Gui_Slider::SetNumStart(int num, GUI_Button * button)
{
	num = (num * 100) / 128;
	this->slider_btn = button;
	int percent = num * 243 / 100;
	if (num <= 0)
	{
		this->slider_btn->position.x = position.x + 1;
		this->slider_btn->position.y = position.y + 3;
	}
	else if (num < 100) {
		this->slider_btn->position.x = position.x + percent - slider_btn->animation.w / 2;
		this->slider_btn->position.y = position.y + 3;
	}
	else if (num >= 100)
	{
		slider_btn->position.x = animation.w + position.x - button->animation.w - 4;
		this->slider_btn->position.y = position.y + 3;
	}
	return num;
}

void Gui_Slider::MoveButton(GUI_Button* button)
{
	this->slider_btn = button;
	LOG("X: %d, Y:%d", slider_btn->position.x, slider_btn->position.y);
	
	
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT /*&& App->settings->MouseIn(button) == true*/)
	{

		if (slider_btn->position.x < (this->animation.w + this->position.x - button->animation.w))
		{
			this->slider_btn->position.x = App->settings->mouse_x - slider_btn->animation.h / 2 ;
			this->slider_btn->position.y = position.y +3;
	
		}
	}
	if (slider_btn->position.x >= (this->animation.w + this->position.x - button->animation.w)) {
		slider_btn->position.x = animation.w + position.x - button->animation.w - 4;
		
	}
	if (slider_btn->position.x <= position.x) {
		slider_btn->position.x = position.x + 1;
	}
}

int Gui_Slider::UpadateNumStart(int num,GUI_Button* button)
{
	if ((slider_btn->position.x + slider_btn->animation.w +5) >= (this->animation.w + this->position.x )) {
		num = 100;
	}
	else if(slider_btn->position.x >= (this->animation.w + this->position.x - button->animation.w)) {
		num = 0;
	}
	else {
		num = ((slider_btn->position.x - position.x) *100 / (position.x + animation.w));
		
	}
	value = (num*128/100);
	LOG(" value music %i", value);
	return value;
}