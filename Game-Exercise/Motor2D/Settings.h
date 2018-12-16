#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;
class GUI_Button;
class Gui_Slider;
class Gui_Label;

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

	//bool MouseIn(GUI* button);
	void Interact(GUI* g);

private:
	
	bool first_update = true;
	bool change_music = false;
	bool close = false;

	GUI* background = nullptr;
	GUI* go_back = nullptr;
	GUI* music = nullptr;
	Gui_Slider* slider = nullptr;
	GUI_Button* button = nullptr;
	GUI_Button* btn_spanish = nullptr;
	GUI_Button* btn_english = nullptr;
	Gui_Label* text_language = nullptr;
	Gui_Label* language = nullptr;
	Gui_Label* music_volume = nullptr;
	GUI_Button* btn_language = nullptr;

public:
	int mouse_x, mouse_y;

};

#endif // Settings