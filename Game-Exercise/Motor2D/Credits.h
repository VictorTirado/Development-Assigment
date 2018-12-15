#ifndef __CREDITS_H__
#define __CREDITS_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;
class GUI_Button;
class Gui_Slider;
class Gui_Label;

class Credits :public j1Module
{
public:
	Credits();
	~Credits();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//bool MouseIn(GUI* button);
	void Interact(GUI* g);

private:
	bool is_faded = false;
	bool first_update = true;
	bool change_map = false;
	bool change_music = false;
	bool close = false;

	GUI* background = nullptr;
	GUI* go_back = nullptr;

	GUI_Button* button;

	Gui_Label* text_language = nullptr;


public:
	int mouse_x, mouse_y;
};
#endif // !__CREDITS_H__
