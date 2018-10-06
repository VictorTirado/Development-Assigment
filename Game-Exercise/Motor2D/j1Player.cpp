#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Scene.h"
//#include "j1Particles.h"
#include "j1FadeToBlack.h"
//#include "ModuleCollision.h"


j1Player::j1Player() : j1Module()
{
	name.create("player");
	pugi::xml_document player_file;
	pugi::xml_node player;
	player = App->LoadPlayer(player_file);

	player_position.x = 0;
	player_position.y = 0;

	path = player.child("folder").attribute("path").as_string();
	for (pugi::xml_node animations = player.child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		p2SString name = animations.attribute("name").as_string();
		if (name == "idle")
			LoadAnimation(animations, &idle);
		if (name == "idleBackwards")
			LoadAnimation(animations, &idleBackwards);
		if (name == "run")
			LoadAnimation(animations, &run);
		if (name == "runBackwards")
			LoadAnimation(animations, &runBackwards);
		if (name == "teleport")
			LoadAnimation(animations, &teleport);
		if (name == "jutsu")
			LoadAnimation(animations, &jutsu);
	}
	current_animation = &idle;

	//idle.PushBack({ 4, 15, 37, 51 });
	//idle.speed = 2.0f;
}

j1Player::~j1Player()
{}


bool j1Player::Start()
{
	bool ret = true;
	
	graphics = App->tex->Load(path.GetString());

	return ret;
}

bool j1Player::PreUpdate()
{
	bool ret = true;

	/*if (player_data.type != ENTITY_TYPES::NO_TYPE)
	{
		LOG("Loading player");
		SpawnPlayer(player_data);
	}*/

	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;

	if (!is_backwards)
	{
		current_animation = &idle;
	}
	

	if (is_backwards)
		current_animation = &idleBackwards;
	
	if (firstUpdate == true) 
	{
		App->render->camera.x = -player_position.x +(App->win->width/2);
		App->render->camera.y = player_position.y + (App->win->height/2);
		firstUpdate = false;
	}
		
	
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		App->render->camera.x = -player_position.x;
		App->render->camera.y = player_position.y;
		player_position.y += 7;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		player_position.y -= 7;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		App->render->camera.x = -player_position.x * 3 + (App->win->width / 2);
		App->render->camera.y = player_position.y + (App->win->height / 2);
		
		current_animation = &runBackwards;
		is_backwards = true;
		player_position.x -= MOVEMENT_SPEED;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		App->render->camera.x = -player_position.x*3 + (App->win->width / 2);
		App->render->camera.y = player_position.y + (App->win->height / 2);
		current_animation = &run;
		is_backwards = false;
		player_position.x += MOVEMENT_SPEED;
	}
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
	{
		current_animation = &jutsu;
		
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		
	}

	

	App->render->Blit(graphics, player_position.x, player_position.y, &current_animation->GetCurrentFrame());

	return ret;
}

bool j1Player::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool j1Player::CleanUp()
{
	LOG("Unloading player");
	
	return true;
}


void j1Player::LoadAnimation(pugi::xml_node& animation, Animation* player)
{
	for (pugi::xml_node frame = animation.child("frame"); frame; frame = frame.next_sibling("frame"))
	{
		player->PushBack({frame.attribute("x").as_int(),frame.attribute("y").as_int(),frame.attribute("w").as_int(),frame.attribute("h").as_int()});
		
	}
	player->speed = animation.attribute("speed").as_float();
	player->loop = animation.attribute("loop").as_bool();
}

bool j1Player::AddPlayer(ENTITY_TYPES type, int x, int y)
{
	bool ret = true;

	player_data.type = type;
	player_data.x = x;
	player_data.y = y;

	return ret;
}

void j1Player::SpawnPlayer(const PlayerInfo& info)
{
	if (info.type == ENTITY_TYPES::PLAYER)
		player_spawn = new j1Player();
}


bool j1Player::Load(pugi::xml_node& data)
{

	if (data.child("map") != nullptr)
	{
		App->scene->map_number = data.child("map").attribute("level").as_int();
	}

	if (App->scene->map_number == 2)
	{
		App->scene->ChangeMap(App->scene->map_number);
	}
	else if (App->scene->map_number == 1)
	{
		App->scene->ChangeMap(App->scene->map_number);
	}

	return true;
}

bool j1Player::Save(pugi::xml_node& data)const
{
	if (data.child("map") == NULL)
	{
		data.append_child("map").append_attribute("level") = App->scene->map_number;
	}
	else
	{
		data.child("map").attribute("level") = App->scene->map_number;
	}

	return true;
}
