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
#include "Brofiler\Brofiler.h"
#include "Entity_Player.h"

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

	full_heart = App->gui->AddImage(20, 20, { 55, 48, 26, 22 });

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

	
	App->gui->MoveGui(full_heart, dt);
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
	

	else if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN)
	{
		change_music = true;
		App->audio->ChangeMusic(change_music);
	}
	else if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN)
	{	
		change_music = false;
		App->audio->ChangeMusic(change_music);
	}

	App->map->Draw();

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("ScenePostUpdate", Profiler::Color::Navy);
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

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


