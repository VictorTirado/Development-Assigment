#include "j1App.h"
#include "j1Fonts.h"
#include "GUI_Label.h"
#include "j1Textures.h"
#include "p2Log.h"


Gui_Label::Gui_Label(int x, int y, p2SString text, UI type,GUI* parent) : GUI(x, y, parent)
{
	position.x = x;
	position.y = y;
	this->type = type;
	this->text = text;


	int w = 0, h = 0;
	App->font->CalcSize(this->text.GetString(), w, h, App->font->default);
	animation.w = w;
	animation.h = h;
	texture = App->font->Print(text.GetString(), { 0, 0, 0, 255 }, App->font->default);
}
Gui_Label::~Gui_Label()
{
	text.Clear();
	App->tex->UnLoad(texture);
	text = nullptr;
	texture = nullptr;
	delete texture;
}