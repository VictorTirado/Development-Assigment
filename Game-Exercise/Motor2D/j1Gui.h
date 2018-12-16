#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Defs.h"
#include "p2DynArray.h"

#define CURSOR_WIDTH 2

enum UI
{
	IMAGE,
	LABEL,
	BUTTON,
	SLIDER,
	NON
};
// TODO 1: Create your structure of classes
struct SDL_Texture;
struct SDL_Rect;
class p2SString;
class GUI;
// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	GUI* AddImage(int x, int y, SDL_Rect* rect, Animation* anim, j1Module* callback,GUI* parent);
	GUI* AddLabel(int x, int y, p2SString text, j1Module* callback, GUI* parent);
	GUI* AddSlider(int x, int y, j1Module* callback, GUI* parent);
	GUI* AddButton(int x, int y, SDL_Rect normal, SDL_Rect mouse_in, SDL_Rect clicked,j1Module* callback,GUI* parent);


	void DestroyAllUi();
	void DestroyUIElement(GUI &element);
	void DebugDraw();


	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	p2SString background_heart_file_name = nullptr;
	SDL_Texture* background_heart = nullptr;

public:
	p2DynArray<GUI*> ui_list;
	Animation shuriken;
	bool debug = false;
};

#endif // __j1GUI_H__