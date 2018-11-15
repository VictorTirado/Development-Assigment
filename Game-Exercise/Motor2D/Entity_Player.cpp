#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1Entitites.h"
#include "j1FadeToBlack.h"

#include "Entity_Player.h"
#include "Entity_Book.h"

Entity_Player::Entity_Player(int x, int y) : Entity(x , y)
{
	sprites = App->tex->Load(App->entities->textures.GetString());
	pugi::xml_document player_file;
	pugi::xml_node player;
	player = App->LoadEntities(player_file, Entities::PLAYER_ENTITY);

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

	deathfx_path = player.child("audio").attribute("path").as_string();
	teleportfx_path = player.child("audio2").attribute("tp_path").as_string();
	
	animation = &idle;
	
	
	
	
	App->audio->LoadFx(deathfx_path.GetString());
	App->audio->LoadFx(teleportfx_path.GetString());
}

Entity_Player::~Entity_Player()
{
	CleanUp();
}


bool Entity_Player::Start()
{
	bool ret = true;

	
	
	return ret;
}

bool Entity_Player::PreUpdate()
{
	bool ret = true;

	return ret;
}

void Entity_Player::Update(float dt)
{
	if (firstUpdate == true)
	{
		can_tp = false;
		collider = App->collision->AddCollider({ 0, 0, 38, 54 }, COLLIDER_TYPE::COLLIDER_PLAYER, App->entities);
		firstUpdate = false;
	}

	else if (!is_backwards)
		animation = &idle;
	else if (is_backwards)
		animation = &idleBackwards;

	player_pos = App->map->WorldToMap(position.x, position.y);

	//LOGIC
	gid = App->map->Get_gid(position.x + 10, position.y + 51);
	
	if (App->map->data.map_layers.end->data->data[gid + 1] != Collision_Type::COLLISION_CHANGE_MAP || App->map->data.map_layers.end->data->data[gid] == Collision_Type::COLLISION_DEATH)
	{
		if (App->map->data.map_layers.end->data->data[gid + 1] != Collision_Type::COLLISION_WALL && App->map->data.map_layers.end->data->data[gid] != Collision_Type::COLLISION_WALL)
		{
			position.y += 70 * dt;
			is_falling = true;
		}
		else
			is_falling = false;
	}
	if (App->map->data.map_layers.end->data->data[gid] == Collision_Type::COLLISION_DEATH)
	{
		
		App->map->CleanUp();
		if (App->scene->map_number == 1)
		{
			App->map->Load("Map2.tmx");
			can_tp = false;
			App->entities->book->firstUpdate = true;
		}
		else if (App->scene->map_number == 2)
			App->map->Load("ForestMap.tmx");
		
		App->entities->DestroyEntities();
		//App->entities->book->CleanUp();
		
		App->audio->PlayFx(1); //player's death fx
		App->fade_to_black->FadeToBlack(App->scene, App->entities, 3.0f);
		App->map->Spawn();
	}

	if (App->map->data.map_layers.end->data->data[gid] == Collision_Type::COLLISION_CHANGE_MAP)
	{
		
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
			can_tp = false;
			//App->entities->book->Start();
		}
		App->fade_to_black->FadeToBlack(App->scene, App->entities, 3.0f);
	}
	//MOVEMENT PLAYER
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->map->data.map_layers.end->data->data[gid-1] != 53 && App->fade_to_black->IsFading() == false)
	{	
		animation = &runBackwards;
		is_backwards = true;
		position.x -= 80*dt;
	}

	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->map->data.map_layers.end->data->data[gid + 1] != 53 && App->fade_to_black->IsFading() == false)
	{
		animation = &run;
		is_backwards = false;
		position.x += 100*dt;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->fade_to_black->IsFading() == false)
	{
		if (App->map->data.map_layers.end->data->data[gid] == 51)
			is_jumping = true;
	}
	//JUMP
	if (App->map->prop->jumping_time == 0.0f)
	   App->map->prop->player_position_y0 = - 1 * position.y;


	if (is_jumping)
	{
		App->map->prop->jumping_time += 0.1f;
		
		position.y -= 150*dt;

		if (position.y > App->map->prop->player_position_y0 && App->map->prop->jumping_time >= 1.5f)
		{
			position.y += 70*dt;
			App->map->prop->jumping_time = 0.0f;
			is_jumping = false;
			is_falling = true;
		}
	}
	
	if (is_falling && !is_backwards)
		animation = &fall;

	if (is_falling && is_backwards)
		animation = &fallBackwards;

	if (is_jumping && is_backwards)
		animation = &jumpBackwards;

	if(is_jumping && !is_backwards)
		animation = &jump;

	//TELEPORT
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN && App->map->data.map_layers.end->data->data[gid + 1] == 51 && can_tp)
	{
		is_tp = true;
		App->audio->PlayFx(2); //Teleport fx
	}

	if (is_tp)
	{
		animation = &teleport;
		App->map->prop->tp_time += 0.1f;

		if (App->map->prop->tp_time == 0.6f)
		{
			position.y -= 100;
			is_tp = false;
			App->map->prop->tp_time = 0.0f;
		}
	}

	//GOD MODE  The player can fly and move everywhere and is not affected by gravity
	if (App->scene->is_god)
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			position.y -= 4;

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			position.y += 4;
	}
	

	App->render->camera.x = (-position.x * App->win->render_scale) + (App->win->width / 2);
	App->render->camera.y = (-position.y * App->win->render_scale) + (App->win->height / 2);
//	collider->SetPos(position.x, position.y);
}

bool Entity_Player::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool Entity_Player::CleanUp()
{
	LOG("Unloading player");
	
	App->tex->UnLoad(sprites);
	sprites = nullptr;
	
	App->audio->fx.clear();
	if (collider != nullptr)
	{
		collider->to_delete = true;
		collider = nullptr;
	}

	return true;
}


void Entity_Player::LoadAnimation(pugi::xml_node& animation, Animation* player)
{
	for (pugi::xml_node frame = animation.child("frame"); frame; frame = frame.next_sibling("frame"))
	{
		player->PushBack({frame.attribute("x").as_int(),frame.attribute("y").as_int(),frame.attribute("w").as_int(),frame.attribute("h").as_int()});
		
	}
	player->speed = animation.attribute("speed").as_float();
	player->loop = animation.attribute("loop").as_bool();
}

bool Entity_Player::Load(pugi::xml_node& data)
{
	if(data.child("map") != NULL)
		App->scene->map_number = data.child("map").attribute("level").as_int();

	if (App->scene->map_number == 2 && data.child("map") != NULL)
	{
		App->fade_to_black->FadeToBlack(App->scene, App->scene, 3.0f);
		App->map->CleanUp();
		App->map->Load("ForestMap.tmx");
		position.x = data.child("position").attribute("x").as_int();
		position.y = data.child("position").attribute("y").as_int();
	}
	else if (App->scene->map_number == 1 && data.child("map") != NULL)
	{
		App->fade_to_black->FadeToBlack(App->scene, App->scene, 3.0f);
		App->map->CleanUp();
		App->map->Load("Map2.tmx");
		position.x = data.child("position").attribute("x").as_int();
		position.y = data.child("position").attribute("y").as_int();
	}
	return true;
}

bool Entity_Player::Save(pugi::xml_node& data)const
{
	data.append_child("map").append_attribute("level") = App->scene->map_number;
	data.append_child("position").append_attribute("x") = position.x;
	data.child("position").append_attribute("y") = position.y;
	return true;
}

void Entity_Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_POWER_UP)
	{
		//App->entities->book->CleanUp();
		can_tp = true;
	}
}



