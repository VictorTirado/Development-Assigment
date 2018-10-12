#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1FadeToBlack.h"
#include "j1Scene.h"

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
	if (!is_faded)
	{
		map_number = 1;
		App->map->Load("Map2.tmx");
	}
	


	//App->audio->PlayMusic(App->audio->path.GetString());
	//App->audio->StartVolume(App->audio->volume);

	

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
	/*if(change_map == true && App->fade_to_black->IsFading() == true)
	{ 
		App->map->CleanUp();
		App->map->Load("ForestMap.tmx");
		change_map = false;	
	}*/

	//DEBUG KEYS
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		map_number = 1;
		ChangeMap(map_number);
		is_faded = true;
	}
	else if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		map_number = 2;
		ChangeMap(map_number);
		/*App->fade_to_black->FadeToBlack(this, this, 2.0f);
		change_map = true;
		App->map->Load("Map1.tmx");*/
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

	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count());
	App->win->SetTitle(title.GetString());
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
		App->map->Load("Map1.tmx");
		App->player->player_position.x = App->map->spawn.x;
		App->player->player_position.y = App->map->spawn.y;
		App->render->camera.x = (-App->player->player_position.x * App->win->render_scale) + (App->win->width / 2);
		App->render->camera.y = (-App->player->player_position.y * App->win->render_scale) + (App->win->height / 2);
	}
	else if (map_number == 2)
	{
		App->fade_to_black->FadeToBlack(this, this, 3.0f);
		App->map->CleanUp();
		App->map->Load("ForestMap.tmx");
	}

	return true;

}


