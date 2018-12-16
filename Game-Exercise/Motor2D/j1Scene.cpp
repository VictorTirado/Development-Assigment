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
#include "j1Scene.h"
#include "j1Entitites.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Fonts.h"
#include "j1Languages.h"
#include "Brofiler\Brofiler.h"
#include "Entity_Player.h"
#include "MainMenu.h"

#include "GUI_Image.h"
#include "GUI_Button.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	
	SDL_Rect ui_backround_rect = { 1057, 573, 243, 61 };
	ui_background = (GUI_Image*)App->gui->AddImage(0, 0, &ui_backround_rect, nullptr,this, nullptr);

	//PAUSE MENU
	SDL_Rect bck2 = { 1625,299,330,421 };
	background_menu = App->gui->AddImage(App->win->width / 2 - 165, 150, &bck2, nullptr, this, nullptr);
	background_menu->invisible = true;

	btn_resume = (GUI_Button*)App->gui->AddButton(App->win->width / 2 - 150, 180, { 1316,382,300,77 }, { 1316,299,300,77 }, { 1317,466,300,77 }, this, nullptr);
	text_resume = (Gui_Label*)App->gui->AddLabel(10, 10, App->languages->current_language.resume.GetString(), this, btn_resume);
	btn_resume->SetText(text_resume);
	btn_resume->invisible = true;
	text_resume->invisible = true;

	btn_back =  (GUI_Button*)App->gui->AddButton(App->win->width / 2 - 150, 260, { 1316,382,300,77 }, { 1316,299,300,77 }, { 1317,466,300,77 }, this, nullptr);
	text_back = (Gui_Label*)App->gui->AddLabel(10, 10, App->languages->current_language.exit.GetString(), this, btn_back);
	btn_back->SetText(text_back);
	btn_back->invisible = true;
	text_back->invisible = true;

	score2 = (Gui_Label*)App->gui->AddLabel(250, 10, "Score:", this, nullptr);
	
	App->entities->time_playing.Start();

	if (!is_faded && map_number == 1)
	{
		map_number = 1;
		if (App->map->Load("Map4.tmx") == true)
		{
			int w, h;
			uchar* data = NULL;
			if (App->map->CreateWalkabilityMap(w, h, &data))
				App->pathfinding->SetMap(w, h, data);

			RELEASE_ARRAY(data);
		}	
	}
	App->audio->PlayMusic(App->audio->path.GetString());
	App->audio->StartVolume(App->audio->volume);
	App->map->Spawn();
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	BROFILER_CATEGORY("ScenePreUpdate", Profiler::Color::BlanchedAlmond);
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("SceneUpdate", Profiler::Color::MediumOrchid);
	//DEBUG KEYS
	if (first_update == true)
	{
		App->entities->book->UpdateBookUI(App->entities->book->is_caught);
		App->entities->UpdatePlayerLifes(App->entities->playerLifes);

		char playerScore[sizeof App->entities->score];
		sprintf_s(playerScore, "%d", App->entities->score);
		player_score_text = App->gui->AddLabel(score2->position.x + score2->animation.w + 15, 10, playerScore, this, score2);

		/*char TimeScore[((sizeof App->entities->player_time  * CHAR_BIT) + 2) / 3 + 2];
		sprintf_s(TimeScore, "%.2f", App->entities->player_time);
		time_score_text = App->gui->AddLabel(App->win->width -100, 10, TimeScore, this, nullptr);*/
		
		first_update = false;
	}

	LOG("%f seconds", App->entities->player_time);
	UpdateTime(App->entities->player_time);
	//App->entities->UpdateTime(App->entities->player->player_time);
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		map_number = 1;
		ChangeMap(map_number);
		is_faded = true;
	}
	else if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		ChangeMap(map_number);
	}
	else if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();
	else if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();
	else if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		collision_debug = !collision_debug;
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		is_god = !is_god;

	/*else if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN)
	{
		change_music = true;
		App->audio->ChangeMusic(change_music);
	}
	else if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN)
	{	
		change_music = false;
		App->audio->ChangeMusic(change_music);
	}*/

	else if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		background_menu->invisible = !background_menu->invisible;
		btn_resume->invisible = !btn_resume->invisible;
		text_resume->invisible = !text_resume->invisible;
		btn_back->invisible = !btn_back->invisible;
		text_back->invisible = !text_back->invisible;
		paused = !paused;
	}

	App->map->Draw();
	
	LOG("%i", App->entities->entities.Count());
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("ScenePostUpdate", Profiler::Color::Navy);
	bool ret = true;

	/*if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;*/

	/*char time_played[sizeof App->entities->player_time];
	sprintf_s(time_played, "%d", App->entities->player_time);
	time_text = App->gui->AddLabel(700, 20, time_played, App->scene, nullptr);*/

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


bool j1Scene::ChangeMap(int map_number)
{
	BROFILER_CATEGORY("SceneChangeMap", Profiler::Color::DeepPink);
	bool ret = true;

	if (map_number == 1)
	{
		App->map->CleanUp();
		App->entities->DestroyEntities();
		App->fade_to_black->FadeToBlack(this, App->entities, 3.0f);
		App->map->Load("Map4.tmx");
		App->map->Spawn();
	}
	else if (map_number == 2)
	{
		App->map->CleanUp();
		App->entities->DestroyEntities();
		App->fade_to_black->FadeToBlack(this, App->entities, 3.0f);
		App->map->Load("ForestMap.tmx");
		App->map->Spawn();
	}
	return true;
}

void j1Scene::UpdateScore(int score)
{
	App->gui->DestroyUIElement(*player_score_text);
	char playerScore[sizeof App->entities->score];
	sprintf_s(playerScore, "%d", App->entities->score);
	player_score_text = App->gui->AddLabel(score2->position.x + score2->animation.w + 15, 10, playerScore, this, score2);
}

void j1Scene::UpdateTime(float time)
{
	App->gui->DestroyUIElement(*time_score_text);
	char TimeScore[((sizeof App->entities->player_time  * CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(TimeScore, "%.1f", App->entities->player_time);
	time_score_text = App->gui->AddLabel(App->win->width - 150, 10, TimeScore, this, nullptr);

}


void j1Scene::Interact(GUI* g)
{
	if (g == btn_resume && paused == true)
	{
		paused = !paused;
		background_menu->invisible = !background_menu->invisible;
		btn_resume->invisible = !btn_resume->invisible;
		text_resume->invisible = !text_resume->invisible;
		btn_back->invisible = !btn_back->invisible;
		text_back->invisible = !text_back->invisible;
	}
	else if (g == btn_back && paused == true)
	{
		App->fade_to_black->FadeToBlack(this, App->main_menu, 3.0f);
		App->map->CleanUp();
		App->gui->DestroyAllUi();
		App->entities->DestroyEntities();
		App->entities->score = 0;
		this->active = false;
		App->main_menu->active = true;
		App->main_menu->Start();
		App->main_menu->first_update = true;
		paused = false;
		

	}
}