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

	player_position.x = 170;
	player_position.y = 315;

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
		if (name == "jump")
			LoadAnimation(animations, &jump);
		if (name == "fall")
			LoadAnimation(animations, &fall);
		if (name == "jumpBackwards")
			LoadAnimation(animations, &jumpBackwards);
		if (name == "fallBackwards")
			LoadAnimation(animations, &fallBackwards);
	}

	current_animation = &idle;
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

	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;

	if (firstUpdate == true)
	{
		App->render->camera.x = -player_position.x  + (App->win->width / 2);
		App->render->camera.y = -player_position.y - (App->win->height / 2);

		firstUpdate = false;
	}
	if (!is_backwards)
		current_animation = &idle;
	
	gid = App->map->Get_gid(player_position.x +10, player_position.y+51);
	App->render->DrawQuad({player_position.x + 10,player_position.y+51,16,16},0,0,255,255);
	
	if (is_backwards)
		current_animation = &idleBackwards;

	//if (current_animation == &idle && firstUpdate == false){
	//	App->render->camera.x = -player_position.x;
	//	App->render->camera.y = -player_position.y - (App->win->height/2);
	//	LOG("%d pos x", player_position.x);
	//	LOG("%d pos y", player_position.y);
	//	LOG("%d camera x", App->render->camera.x);
	//	LOG("%d camera y", App->render->camera.y);
	//}
	
	//LOGIC
	if (App->map->data.map_layers.end->data->data[gid] != 51 /*|| App->map->data.map_layers.end->data->data[gid] != 51*/)
	{
		player_position.y += 1;
		is_falling = true;
		App->render->camera.y = player_position.y* -3 + (App->win->height / 2);
	}
	else
	{
		player_position.y = player_position.y;
		is_falling = false;
	}
	if (App->map->data.map_layers.end->data->data[gid -1] == 53 || App->map->data.map_layers.end->data->data[gid + 1] == 53)
	{
		LOG("HOLAAAAAAAAAAAAAAAAAAAA");
		player_position.x = player_position.x;
	}

	/*if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		App->render->camera.x = -player_position.x ;
		App->render->camera.y = -player_position.y - 350;
		player_position.y += MOVEMENT_SPEED;
	}*/

	
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		App->render->camera.x = -player_position.x*3 + (App->win->width/2);
		App->render->camera.y = -player_position.y * 3 + (App->win->height / 2);
		current_animation = &runBackwards;
		is_backwards = true;
		player_position.x -= MOVEMENT_SPEED;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		App->render->camera.x = -player_position.x*3 + (App->win->width / 2);
		App->render->camera.y = -player_position.y * 3 + (App->win->height / 2);
		current_animation = &run;
		is_backwards = false;
		player_position.x += MOVEMENT_SPEED;
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
		current_animation = &jutsu;

	if (App->map->data.map_layers.end->data->data[gid] == 71)
	{
		player_position.x = 50;
		player_position.y = 250;
	}


	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		//if (App->map->data.map_layers.end->data->data[gid] == 51)
			is_jumping = true;
	}
	

	//JUMP
	if (jumping_time == 0.0f)
	   player_position_y0 = - 1 * player_position.y;


	if (is_jumping)
	{
		jumping_time += 0.1f;
		
		player_position.y -= gravity;

		if (player_position.y > player_position_y0 && jumping_time >= 1.5f)
		{
			player_position.y += 5;
			jumping_time = 0.0f;
			is_jumping = false;
			is_falling = true;
		}
	}
	
	if (is_falling && !is_backwards)
		current_animation = &fall;

	if (is_falling && is_backwards)
		current_animation = &fallBackwards;

	if (is_jumping && is_backwards)
		current_animation = &jumpBackwards;

	if(is_jumping && !is_backwards)
		current_animation = &jump;


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
	
	App->tex->UnLoad(graphics);
	graphics = nullptr;

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

	if (data.child("position") != nullptr)
	{
		player_position.x = data.child("position").attribute("x").as_int();
		player_position.y = data.child("position").attribute("y").as_int();
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

	if (data.child("position") == NULL)
	{
		data.append_child("position").append_attribute("x") = player_position.x;
		data.append_child("position").append_attribute("y") = player_position.y;
	}

	else
	{
		data.child("position").attribute("x") = player_position.x;
		data.child("position").attribute("y") = player_position.y;
	}

	return true;
}
