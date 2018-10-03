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
		if(name == "idle")
		LoadAnimation(animations, &idle);
		if (name == "run")
			LoadAnimation(animations, &run);
		if (name == "teleport")
			LoadAnimation(animations, &teleport);
		if (name == "jutsu")
			LoadAnimation(animations, &jutsu);
	}

}

j1Player::~j1Player()
{}


bool j1Player::Start()
{
	bool ret = true;
	
	return ret;
}

bool j1Player::PreUpdate()
{
	bool ret = true;
	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		player_position.x += 3;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		player_position.x -= 3;
	
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

