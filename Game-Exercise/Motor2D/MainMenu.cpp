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
#include "Settings.h"
#include "SelectCharacter.h"
#include "j1Languages.h"
#include "Credits.h"

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
	SDL_Rect bck = { 0,0,1024,768 };
	SDL_Rect bck2 = { 1625,299,330,421 };
	SDL_Rect set = { 1067,54,37,37 };
	//MENU _UI
	
	background = App->gui->AddImage(0, 0, &bck,nullptr,this, nullptr);
	background2 = App->gui->AddImage(App->win->width/2 - 165, 150, &bck2, nullptr,this, nullptr);
	

	
	//BTN_CONTINUE
	btn_play = (GUI_Button*)App->gui->AddButton(App->win->width/2 -150,180 , { 1316,382,300,77 }, { 1316,299,300,77 }, { 1317,466,300,77 },this, nullptr);
	text_play = (Gui_Label*)App->gui->AddLabel(10, 10, App->languages->current_language.play.GetString(),this,btn_play);
	btn_play->SetText(text_play);

	//BTN_CONTINUE
	if (root.child("entities").child("player").child("position").attribute("x").as_int() != NULL) {
		btn_continue = (GUI_Button*)App->gui->AddButton(App->win->width / 2 - 150, 320, { 1316,382,300,77 }, { 1316,299,300,77 }, { 1317,466,300,77 },this, nullptr);
		text_play = (Gui_Label*)App->gui->AddLabel(10, 10,App->languages->current_language.continue_.GetString(),this, nullptr);
		btn_continue->SetText(text_play);
	}

	btn_credits = (GUI_Button*)App->gui->AddButton(App->win->width / 2 - 150, 460, { 1316,382,300,77 }, { 1316,299,300,77 },{ 1317,466,300,77 },this, nullptr);
	text_credits = (Gui_Label*)App->gui->AddLabel(10, 10, App->languages->current_language.credits.GetString(),this, nullptr);
	btn_credits->SetText(text_credits);
	btn_settings = App->gui->AddButton(App->win->width - 150, 150, { 1137,298,55,55 }, { 1138,361,55,55 }, { 1137,419,55,55 },this,nullptr);

	adjust = App->gui->AddImage(btn_settings->position.x + btn_settings->animation.w/6, btn_settings->position.y - 3 + btn_settings->animation.h / 6, &set, nullptr,this, btn_settings);
	btn_exit = App->gui->AddButton(App->win->width - 150, 50, { 1207,298,55,55 }, { 1207,361,55,55 }, { 1207,420,55,55 },this, nullptr);

	//select_lng = (GUI_Box*)App->gui->AddBox(0, 0, (GUI_Button*)btn_language,(GUI_Button*)btn_options, this, nullptr);
	//select_lng->SetOptions((GUI_Button*)btn_options);


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
	if (first_update == true)
	{
		App->audio->PlayMusic("audio/music/Main_menu.ogg");
		first_update = false;
	}

	App->input->GetMousePosition(mouse_x, mouse_y);

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		App->gui->DestroyAllUi();
		App->languages->DeleteLanguage();
		App->languages->ChangeLanguage();
		App->main_menu->Start();

	}

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

//bool MainMenu::MouseIn(GUI* element)
//{
//
//	GUI_Button*  ex2 = (GUI_Button*)element;
//	if (element->type == BUTTON) {
//		if (mouse_x > element->position.x && mouse_x < element->position.x + element->animation.w && mouse_y > element->position.y && mouse_y < element->position.y + element->animation.h)
//		{
//			ex2->setAnimation(2);
//			if (delete_kunais == false) {
//			//	kunai_left = App->gui->AddImage(element->position.x - 60, element->position.y + 10,nullptr, &App->gui->shuriken,nullptr);
//				//kunai_right = App->gui->AddImage(element->position.x + 270, element->position.y + 10, nullptr, &App->gui->shuriken,nullptr);
//				delete_kunais = true;
//				return true;
//			}
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
//			if(kunai_left != nullptr || kunai_right != nullptr && delete_kunais == true){
//				kunai_left->delete_ui = true;
//				kunai_right->delete_ui = true;
//				delete_kunais = false;
//				return false;
//				
//			}
//			
//		}
//	}
//}

void MainMenu::Interact(GUI* g)
{
	if (g == btn_play)
	{
		if (App->fade_to_black->IsFading() == false) {
			App->fade_to_black->FadeToBlack(this, App->scene, 2.0f);
			App->gui->DestroyAllUi();
			App->characters->active = true;
			App->characters->Start();
		}	
		this->active = false;
	}
	else if (g == btn_continue)
	{
		
		App->fade_to_black->FadeToBlack(App->scene, App->entities, 3.0f);
		App->gui->DestroyAllUi();
		App->settings->active = true;
		App->settings->Start();

		this->active = false;
	}
	else if (g == btn_credits)
	{
		App->fade_to_black->FadeToBlack(App->scene, App->entities, 3.0f);
		App->gui->DestroyAllUi();
		App->credits->active = true;
		App->credits->Start();

		this->active = false;
	}
	else if (g == btn_exit)
	{
		App->gui->DestroyAllUi();
		close = true;
	}
	
}


