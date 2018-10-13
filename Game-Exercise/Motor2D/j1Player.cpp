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
#include "j1Collision.h"
#include "j1Book.h"
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
		if (name == "teleportBackwards")
			LoadAnimation(animations, &teleportBackwards);
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

	player_collider = App->collision->AddCollider({ 0, 0, 38, 54 }, COLLIDER_PLAYER, this);

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
		if (App->scene->map_number == 1)
		{
			player_position.x = App->map->spawn.x;
			player_position.y = App->map->spawn.y;
			LOG("%d", player_position.x);
				LOG("%d", player_position.y);
		}
		else if (App->scene->map_number == 2)
		{
			player_position.x = App->map->spawn.x;
			player_position.y = App->map->spawn.y;
		}
		App->render->camera.x = (-player_position.x * App->win->render_scale) + (App->win->width / 2);
		App->render->camera.y = (-player_position.y * App->win->render_scale) + (App->win->height / 2);
		
		firstUpdate = false;
	}
	else if (!is_backwards)
		current_animation = &idle;
	else if (is_backwards)
		current_animation = &idleBackwards;

	//LOGIC
	gid = App->map->Get_gid(player_position.x + 10, player_position.y + 51);
	App->render->DrawQuad({ player_position.x + 10,player_position.y + 51,16,16 }, 0, 0, 255, 255);
	if (App->map->data.map_layers.end->data->data[gid + 1] != 72 || App->map->data.map_layers.end->data->data[gid] == 71)
	{
		if (App->map->data.map_layers.end->data->data[gid + 1] != 51 && App->map->data.map_layers.end->data->data[gid] != 51 && !App->scene->is_god)
		{
			player_position.y += 1;
			is_falling = true;
			App->render->camera.y = (player_position.y) *(-App->win->render_scale) + (App->win->height / 2);
		}
		else
			is_falling = false;
	}
	if (App->map->data.map_layers.end->data->data[gid] == 71)
	{
		App->fade_to_black->FadeToBlack(this, this, 3.0f);
		App->map->CleanUp();
		if (App->scene->map_number == 1)
		{
			App->map->Load("Map2.tmx");
		}
		else if (App->scene->map_number == 2)
		{
			App->map->Load("ForestMap.tmx");
		}
		player_position.x = App->map->spawn.x;
		player_position.y = App->map->spawn.y;
		App->render->camera.x = (-player_position.x * App->win->render_scale) + (App->win->width / 2);
		App->render->camera.y = (-player_position.y * App->win->render_scale) + (App->win->height / 2);
	}
	if (App->map->data.map_layers.end->data->data[gid] == 72)
	{
		App->fade_to_black->FadeToBlack(this, this, 3.0f);
		App->map->CleanUp();
		if (App->scene->map_number == 1)
		{
			App->map->Load("ForestMap.tmx");
			App->scene->map_number = 2;
			firstUpdate = true;
		}
		else if (App->scene->map_number == 2)
		{
			App->map->Load("Map2.tmx");
			App->scene->map_number = 1;
			firstUpdate = true;
		}
		
		player_position.x = App->map->spawn.x;
		player_position.y = App->map->spawn.y;
		App->render->camera.x = (-player_position.x * App->win->render_scale) + (App->win->width / 2);
		App->render->camera.y = (-player_position.y * App->win->render_scale) + (App->win->height / 2);
	}
	//MOVEMENT PLAYER
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->map->data.map_layers.end->data->data[gid-1] != 53)
	{
		App->render->camera.x = (-player_position.x * App->win->render_scale) + (App->win->width/2);
		App->render->camera.y = (-player_position.y * App->win->render_scale) + (App->win->height / 2);
		current_animation = &runBackwards;
		is_backwards = true;
		player_position.x -= MOVEMENT_SPEED;
	}

	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->map->data.map_layers.end->data->data[gid + 1] != 53)
	{
		App->render->camera.x = (-player_position.x * App->win->render_scale) + (App->win->width / 2);
		App->render->camera.y = (-player_position.y * App->win->render_scale) + (App->win->height / 2);
		current_animation = &run;
		is_backwards = false;
		player_position.x += MOVEMENT_SPEED;
	}

	else if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
		current_animation = &jutsu;

	


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

	//TELEPORT
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT && App->map->data.map_layers.end->data->data[gid + 1] == 51 && can_tp)
	{
		current_animation = &teleport;
		player_position.y -= 100;
	}


	//GOD MODE  The player can fly and move everywhere and is not affected by gravity

	if (App->scene->is_god)
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			App->render->camera.x = (-player_position.x * App->win->render_scale) + (App->win->width / 2);
			App->render->camera.y = (-player_position.y * App->win->render_scale) + (App->win->height / 2);
			player_position.y -= 4;
		}
			

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			App->render->camera.x = (-player_position.x * App->win->render_scale) + (App->win->width / 2);
			App->render->camera.y = (-player_position.y * App->win->render_scale) + (App->win->height / 2);
			player_position.y += 4;
		}
			
	}

	player_collider->SetPos(player_position.x, player_position.y);
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
	if(data.child("map") != NULL)
		App->scene->map_number = data.child("map").attribute("level").as_int();

	if (App->scene->map_number == 2 && data.child("map") != NULL)
	{
		App->fade_to_black->FadeToBlack(this, this, 3.0f);
		App->map->CleanUp();
		App->map->Load("ForestMap.tmx");
		player_position.x = data.child("position").attribute("x").as_int();
		player_position.y = data.child("position").attribute("y").as_int();
	}
	else if (App->scene->map_number == 1 && data.child("map") != NULL)
	{
		App->fade_to_black->FadeToBlack(this, this, 3.0f);
		App->map->CleanUp();
		App->map->Load("Map1.tmx");
		player_position.x = data.child("position").attribute("x").as_int();
		player_position.y = data.child("position").attribute("y").as_int();
	}


	return true;
}

bool j1Player::Save(pugi::xml_node& data)const
{
	data.append_child("map").append_attribute("level") = App->scene->map_number;
	data.append_child("position").append_attribute("x") = player_position.x;
	data.child("position").append_attribute("y") = player_position.y;
	return true;
}

void j1Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_POWER_UP)
	{
		App->book->CleanUp();
		can_tp = true;
	}


}


