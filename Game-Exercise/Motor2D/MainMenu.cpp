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
#include "Brofiler\Brofiler.h"
#include "Entity_Player.h"

#include "GUI_Button.h"

MainMenu::MainMenu() : j1Module()
{
	name.create("MainMenu");
}

// Destructor
MainMenu::~MainMenu()
{}

// Called before render is available
bool MainMenu::Awake()
{
	LOG("Loading main menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool MainMenu::Start()
{
	background = App->gui->AddImage(0, 0, {941,881,362,401});
	btn_play = App->gui->AddButton(10, 10, { 1213,293,209,52 }, { 1431,293,209,52 }, { 1657,293,209,52 });
	return true;
}

// Called each loop iteration
bool MainMenu::PreUpdate()
{
	BROFILER_CATEGORY("ScenePreUpdate", Profiler::Color::BlanchedAlmond);
	return true;
}

// Called each loop iteration
bool MainMenu::Update(float dt)
{
	BROFILER_CATEGORY("SceneUpdate", Profiler::Color::MediumOrchid);
	//DEBUG KEYS
	MouseIn(btn_play);


	App->input->GetMousePosition(mouse_x, mouse_y);
	return true;
}

// Called each loop iteration
bool MainMenu::PostUpdate()
{
	BROFILER_CATEGORY("ScenePostUpdate", Profiler::Color::Navy);
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool MainMenu::CleanUp()
{
	LOG("Freeing main menu");

	return true;
}

void MainMenu::MouseIn(GUI* element)
{

	GUI_Button*  ex2 = (GUI_Button*)element;
	if (element->type == BUTTON) {
		if (mouse_x > element->position.x && mouse_x < element->position.x + element->animation.w && mouse_y > element->position.y && mouse_y < element->position.y + element->animation.h)
		{
			ex2->setAnimation(2);
		}
		if (mouse_x > element->position.x && mouse_x < element->position.x + element->animation.w && mouse_y > element->position.y && mouse_y < element->position.y + element->animation.h)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{

				ex2->setAnimation(3);
			}
		}
		else
		{
			ex2->setAnimation(1);
		}
	}
}