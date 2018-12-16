#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "Entity_Book.h"
#include "j1FadeToBlack.h"
#include "MainMenu.h"
#include "j1Entitites.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Fonts.h"
#include "j1Languages.h"
#include "Brofiler\Brofiler.h"
#include "Entity_Player.h"
#include "j1Scene.h"
#include "Credits.h"

#include "GUI_Button.h"
#include "GUI_Slider.h"

Credits::Credits() : j1Module()
{
	name.create("Credits");
}

// Destructor
Credits::~Credits()
{}

// Called before render is available
bool Credits::Awake()
{
	LOG("Loading Credits");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Credits::Start()
{
	pugi::xml_document data;
	pugi::xml_node root;
	pugi::xml_parse_result result = data.load_file("save_game.xml");
	root = data.child("game_state");

	//MENU _UI

	SDL_Rect bck = { 0,0,1024,768 };
	background = App->gui->AddImage(0, 0, &bck, nullptr, this, nullptr);
	go_back = App->gui->AddButton(50, 50, { 1129,95,48,51 }, { 1128,160,48,51 }, { 1128,160,48,51 }, this, nullptr);
	
	btn_web = (GUI_Button*)App->gui->AddButton(300, 200, { 1068,297,55,55 }, { 1069,362,55,55 }, { 1069,421,55,55 }, this, nullptr);

	return true;
}

bool Credits::PreUpdate()
{
	BROFILER_CATEGORY("CreditsPreUpdate", Profiler::Color::BlanchedAlmond);
	return true;
}

// Called each loop iteration
bool Credits::Update(float dt)
{
	BROFILER_CATEGORY("CreditsUpdate", Profiler::Color::MediumOrchid);
	//DEBUG KEYS


	App->input->GetMousePosition(mouse_x, mouse_y);
	return true;
}

// Called each loop iteration
bool Credits::PostUpdate()
{
	BROFILER_CATEGORY("CreditsPostUpdate", Profiler::Color::Navy);
	bool ret = true;

	if (close == true)
		ret = false;

	return ret;
}

// Called before quitting
bool Credits::CleanUp()
{
	LOG("Freeing Credits");

	return true;
}

void Credits::Interact(GUI* g)
{
	if (g == go_back)
	{
		App->fade_to_black->FadeToBlack(this, App->scene, 3.0f);
		App->gui->DestroyAllUi();
		App->main_menu->active = true;
		App->main_menu->Start();

		this->active = false;
	}

	if (g == btn_web)
	{
		ShellExecute(GetActiveWindow(), "open","https://victortirado.github.io/Development-Assigment/", NULL, NULL, SW_SHOWNORMAL);
	}

}