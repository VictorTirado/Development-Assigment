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
	GUI* full_heart = nullptr;
	SDL_Rect heart_rect = { 1605, 1037, 26, 22 };

public:
	int map_number = 1;
	bool collision_debug = false;
	bool is_god = false;
};

#endif // __j1SCENE_H__