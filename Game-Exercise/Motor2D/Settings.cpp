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
#include "Settings.h"

#include "GUI_Button.h"
#include "GUI_Slider.h"

Settings::Settings() : j1Module()
{
	name.create("Settings");
}

// Destructor
Settings::~Settings()
{}

// Called before render is available
bool Settings::Awake()
{
	LOG("Loading main menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Settings::Start()
{
	pugi::xml_document data;
	pugi::xml_node root;
	pugi::xml_parse_result result = data.load_file("save_game.xml");
	root = data.child("game_state");

	//MENU _UI
	
	SDL_Rect bck = { 0,0,1024,768 };
	background = App->gui->AddImage(0, 0, &bck, nullptr,this, nullptr);
	go_back = App->gui->AddButton(50, 50, {1129,95,48,51}, {1128,160,48,51}, { 1128,160,48,51 },this, nullptr);
	music = App->gui->AddLabel(100,300,App->languages->current_language.music_volume,this, nullptr);
	language = (Gui_Label*)App->gui->AddLabel(App->win->width - 450, 60, App->languages->current_language.choose_language, this, nullptr);
	slider = (Gui_Slider*)App->gui->AddSlider(music->animation.w + 150, 290,this, music);
	button = (GUI_Button*)App->gui->AddButton(0, 0, { 1068,297,55,55 }, { 1069,362,55,55 }, { 1069,421,55,55 },this, (GUI*)slider);
	slider->SetNumStart(App->audio->volume, button);
	//music_volume = (Gui_Label*)App->gui->AddLabel(slider->position.x + slider->animation.w +20, slider->position.y + 10, App->audio->volume, this, nullptr);

	btn_language = (GUI_Button*)App->gui->AddButton(App->win->width - 250, 50, { 515,805,190,49 }, { 515,805,190,49 }, { 515,805,190,49 }, this, nullptr);
	text_language = (Gui_Label*)App->gui->AddLabel(10, 10, App->languages->current_language.language.GetString(), this, nullptr);
	btn_language->SetText(text_language);
	
	return true;
}

// Called each loop iteration
bool Settings::PreUpdate()
{
	BROFILER_CATEGORY("ScenePreUpdate", Profiler::Color::BlanchedAlmond);
	return true;
}

// Called each loop iteration
bool Settings::Update(float dt)
{
	BROFILER_CATEGORY("SceneUpdate", Profiler::Color::MediumOrchid);
	//DEBUG KEYS
	if (button->MouseIn(button) == true)
	{
		slider->MoveButton(button);
		slider->UpadteNumStart(App->audio->volume,button);
	}
	Mix_VolumeMusic(slider->value);

	App->input->GetMousePosition(mouse_x, mouse_y);
	return true;
}

// Called each loop iteration
bool Settings::PostUpdate()
{
	BROFILER_CATEGORY("ScenePostUpdate", Profiler::Color::Navy);
	bool ret = true;
	
	if (close == true)
		ret = false;

	return ret;
}

// Called before quitting
bool Settings::CleanUp()
{
	LOG("Freeing main menu");

	return true;
}

//bool Settings::MouseIn(GUI* element)
//{
//
//	GUI_Button*  ex2 = (GUI_Button*)element;
//	if (element->type == BUTTON) {
//		if (mouse_x > element->position.x && mouse_x < element->position.x + element->animation.w && mouse_y > element->position.y && mouse_y < element->position.y + element->animation.h)
//		{
//			ex2->setAnimation(2);
//			
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
//		}
//		else
//		{
//			ex2->setAnimation(1);
//			return false;
//		}
//	}
//}

void Settings::Interact(GUI* g)
{
	if (g->position.y == 180)
	{
		App->fade_to_black->FadeToBlack(this, App->scene, 3.0f);
		App->gui->DestroyAllUi();
		App->scene->active = true;
		App->scene->Start();

		this->active = false;
	}
	else if (g == btn_language)
	{
		SelectLanguage(btn_language);
		
	}
	else if (g == btn_spanish  )
	{
		App->gui->DestroyAllUi();
		App->languages->DeleteLanguage();
		App->languages->ChangeLanguage();
		App->settings->Start();
	}
	else if (g == btn_english)
	{
		App->gui->DestroyAllUi();
		App->languages->DeleteLanguage();
		App->languages->ChangeLanguage();
		App->settings->Start();
	}
	
	else if (g->position.y == 50)
	{
		App->fade_to_black->FadeToBlack(this, App->main_menu, 3.0f);
		App->gui->DestroyAllUi();
		App->main_menu->active = true;
		App->main_menu->Start();
		this->active = false;
	}

}
void Settings::SelectLanguage(GUI_Button* btn_language)
{
	if (App->languages->current_language.current == Language::ENLGLISH) {
		btn_spanish = (GUI_Button*)App->gui->AddButton(btn_language->position.x, btn_language->position.y + btn_language->animation.h, { 515,805,190,49 }, { 515,805,190,49 }, { 515,805,190,49 }, this, btn_language);
		text_language = (Gui_Label*)App->gui->AddLabel(10, 10, App->languages->spanish.language.GetString(), this, nullptr);
		btn_spanish->SetText(text_language);
	}
	else if (App->languages->current_language.current == Language::SPANISH)
	{
		btn_english = (GUI_Button*)App->gui->AddButton(btn_language->position.x, btn_language->position.y + btn_language->animation.h, { 515,805,190,49 }, { 515,805,190,49 }, { 515,805,190,49 }, this, btn_language);
		text_language = (Gui_Label*)App->gui->AddLabel(10, 10, App->languages->English.language.GetString(), this, nullptr);
		btn_english->SetText(text_language);
	}
}