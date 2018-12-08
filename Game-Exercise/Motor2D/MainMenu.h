#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;
class GUI_Button;

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

	void MouseIn(GUI* button);

private:
	bool is_faded = false;
	bool change_map = false;
	bool change_music = false;
	GUI* background = NULL;
	GUI* btn_play = NULL;

public:
	int mouse_x, mouse_y;
};

#endif // __MAINMENU_H__