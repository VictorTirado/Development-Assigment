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
	if (!is_faded && map_number == 1)
	{
		map_number = 1;
		App->map->Load("Map2.tmx");
		
	}
	//App->map->Spawn();
	//App->entities->SpawnEntities(0, 0, PLAYER);
	//App->entities->SpawnEntities(0, 0, BOOK);
	App->audio->PlayMusic(App->audio->path.GetString());
	App->audio->StartVolume(App->audio->volume);

	

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	//DEBUG KEYS
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		map_number = 1;
		ChangeMap(map_number);
		//App->entities->book->Start();
		is_faded = true;
	}
	else if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		if (map_number = 1)
		{
			App->entities->player->can_tp = false;
			App->entities->player->firstUpdate = true;
			App->entities->book->firstUpdate = true;
		}
		
	}
	else if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();
	else if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();
	else if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		collision_debug = !collision_debug;
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		is_god = !is_god;

	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
		fps_are_cap = !fps_are_cap;
	
		

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

	//p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
	//				App->map->data.width, App->map->data.height,
	//				App->map->data.tile_width, App->map->data.tile_height,
	//				App->map->data.tilesets.count());
	//App->win->SetTitle(title.GetString());
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
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
	bool ret = true;

	if (map_number == 1)
	{
		App->fade_to_black->FadeToBlack(this, this, 3.0f);
		App->map->CleanUp();
		App->map->Load("Map2.tmx");
		App->entities->player->firstUpdate = true;
		App->entities->book->firstUpdate = true;
		App->render->camera.x = (-App->entities->player->position.x * App->win->render_scale) + (App->win->width / 2);
		App->render->camera.y = (-App->entities->player->position.y * App->win->render_scale) + (App->win->height / 2);
	}
	else if (map_number == 2)
	{
		App->fade_to_black->FadeToBlack(this, this, 3.0f);
		App->map->CleanUp();
		App->map->Load("ForestMap.tmx");
	}

	return true;

}


