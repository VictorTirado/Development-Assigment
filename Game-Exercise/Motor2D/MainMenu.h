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

	bool MouseIn(GUI* button);
	void Interact(GUI* g);
private:
	bool is_faded = false;
	bool change_map = false;
	bool change_music = false;
	bool delete_kunais = false;
	bool close = false;

	GUI* background = nullptr;
	GUI* background2 = nullptr;
	GUI* adjust;

	GUI* cross = nullptr;
	GUI_Button* btn_play = nullptr;
	GUI* btn_continue = nullptr;
	GUI* btn_settings = nullptr;
	GUI* btn_credits = nullptr;
	GUI* btn_exit = nullptr;
	GUI* kunai_left = nullptr;
	GUI* kunai_right = nullptr;

	Gui_Label* text_play = nullptr;

	
	

public:
	int mouse_x, mouse_y;
	
};

#endif // __MAINMENU_H__