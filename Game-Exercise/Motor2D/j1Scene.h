#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;
class GUI_Button;

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

private:
	bool is_faded = false;
	bool change_map = false;
	bool change_music = false;
	

public:
	int map_number = 1;
	bool collision_debug = false;
	bool is_god = false;

	GUI* hearts = nullptr;
	SDL_Rect hearts3 = { 1603, 926, 94, 22 };
	SDL_Rect hearts2 = {1603, 959, 84, 22};
	SDL_Rect hearts1 = { 1603, 988, 84, 22 };
	SDL_Rect hearts0 = { 1603, 1020, 84, 22 };
};

#endif // __j1SCENE_H__