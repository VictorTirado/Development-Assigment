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
#include "j1Particles.h"
#include "j1Pathfinding.h"
#include "Entity_Gaara.h"
#include "j1Gui.h"
#include "Entity_Book.h"
#include "Brofiler\Brofiler.h"

Entity_Gaara::Entity_Gaara(int x, int y):Entity(x, y)
{
	sprites = App->tex->Load(App->entities->textures.GetString());
	pugi::xml_document gaara_file;
	pugi::xml_node gaara;

	gaara = App->LoadEntities(gaara_file, Entities::GAARA_ENTITY);
	path = gaara.child("folder").attribute("path").as_string();

	for (pugi::xml_node animations = gaara.child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		p2SString name = animations.attribute("name").as_string();
		if (name == "idle")
			LoadAnimation(animations, &idle);
	}
}

Entity_Gaara::~Entity_Gaara()
{
	App->tex->UnLoad(sprites);
	sprites = nullptr;
}

void Entity_Gaara::Update(float dt)
{
	animation = &idle;
	gaara_pos = App->map->WorldToMap(position.x, position.y);

	if (firstUpdate == true)
	{
		firstUpdate = false;
	}


	//LOGIC
	gid = App->map->Get_gid(position.x + 10, position.y + 51);

	if (App->map->data.map_layers.end->data->data[gid + 1] != Collision_Type::COLLISION_CHANGE_MAP || App->map->data.map_layers.end->data->data[gid] == Collision_Type::COLLISION_DEATH)
	{
		if (App->map->data.map_layers.end->data->data[gid + 1] != Collision_Type::COLLISION_WALL && App->map->data.map_layers.end->data->data[gid] != Collision_Type::COLLISION_WALL)
		{
			position.y += 70 * dt;
		}
	}

	if (App->map->data.map_layers.end->data->data[gid] == Collision_Type::COLLISION_DEATH)
	{
		App->map->CleanUp();
		App->entities->DestroyEntities();
		if (App->scene->map_number == 1)
		{
			App->map->Load("Map4.tmx");
			App->map->Spawn();
		}

		else if (App->scene->map_number == 2)
		{
			App->map->Load("ForestMap.tmx");
			App->map->Spawn();
		}
		App->fade_to_black->FadeToBlack(App->scene, App->entities, 3.0f);

	}

	if (App->map->data.map_layers.end->data->data[gid] == Collision_Type::COLLISION_CHANGE_MAP)
	{

		App->map->CleanUp();
		App->entities->DestroyEntities();
		if (App->scene->map_number == 1)
		{
			if (App->map->Load("ForestMap.tmx"))
			{
				App->map->Spawn();

				int w, h;
				uchar* data = NULL;
				if (App->map->CreateWalkabilityMap(w, h, &data))
					App->pathfinding->SetMap(w, h, data);

				RELEASE_ARRAY(data);

			}
			App->scene->map_number = 2;
			firstUpdate = true;
		}
		else if (App->scene->map_number == 2)
		{
			if (App->map->Load("Map4.tmx"))
			{
				App->map->Spawn();

				int w, h;
				uchar* data = NULL;
				if (App->map->CreateWalkabilityMap(w, h, &data))
					App->pathfinding->SetMap(w, h, data);

				RELEASE_ARRAY(data);

			}
			App->scene->map_number = 1;
			firstUpdate = true;
		}

		App->fade_to_black->FadeToBlack(App->scene, App->entities, 3.0f);
	}
	//MOVEMENT PLAYER
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->map->data.map_layers.end->data->data[gid - 1] != COLLISION_FLOOR && App->fade_to_black->IsFading() == false)
	{
		
		position.x -= 80 * dt;
	}
	
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->map->data.map_layers.end->data->data[gid + 1] != COLLISION_FLOOR && App->fade_to_black->IsFading() == false)
	{
		
		position.x += 100 * dt;
	}
	/*
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->fade_to_black->IsFading() == false)
	{
		if (App->map->data.map_layers.end->data->data[gid] == 51)
			is_jumping = true;
	}*/

	//DEBUG KEY FOR TP
	//if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
	//	can_tp = true;

	////THROW KUNAI
	//if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
	//	is_shooting = true;


	//if (is_shooting)
	//{
	//	App->audio->PlayFx(3);
	//	if (is_backwards)
	//	{
	//		animation = &throwKunaiBackwards;
	//		App->particles->kunai_particle_backwards.speed.x = -800 * dt;
	//		App->particles->AddParticle(App->particles->kunai_particle_backwards, position.x, position.y + 20, COLLIDER_PLAYER_SHOT);
	//	}

	//	else
	//	{
	//		animation = &throwKunai;
	//		App->particles->kunai_particle.speed.x = 800 * dt;
	//		App->particles->AddParticle(App->particles->kunai_particle, position.x + 12, position.y + 20, COLLIDER_PLAYER_SHOT);
	//	}
	//	is_shooting = false;
	//}

	//if (!is_shooting)
	//{
	//	throwKunaiBackwards.Reset();
	//	throwKunai.Reset();
	//}

	////JUMP
	//if (!is_jumping)
	//{
	//	old_player_position.y = position.y;
	//	velocity.y = 0;
	//}


	//if (is_jumping)
	//{
	//	velocity.y = -200 * dt;

	//	if (position.y < old_player_position.y - 60)
	//	{
	//		velocity.y = 1 * dt;
	//		is_jumping = false;
	//	}

	//}
	//velocity.y += App->map->prop->gravity;
	//position.y += velocity.y;

	//if (is_falling && !is_backwards)
	//	animation = &fall;

	//if (is_falling && is_backwards)
	//	animation = &fallBackwards;

	//if (is_jumping && is_backwards)
	//	animation = &jumpBackwards;

	//if (is_jumping && !is_backwards)
	//	animation = &jump;

	////TELEPORT
	//if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN && App->map->data.map_layers.end->data->data[gid + 1] == 51 && can_tp)
	//{
	//	is_tp = true;
	//	App->audio->PlayFx(2); //Teleport fx
	//}

	//if (is_tp)
	//{
	//	animation = &teleport;
	//	App->map->prop->tp_time += 0.1f;

	//	if (App->map->prop->tp_time == 0.6f)
	//	{
	//		position.y -= 100;
	//		is_tp = false;
	//		App->map->prop->tp_time = 0.0f;
	//	}
	//}

	////GOD MODE  The player can fly and move everywhere and is not affected by gravity
	//if (App->scene->is_god)
	//{
	//	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && App->fade_to_black->IsFading() == false)
	//		position.y -= 120 * dt;

	//	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && App->fade_to_black->IsFading() == false)
	//		position.y += 120 * dt;
	//}

	App->render->camera.x = (-position.x * App->win->render_scale) + (App->win->width / 2);
	App->render->camera.y = (-position.y * App->win->render_scale) + (App->win->height / 2);
}

void Entity_Gaara::LoadAnimation(pugi::xml_node& animation, Animation* player)
{
	for (pugi::xml_node frame = animation.child("frame"); frame; frame = frame.next_sibling("frame"))
	{
		player->PushBack({ frame.attribute("x").as_int(),frame.attribute("y").as_int(),frame.attribute("w").as_int(),frame.attribute("h").as_int() });

	}
	player->speed = animation.attribute("speed").as_float();
	player->loop = animation.attribute("loop").as_bool();
}