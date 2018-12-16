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
#include "SelectCharacter.h"
#include "j1Languages.h"

#include "GUI_Button.h"
#include "GUI_Slider.h"

Characters::Characters() : j1Module()
{
	name.create("Characters");
}

// Destructor
Characters::~Characters()
{}

// Called before render is available
bool Characters::Awake()
{
	LOG("Loading main menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Characters::Start()
{
	
	//MENU _UI

	SDL_Rect bck = { 0,0,1024,768 };
	SDL_Rect bck2 = { 600,943,517,271 };
	background = App->gui->AddImage(0, 0, &bck, nullptr,this, nullptr);
	background2 = App->gui->AddImage((App->win->width / 2) - bck2.w/2, App->win->height / 2 - 50, &bck2, nullptr,this, nullptr);
	go_back = App->gui->AddButton(50, 50, { 1129,95,48,51 }, { 1128,160,48,51 }, { 1128,160,48,51 },this, nullptr);

	
	
	sasuke = (GUI_Button*)App->gui->AddButton(200, 50, { 1458,556,120,120 }, { 1318,554,120,120 }, { 1318,554,120,120 },this, nullptr);
	gaara = (GUI_Button*)App->gui->AddButton(400, 50, { 1458,686,120,120 }, { 1317,684,120,120 }, { 1317,684,120,120 },this, nullptr);
	anonymous = (GUI_Button*)App->gui->AddButton(600, 50, { 1056,683,120,120 }, { 1187,683,120,120 }, { 1187,683,120,120 },this, nullptr);
	return true;
}

// Called each loop iteration
bool Characters::PreUpdate()
{
	BROFILER_CATEGORY("ScenePreUpdate", Profiler::Color::BlanchedAlmond);
	
	return true;
}

// Called each loop iteration
bool Characters::Update(float dt)
{
	BROFILER_CATEGORY("SceneUpdate", Profiler::Color::MediumOrchid);
	//DEBUG KEYS
	/*if(btn_play!=nullptr)
	MouseIn(btn_play);*/
	if (show_stats == true) {
		ShowStats(sasuke);
	}
	App->input->GetMousePosition(mouse_x, mouse_y);
	if (start_game == true)
		StartGame();
	return true;
}

// Called each loop iteration
bool Characters::PostUpdate()
{
	BROFILER_CATEGORY("ScenePostUpdate", Profiler::Color::Navy);
	bool ret = true;
	
	if (close == true)
		ret = false;

	return ret;
}

// Called before quitting
bool Characters::CleanUp()
{
	LOG("Freeing main menu");

	return true;
}

//bool Characters::MouseIn(GUI* element)
//{
//
//	GUI_Button*  ex2 = (GUI_Button*)element;
//	if (element->type == BUTTON) {
//		if (mouse_x > element->position.x && mouse_x < element->position.x + element->animation.w && mouse_y > element->position.y && mouse_y < element->position.y + element->animation.h)
//		{
//			ex2->setAnimation(2);
//			
//		}
//		if (mouse_x > element->position.x && mouse_x < element->position.x + element->animation.w && mouse_y > element->position.y && mouse_y < element->position.y + element->animation.h)
//		{
//			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
//			{
//				ex2->setAnimation(3);
//				Interact(element);
//				return true;
//			}
//		
//		}
//		else
//		{
//			ex2->setAnimation(1);
//			return false;
//		}
//	}
//}

void Characters::Interact(GUI* g)
{
	if (g->position.y == 180)
	{
		App->fade_to_black->FadeToBlack(this, App->scene, 3.0f);
		App->gui->DestroyAllUi();
		App->scene->active = true;
		App->scene->Start();

		this->active = false;
	}
	else if (g->position.x == 200)
	{
		type = 1;
		start_game = true;
	}
	else if (g->position.x == 400)
	{
		type = 2;
		start_game = true;
	}
	else if (g->position.x == 600)
	{
	}
	else if (g->position.y == 50)
	{

		App->fade_to_black->FadeToBlack(this, App->main_menu, 3.0f);
		App->gui->DestroyAllUi();
		App->main_menu->active = true;
		App->main_menu->Start();
	}

}
bool Characters::ShowStats(GUI* g)
{
	if (g->position.x == 200 && show_stats == true && mouse_x > g->position.x && mouse_x < g->position.x + g->animation.w && mouse_y > g->position.y && mouse_y < g->position.y + g->animation.h)
	{
		stats_sasuke.name = (Gui_Label*)App->gui->AddLabel(500, 500, "Sasuke",this, nullptr);
		stats_sasuke.lifes = (Gui_Label*)App->gui->AddLabel(500, 600, "Lifes: 3",this, nullptr);
		type = SASUKE;
		return true;
	}
	else if (g->position.x == 400)
	{
		App->gui->AddLabel(500, 500, "Gaara",this, nullptr);
	}
	else if (g->position.x == 600)
	{
		App->gui->AddLabel(500, 600, "Finish the maps in less than 3 min to unlock it",this, nullptr);
	}
	else
	{
		show_stats = false;
		return false;
	}
}
void Characters::StartGame()
{
	if (type != 0) {
		btn_play = (GUI_Button*)App->gui->AddButton(App->win->width / 2 - 150, 180, { 1316,382,300,77 }, { 1316,299,300,77 }, { 1317,466,300,77 },this, nullptr);
		text_play = (Gui_Label*)App->gui->AddLabel(10, 10, App->languages->current_language.play.GetString(),this, btn_play);
		btn_play->SetText(text_play);
		App->scene->first_update = true;
		start_game = false;
	}
}