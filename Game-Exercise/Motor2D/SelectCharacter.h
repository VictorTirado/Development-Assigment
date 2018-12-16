#ifndef __CHARACTERS_H__
#define __CHARACTERS_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;
class GUI_Button;
class Gui_Slider;
class Gui_Label;

struct Stats
{
	Gui_Label* name;
	Gui_Label* lifes;
	Gui_Label* jump;
};

enum Player_Type
{
	NO_SELECTED,
	SASUKE,
	GAARA,
	NARUTO

};
class Characters : public j1Module
{
public:

	Characters();

	// Destructor
	virtual ~Characters();

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
	bool ShowStats(GUI* g);
	void StartGame();


private:
	bool is_faded = false;
	bool change_map = false;
	bool start_game = false;
	bool show_stats = true;
	bool close = false;
	

	GUI_Button* btn_play = nullptr;
	Gui_Label* text_play = nullptr;

	GUI* background = nullptr;
	GUI* background2 = nullptr;
	GUI* go_back = nullptr;
	GUI* music = nullptr;
	Gui_Slider* slider;
	GUI_Button* sasuke;
	GUI_Button* gaara;
	GUI_Button* anonymous;

	Stats stats_sasuke;



public:
	int mouse_x, mouse_y;
	int type = 0;
};

#endif // __CHARACTERS_H__