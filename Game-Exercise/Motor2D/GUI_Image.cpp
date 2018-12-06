#include "j1App.h"
#include "GUI_Image.h"
#include "p2Log.h"


GUI_Image::GUI_Image(int x, int y, SDL_Rect rect, UI type) : GUI(x, y)
{
	position.x = x;
	position.y = y;
	animation = rect;
	LOG("UIImage created in x:%i, y:%i", x, y);

}