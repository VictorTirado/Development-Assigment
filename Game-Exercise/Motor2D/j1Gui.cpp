#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "GUI.h"

#include "GUI_Image.h"
#include "GUI_Label.h"
#include "GUI_button.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

bool j1Gui::Update(float dt)
{
	for (int i = 0; i < ui_list.Count(); i++)
		if (ui_list.At(i) != nullptr)
			ui_list[i]->Update();
	for (int i = 0; i < ui_list.Count(); i++)
		if (ui_list.At(i) != nullptr)
			ui_list[i]->Draw(atlas);

	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

GUI* j1Gui::AddImage(int x, int y, SDL_Rect rect)
{
	GUI* image = new GUI_Image(x, y, rect, IMAGE);
	ui_list.PushBack(image);
	return image;
}
GUI* j1Gui::AddLabel(int x, int y, p2SString text)
{
	GUI* label = new Gui_Label(x, y, text, LABEL);
	ui_list.PushBack(label);
	return label;
}

GUI* j1Gui::AddButton(int x, int y, SDL_Rect normal, SDL_Rect mouse_in, SDL_Rect clicked)
{
	GUI* button = new GUI_Button(x, y, normal, mouse_in, clicked, BUTTON);
	ui_list.PushBack(button);
	return button;
}

void j1Gui::MoveGui(GUI* type, float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		type->position.x -= 200 * dt;

	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		type->position.x += 200 * dt;

	else if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		type->position.y += 200 * dt;

	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		type->position.y -= 200 * dt;
}