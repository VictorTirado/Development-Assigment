#ifndef __GUI_H__
#define __GUI_H__

#include "p2Point.h"
#include "Animation.h"
#include "j1Gui.h"
#include "SDL/include/SDL.h"


struct SDL_Texture;
struct SDL_Rect;
class GUI_Button;

class GUI
{
public:
	UI type = UI::NON;
	iPoint position;
	SDL_Rect animation = { 0,0,0,0 };
	Animation* animation2;
	SDL_Texture* texture = nullptr;
	j1Module* callback = nullptr;
	iPoint screen_position = iPoint(0, 0);
	GUI* parent;
	bool delete_ui = false;
	bool invisible = false;

public:
	GUI(int x, int y,j1Module* callback,GUI* parent);
	virtual ~GUI();

	virtual void Update();
	virtual void Draw(SDL_Texture* sprites);
	virtual bool MouseIn(GUI* element);
public:
	int mouse_x, mouse_y;
};

#endif 