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
	SDL_Texture* texture = nullptr;
	bool delete_ui = false;

public:
	GUI(int x, int y);
	virtual ~GUI();

	virtual void Update();
	virtual void Draw(SDL_Texture* sprites);
};

#endif 