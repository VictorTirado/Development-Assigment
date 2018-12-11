#include "j1App.h"
#include "p2Defs.h"
#include "GUI_Image.h"
#include "p2Log.h"


GUI_Image::GUI_Image(int x, int y, UI type,GUI* parent,Animation* anim, SDL_Rect* rect) : GUI(x, y,parent)
{
	position.x = x;
	position.y = y;
	if(rect != nullptr)
	animation = *rect;

	LOG("UIImage created in x:%i, y:%i", x, y);

	if (anim != nullptr)
	{
		animation2 = anim;
		animation2->speed = 0.15f;
		animation2->loop = true;
	}
}