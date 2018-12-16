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
	
	//MENU _UI
	
	SDL_Rect bck = { 0,0,1024,768 };
	background = App->gui->AddImage(0, 0, &bck, nullptr,this, nullptr);
	go_back = App->gui->AddButton(50, 50, {1129,95,48,51}, {1128,160,48,51}, { 1128,160,48,51 },this, nullptr);
	music = App->gui->AddLabel(100,300,App->languages->current_language.music_volume,this, nullptr);
	language = (Gui_Label*)App->gui->AddLabel(App->win->width - 450, 60, App->languages->current_language.choose_language, this, nullptr);
	slider = (Gui_Slider*)App->gui->AddSlider(music->animation.w + 150, 290,this, music);
	button = (GUI_Button*)App->gui->AddButton(0, 0, { 1068,297,55,55 }, { 1069,362,55,55 }, { 1069,421,55,55 },this, (GUI*)slider);
	slider->SetNumStart(App->audio->volume, button);
	slider->value = App->audio->volume;

	slider_fx = (Gui_Slider*)App->gui->AddSlider(music->animation.w + 150, 450, this, music);
	button_fx = (GUI_Button*)App->gui->AddButton(0, 0, { 1068,297,55,55 }, { 1069,362,55,55 }, { 1069,421,55,55 }, this, (GUI*)slider);
	slider_fx->SetNumStart(0, button_fx);
	slider_fx->value = App->audio->fx_volume;

	btn_language = (GUI_Button*)App->gui->AddButton(language->position.x + language->animation.w, 50, { 515,805,190,49 }, { 515,805,190,49 }, { 515,805,190,49 }, this, language);
	text_language = (Gui_Label*)App->gui->AddLabel(10, 10, App->languages->current_language.language.GetString(), this, nullptr);
	btn_language->SetText(text_language);

	if (App->languages->current_language.current == Language::ENLGLISH)
	{
		btn_spanish = (GUI_Button*)App->gui->AddButton(language->position.x + language->animation.w, btn_language->position.y + btn_language->animation.h, { 515,805,190,49 }, { 515,805,190,49 }, { 515,805,190,49 }, this, btn_language);
		text_language = (Gui_Label*)App->gui->AddLabel(10, 10, App->languages->spanish.language.GetString(), this, nullptr);
		btn_spanish->SetText(text_language);
		btn_spanish->invisible = true;
		text_language->invisible = true;
	}
	else if (App->languages->current_language.current == Language::SPANISH)
	{
		btn_english = (GUI_Button*)App->gui->AddButton(language->position.x + language->animation.w, btn_language->position.y + btn_language->animation.h, { 515,805,190,49 }, { 515,805,190,49 }, { 515,805,190,49 }, this, btn_language);
		text_language = (Gui_Label*)App->gui->AddLabel(10, 10, App->languages->English.language.GetString(), this, nullptr);
		btn_english->SetText(text_language);
		btn_english->invisible = true;
		text_language->invisible = true;
	}


	
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
		slider->UpadateNumStart(App->audio->volume,button);
		
	}
	/*if (button->MouseIn(button_fx) == true)
	{
		slider->MoveButton(button_fx);
		slider->UpadateNumStart(App->audio->volume, button_fx);

	}*/
	Mix_VolumeMusic(slider->value);
	//Mix_VolumeChunk(Mix_GetChunk(0), App->audio->fx_volume);

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



void Settings::Interact(GUI* g)
{
	
	if (g == btn_language)
	{
		if (App->languages->current_language.current == Language::ENLGLISH)
		{
			btn_spanish->invisible = false;
			text_language->invisible = false;
		}
		else if (App->languages->current_language.current == Language::SPANISH)
		{
			btn_english->invisible = false;
			text_language->invisible = false;
		}
	}
	else if (g == btn_spanish && btn_spanish->invisible == false)
	{
		App->gui->DestroyAllUi();
		App->languages->DeleteLanguage();
		App->languages->ChangeLanguage();
		App->settings->Start();
	}
	else if (g == btn_english && btn_english->invisible == false)
	{
		App->gui->DestroyAllUi();
		App->languages->DeleteLanguage();
		App->languages->ChangeLanguage();
		App->settings->Start();
	}
	
	else if (g == go_back)
	{
		App->fade_to_black->FadeToBlack(this, App->main_menu, 3.0f);
		App->gui->DestroyAllUi();
		App->main_menu->active = true;
		App->main_menu->Start();
		this->active = false;
	}

}
