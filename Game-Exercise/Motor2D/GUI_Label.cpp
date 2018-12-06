#include "j1App.h"
#include "j1Fonts.h"
#include "GUI_Label.h"
#include "p2Log.h"


Gui_Label::Gui_Label(int x, int y, p2SString text, UI type) : GUI(x, y)
{
	position.x = x;
	position.y = y;
	this->type = type;
	this->text = text;
	texture = App->font->Print(text.GetString(), { 254, 203, 0, 255 }, App->font->default);

	int w = 0, h = 0;
	App->font->CalcSize(this->text.GetString(), w, h, App->font->default);
	animation.w = w;
	animation.h = w;
}