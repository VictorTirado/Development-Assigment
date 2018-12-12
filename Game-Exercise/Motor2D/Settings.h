#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;
class GUI_Button;
class Gui_Slider;

class Settings : public j1Module
{
public:

	Settings();

	// Destructor
	virtual ~Settings();

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
	GUI* go_back = nullptr;
	GUI* music = nullptr;
	Gui_Slider* slider;
	GUI_Button* button;


	


public:
	int mouse_x, mouse_y;

};

#endif // Settings