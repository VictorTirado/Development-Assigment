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

	for (pugi::xml_node animations = player.child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		p2SString name = animations.attribute("name").as_string();
		if (name == "idle")
			LoadAnimation(animations, &idle);
		if (name == "run")
			LoadAnimation(animations, &run);
		if (name == "teleport")
			LoadAnimation(animations, &teleport);
		if (name == "jutsu")
			LoadAnimation(animations, &jutsu);
	}
	current_animation = &idle;

	idle.PushBack({ 4, 15, 37, 51 });
	
}

j1Player::~j1Player()
{}


bool j1Player::Start()
{
	bool ret = true;
	
	graphics = App->tex->Load("textures/Sasuke_sprites.png");

	return ret;
}

bool j1Player::PreUpdate()
{
	bool ret = true;

	if (player_data.type != ENTITY_TYPES::NO_TYPE)
	{
		LOG("Loading player");
		SpawnPlayer(player_data);
	}

	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;
	

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



bool j1Player::Save(pugi::xml_node& save) const
{
	bool ret = false;
	
	return ret;
}

bool j1Player::Load(pugi::xml_node& save)
{
	bool ret = false;

	return ret;
}

void j1Player::LoadAnimation(pugi::xml_node& animation, Animation* player)
{
	for (pugi::xml_node frame = animation.child("frame"); frame; frame = frame.next_sibling("frame"))
	{
		player->PushBack({frame.attribute("x").as_int(),frame.attribute("y").as_int(),frame.attribute("w").as_int(),frame.attribute("h").as_int()});
		player->speed = animation.child("animation").attribute("speed").as_float();
	}
	
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

