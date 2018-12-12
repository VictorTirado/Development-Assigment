#include "j1Languages.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1FadeToBlack.h"
#include "Brofiler\Brofiler.h"

j1Languages::j1Languages() : j1Module()
{
	name.create("language");

}

j1Languages::~j1Languages()
{}


bool j1Languages::Awake(pugi::xml_node& config)
{
	pugi::xml_document languages;
	pugi::xml_node language;
	
	language = App->LoadLanguages(languages,ENGLISH);
	English.current = Language::ENLGLISH;
	English.play = language.child("main_menu").child("play").attribute("value").as_string();
	English.continue_ = language.child("main_menu").child("continue").attribute("value").as_string();
	English.settings = language.child("main_menu").child("settings").attribute("value").as_string();
	English.exit = language.child("main_menu").child("exit").attribute("value").as_string();

	current_language = English;
	bool ret = true;
	return ret;
}

bool j1Languages::Start()
{
	bool ret = true;
	

	return ret;
}

bool j1Languages::PreUpdate()
{
	bool ret = true;
	


	return ret;
}

bool j1Languages::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		ChangeLanguage();

	LOG("Language: %s", current_language.play.GetString());
	
	bool ret = true;

	return ret;
}

bool j1Languages::PostUpdate()
{

	bool ret = true;
	return ret;
}

bool j1Languages::CleanUp()
{
	return true;
}

bool j1Languages::Load(pugi::xml_node& data)
{
	bool ret = true;
	return ret;
}

bool j1Languages::Save(pugi::xml_node& data)const
{
	bool ret = true;


	return ret;
}

bool j1Languages::ChangeLanguage()
{
	bool ret = true;
	if (current_language.current == ENGLISH) {
		current_language.current = SPANISH;
		LoadLanguage(Language::SPANISH);
		
	}
	else if (current_language.current == SPANISH)
	{
		current_language.current = ENLGLISH;
		LoadLanguage(Language::ENLGLISH);
	
	}
	return ret;
}
void j1Languages::DeleteLanguage()
{
	current_language.continue_ = nullptr;
	current_language.exit = nullptr;
	current_language.play = nullptr;
	current_language.settings = nullptr;
	
}
bool j1Languages::LoadLanguage(Language _language_)
{
	bool ret = false;
	pugi::xml_document languages;
	if (current_language.current == SPANISH && Language::SPANISH)
	{
		pugi::xml_node language_spanish;
		language_spanish = App->LoadLanguages(languages, ESPAÑOL);
		LanguageContent spanish;
		spanish.current = Language::SPANISH;
		spanish.play = language_spanish.child("menu_principal").child("jugar").attribute("value").as_string();
		spanish.continue_ = language_spanish.child("menu_principal").child("continuar").attribute("value").as_string();
		spanish.settings = language_spanish.child("menu_principal").child("opciones").attribute("value").as_string();
		spanish.exit = language_spanish.child("menu_principal").child("salir").attribute("value").as_string();

		current_language = spanish;

		
	}
	if (current_language.current == ENLGLISH/* && Language::ENLGLISH*/)
	{
		pugi::xml_node language_english;
		language_english = App->LoadLanguages(languages, ENGLISH);
		LanguageContent English;
		English.current = Language::ENLGLISH;
		English.play = language_english.child("main_menu").child("play").attribute("value").as_string();
		English.continue_ = language_english.child("main_menu").child("continue").attribute("value").as_string();
		English.settings = language_english.child("main_menu").child("opcions").attribute("value").as_string();
		English.exit = language_english.child("main_menu").child("exit").attribute("value").as_string();

		current_language = English;


	}
	return ret;
}






