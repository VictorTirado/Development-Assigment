#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2DynArray.h"

#define CURSOR_WIDTH 2

enum UI
{
	IMAGE,
	LABEL,
	BUTTON,
	NON,
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
	GUI* AddImage(int x, int y, SDL_Rect rect);
	GUI* AddLabel(int x, int y, p2SString text);
	GUI* AddButton(int x, int y, SDL_Rect normal, SDL_Rect mouse_in, SDL_Rect clicked);
	void MoveGui(GUI* type, float dt);


	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	p2DynArray<GUI*> ui_list;
};

#endif // __j1GUI_H__