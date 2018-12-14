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
#include "GUI_Slider.h"

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
	LOG("Loading GUI");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");
	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	shuriken.PushBack({ 863,1383,40,40 });
	shuriken.PushBack({ 985,1382,40,40 });
	shuriken.PushBack({ 1043,1384,40,40 });
	shuriken.PushBack({ 1106,1383,40,40 });
	shuriken.PushBack({ 1175,1384,40,40 });

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	for (uint i = 0; i < ui_list.Count(); i++)
	{
		if (ui_list[i]->delete_ui == true)
		{
			delete (ui_list[i]);
			ui_list[i] = nullptr;
			ui_list.Pop(ui_list[i]);
		}
	}
	return true;
}

bool j1Gui::Update(float dt)
{
	for (int i = 0; i < ui_list.Count(); i++) {
		if (ui_list.At(i) != nullptr)
			ui_list[i]->Update();
	}
	for (int i = 0; i < ui_list.Count(); i++) {
		if (ui_list.At(i) != nullptr)
			ui_list[i]->Draw(atlas);
	}
	for (int i = 0; i < ui_list.Count(); i++) {
		if (ui_list.At(i) != nullptr && ui_list[i]->type == BUTTON)
			ui_list[i]->MouseIn(ui_list[i]);
	}


	LOG("elements ui: %d", ui_list.Count());
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

GUI* j1Gui::AddImage(int x, int y, SDL_Rect* rect, Animation* anim, j1Module* callback,GUI* parent)
{
	GUI* image = new GUI_Image(x, y, IMAGE, parent,anim, callback,rect);
	ui_list.PushBack(image);
	return image;
}
GUI* j1Gui::AddLabel(int x, int y, p2SString text, j1Module* callback, GUI* parent)
{
	GUI* label = new Gui_Label(x, y, text,callback, LABEL,parent);
	ui_list.PushBack(label);
	return label;
}

GUI* j1Gui::AddButton(int x, int y, SDL_Rect normal, SDL_Rect mouse_in, SDL_Rect clicked, j1Module* callback, GUI* parent)
{
	GUI* button = new GUI_Button(x, y, normal, mouse_in, clicked, callback, BUTTON,parent);
	ui_list.PushBack(button);
	return button;
}

GUI* j1Gui::AddSlider(int x, int y, j1Module* callback, GUI* parent)
{
	GUI* slider = new Gui_Slider(x, y,callback, SLIDER, parent);
	ui_list.PushBack(slider);
	return slider;
}



void j1Gui::DestroyAllUi()
{
	for (uint i = 0; i < ui_list.Count(); i++)
	{
		if (ui_list[i] != nullptr)
		{
			delete ui_list[i];
			ui_list[i] = nullptr;
		}
	}
	ui_list.Clear();
}