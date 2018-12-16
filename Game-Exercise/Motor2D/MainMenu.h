#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;
class GUI_Button;
class Gui_Label;

class MainMenu : public j1Module
{
public:

	MainMenu();

	// Destructor
	virtual ~MainMenu();

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

	void Interact(GUI* g);

	
private:
	SDL_Rect bck = { 0,0,1024,768 };
	SDL_Rect bck2 = { 1625,299,330,421 };
	SDL_Rect set = { 1067,54,37,37 };
	bool is_faded = false;
	bool close = false;

	GUI* background = nullptr;
	GUI* background2 = nullptr;
	GUI* adjust = nullptr;
	GUI* cross = nullptr;
	GUI* btn_settings = nullptr;
	GUI* btn_exit = nullptr;

	GUI_Button* btn_play = nullptr;
	GUI_Button* btn_continue = nullptr;
	GUI_Button* btn_credits = nullptr;
	GUI_Button* btn_spanish = nullptr;
	GUI_Button* btn_language = nullptr;

	Gui_Label* text_language = nullptr;
	Gui_Label* text_play = nullptr;
	Gui_Label* text_continue = nullptr;
	Gui_Label* text_credits = nullptr;

public:
	int mouse_x, mouse_y;
	bool first_update = true;
};

#endif // __MAINMENU_H__