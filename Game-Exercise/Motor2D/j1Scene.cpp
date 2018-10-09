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
		App->map->Load("Map1.tmx");
	}
	


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
	/*if(change_map == true && App->fade_to_black->IsFading() == true)
	{ 
		App->map->CleanUp();
		App->map->Load("ForestMap.tmx");
		change_map = false;
		
		
	}*/
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame();

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame();
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		
		//App->fade_to_black->FadeToBlack(this, this, 2.0f);
		map_number = 2;
		ChangeMap(map_number);
		//change_map = true;
		is_faded = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		map_number = 1;
		ChangeMap(map_number);
		/*App->fade_to_black->FadeToBlack(this, this, 2.0f);
		change_map = true;
		App->map->Load("Map1.tmx");*/
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		LOG("%d camera x", App->render->camera.x);
		LOG("%d camera y", App->render->camera.y);
		App->render->camera.y -= 10;
	}
	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		LOG("%d camera x", App->render->camera.x);
		LOG("%d camera y", App->render->camera.y);
		App->render->camera.y += 10;
		}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		LOG("%d camera x", App->render->camera.x);
		LOG("%d camera y", App->render->camera.y);
		App->render->camera.x -= 10;
	}
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			LOG("%d camera x", App->render->camera.x);
			LOG("%d camera y", App->render->camera.y);
			App->render->camera.x += 10;
		}
	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN)
	{
		LOG("%d", App->audio->volume);
		change_music = true;
		App->audio->ChangeMusic(change_music);
	}
	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN)
	{
		LOG("%d", App->audio->volume);
		change_music = false;
		App->audio->ChangeMusic(change_music);
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		ChangeMap(map_number);
	}

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		collision_debug = !collision_debug;
	}

	//App->render->Blit(img, 0, 0);
	App->map->Draw();

	
	// "Map:%dx%d Tiles:%dx%d Tilesets:%d"
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
	}
	else if (map_number == 2)
	{
		App->fade_to_black->FadeToBlack(this, this, 3.0f);
		App->map->CleanUp();
		App->map->Load("ForestMap.tmx");
	}

	return true;

}


