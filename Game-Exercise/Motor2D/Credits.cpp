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
	//MENU _UI

	SDL_Rect bck = { 0,0,1024,768 };
	background = App->gui->AddImage(0, 0, &bck, nullptr, this, nullptr);
	go_back = App->gui->AddButton(50, 50, { 1129,95,48,51 }, { 1128,160,48,51 }, { 1128,160,48,51 }, this, nullptr);

	btn_license = (GUI_Button*)App->gui->AddButton(App->win->width/2 - 150 , 50, { 1316,382,300,77 }, { 1316,299,300,77 }, { 1317,466,300,77 },this,nullptr);
	license_text = (Gui_Label*)App->gui->AddLabel(200, 200, "License", this, btn_license);
	btn_license->SetText(license_text);

	website_text = (Gui_Label*)App->gui->AddLabel(App->win->width / 2 - 200, 200, "Check our website", this, nullptr);

	victor_text = (Gui_Label*)App->gui->AddLabel(50, 380, "Victor's Github", this, nullptr);
	btn_github_victor = (GUI_Button*)App->gui->AddButton(victor_text->position.x , victor_text->position.y + 60, { 1316,382,300,77 }, { 1316,299,300,77 }, { 1317,466,300,77 }, this, victor_text);
	enric_text = (Gui_Label*)App->gui->AddLabel(App->win->width- 350, victor_text->position.y, "Enric's Github", this, victor_text);
	btn_github_enric = (GUI_Button*)App->gui->AddButton(enric_text->position.x , enric_text->position.y + 60, { 1316,382,300,77 }, { 1316,299,300,77 }, { 1317,466,300,77 }, this, enric_text);
	btn_web = (GUI_Button*)App->gui->AddButton(App->win->width / 2 - 150, website_text->position.y +50, { 1316,382,300,77 }, { 1316,299,300,77 }, { 1317,466,300,77 }, this, website_text);
	web_text = (Gui_Label*)App->gui->AddLabel(200, 200, "Website", this, btn_web);
	btn_web->SetText(web_text);
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
	if (g == btn_github_enric)
	{
		ShellExecute(GetActiveWindow(), "open", "https://github.com/PerezEnric", NULL, NULL, SW_SHOWNORMAL);
	}
	if (g == btn_github_victor)
	{
		ShellExecute(GetActiveWindow(), "open", "https://github.com/VictorTirado", NULL, NULL, SW_SHOWNORMAL);
	}
	if (g == btn_license)
	{
		ShellExecute(GetActiveWindow(), "open", "https://github.com/VictorTirado/Development-Assigment/blob/master/LICENSE", NULL, NULL, SW_SHOWNORMAL);
	}

}