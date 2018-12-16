#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;
class GUI_Button;
class GUI_Image;
class Gui_Label;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

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
	bool ChangeMap(int map_number);

	void UpdateScore(int score);
	void Interact(GUI* g);

private:
	bool is_faded = false;
	bool change_map = false;
	bool change_music = false;
public:
	int map_number = 1;
	bool collision_debug = false;
	bool is_god = false;
	bool first_update = true;
	bool paused = false;
	p2SString puntuation;

	GUI* hearts = nullptr;
	GUI* score_text = nullptr;
	GUI* background_menu = nullptr;
	GUI_Button* btn_resume = nullptr;
	GUI_Button* btn_back = nullptr;
	Gui_Label* score2 = nullptr;
	SDL_Rect hearts3 = { 1603, 926, 94, 22 };
	SDL_Rect hearts2 = {1603, 959, 94, 22};
	SDL_Rect hearts1 = { 1603, 988, 94, 22 };
	SDL_Rect hearts0 = { 1603, 1020, 94, 22 };

	GUI* book_caught_ui = nullptr;
	SDL_Rect book_caught_rect = { 1855, 947, 28, 25 };
	SDL_Rect book_not_caught_rect = { 1789, 947, 28, 25 };

	GUI* ui_background = nullptr;
	GUI* player_score_text = nullptr;
	Gui_Label* text_resume = nullptr;
	Gui_Label* text_back = nullptr;


	p2SString score_string;
	GUI* time_text = nullptr;
};

#endif // __j1SCENE_H__