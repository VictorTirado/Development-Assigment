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
#include "j1Scene.h"

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
	pugi::xml_document data;
	pugi::xml_node root;
	pugi::xml_parse_result result = data.load_file("save_game.xml");
	root = data.child("game_state");

	//MENU _UI
	background = App->gui->AddImage(0, 0, &bck,nullptr);
	btn_play = App->gui->AddButton(App->win->width/2 -150,50, { 1523,919,256,64 } , { 1523,679,256,64 }, { 1523,759,256,64 });
	btn_exit = App->gui->AddButton(App->win->width / 2 - 150, 150, { 1523,919,256,64 }, { 1523,679,256,64 }, { 1523,759,256,64 });
	if(root.child("entities").child("player").child("position").attribute("x").as_int() != NULL)
	btn_settings = App->gui->AddButton(App->win->width / 2 - 150, 250, { 1523,919,256,64 }, { 1523,679,256,64 }, { 1523,759,256,64 });

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
	MouseIn(btn_exit);
	if(btn_settings!=nullptr)
	MouseIn(btn_settings);


	App->input->GetMousePosition(mouse_x, mouse_y);
	return true;
}

// Called each loop iteration
bool MainMenu::PostUpdate()
{
	BROFILER_CATEGORY("ScenePostUpdate", Profiler::Color::Navy);
	bool ret = true;

	if (close == true)
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
			if (delete_kunais == false) {
				kunai_left = App->gui->AddImage(element->position.x - 60, element->position.y + 10,nullptr, &App->gui->shuriken);
				kunai_right = App->gui->AddImage(element->position.x + 270, element->position.y + 10, nullptr, &App->gui->shuriken);
				delete_kunais = true;
			}
		}
		if (mouse_x > element->position.x && mouse_x < element->position.x + element->animation.w && mouse_y > element->position.y && mouse_y < element->position.y + element->animation.h)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{

				ex2->setAnimation(3);

				Interact(element);
			}
		}
		else
		{
			ex2->setAnimation(1);
			if(kunai_left != nullptr || kunai_right != nullptr && delete_kunais == true){
				kunai_left->delete_ui = true;
				kunai_right->delete_ui = true;
				delete_kunais = false;
				
			}
		}
	}
}

void MainMenu::Interact(GUI* g)
{
	if (g->position.y == 50)
	{
		App->fade_to_black->FadeToBlack(this,App->scene, 3.0f);
		App->gui->DestroyAllUi();
		App->scene->active = true;
		App->scene->Start();
		
		this->active = false;
	}
	else if (g->position.y == 250)
	{
		App->gui->DestroyAllUi();
		close = true;
	}
	
}
