#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "Entity_Ninja.h"

#include "j1Window.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Entitites.h"
#include "j1Scene.h"
#include "j1Pathfinding.h"

#include "j1FadeToBlack.h"
#include "Brofiler\Brofiler.h"
#include "Entity_Player.h"


Entity_Ninja::Entity_Ninja(int x, int y) :Entity(x, y)
{

	sprites = App->tex->Load("textures/Enemy_Ninja.png");
	pugi::xml_document ninja_file;
	pugi::xml_node ninja;
	ninja = App->LoadEntities(ninja_file, Entities::NINJA_ENTITY);

	path = ninja.child("folder").attribute("path").as_string();

	for (pugi::xml_node animations = ninja.child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		p2SString name = animations.attribute("name").as_string();
		if (name == "idle")
			LoadAnimation(animations, &idle);
		if (name == "idleRight")
			LoadAnimation(animations, &idleRight);
		if (name == "runLeft")
			LoadAnimation(animations, &runLeft);
		if (name == "runRight")
			LoadAnimation(animations, &runRight);
	}

	animation = &idle;

}

Entity_Ninja::~Entity_Ninja() 
{
	App->tex->UnLoad(sprites);
	sprites = nullptr;
	X = nullptr;
}


void Entity_Ninja::Update(float dt)
{
	BROFILER_CATEGORY("EntityNinjaUpdate", Profiler::Color::PowderBlue);
	if (firstUpdate == true) {
		lives = 2;
		collider = App->collision->AddCollider({ 0, 0, 30, 45 }, COLLIDER_TYPE::COLLIDER_ENEMY, App->entities);
		X = App->tex->Load("textures/x.png");
		original_pos = App->map->WorldToMap(position.x, position.y);
		firstUpdate = false;
	}

	ninja_pos = App->map->WorldToMap(position.x, position.y);
	//player_pos = App->entities->player->player_pos;
	player_pos.y += 1;
	gid = App->map->Get_gid(position.x + 10, position.y + 35);
	App->render->DrawQuad({ position.x + 10,position.y + 35,16,16 }, 0, 0, 255, 255);

	if (App->map->data.map_layers.end->data->data[gid + 1] != 51 && App->map->data.map_layers.end->data->data[gid] != 51)
		position.y += 70 * dt;
	

	if (Radar() == true) {
		if (App->pathfinding->CreatePath(ninja_pos, player_pos,NINJA) != -1)
		{
			const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
			if (App->scene->collision_debug == true)
			{
				// SEE THE PATH
				for (int i = 0; i < path->Count(); ++i)
				{
					iPoint x_pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
					App->render->Blit(X, x_pos.x, x_pos.y);
				}
			}
			if (path->Count() > 0)
			{
				path_to_follow = iPoint(path->At(0)->x, path->At(0)->y);
				if (path_to_follow.x < ninja_pos.x  )
				{
					animation = &runLeft;
					speed.x = -60 * dt;

				}
				else if (path_to_follow.x > ninja_pos.x  && App->map->data.map_layers.end->data->data[gid + 1] != 53)
				{
					animation = &runRight;
					speed.x = 60 * dt;
				}
				/*if (path_to_follow.y < ninja_pos.y)
				{
					speed.y = -60 * dt;
				}
				if (path_to_follow.y > ninja_pos.y)
				{
					speed.y = +60 * dt;
				}*/
			}

		}
	}
	else if (ninja_pos != original_pos)
	{
		if (App->pathfinding->CreatePath(ninja_pos, original_pos,NINJA) != -1 && App->fade_to_black->IsFading() == false)
		{
			const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
			if (App->collision->debug == true)
			{
				for (int i = 0; i < path->Count(); ++i)
				{
					iPoint x_pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
					App->render->Blit(X, x_pos.x, x_pos.y);
				}
			}
			if (path->Count() > 0)
			{
				path_to_follow = iPoint(path->At(0)->x, path->At(0)->y);
				if (path_to_follow.x < ninja_pos.x  && App->map->data.map_layers.end->data->data[gid + 1] != 53 && App->map->data.map_layers.end->data->data[gid - 1] != 53)
				{
					animation = &runLeft;
					speed.x = -60 * dt;

				}
				else if (path_to_follow.x > ninja_pos.x && App->map->data.map_layers.end->data->data[gid + 1] != 53 && App->map->data.map_layers.end->data->data[gid - 1] != 53)
				{
					animation = &runRight;
					speed.x = 60 * dt;
				}
			/*	if (path_to_follow.y < ninja_pos.y)
				{
					speed.y = -60 * dt;
				}
				if (path_to_follow.y > ninja_pos.y)
				{
					speed.y = +60 * dt;
				}*/
			}
		}
	}
	position += speed;

}



void Entity_Ninja::OnCollision(Collider* collider)
{
	if (App->scene->is_god == false)
	{
		if (collider->type == COLLIDER_TYPE::COLLIDER_PLAYER && damage_cd == 0)
		{
			App->entities->HurtingPlayer();
			App->entities->UpdatePlayerLifes(App->entities->playerLifes);
		}
		if (collider->type == COLLIDER_TYPE::COLLIDER_PLAYER && App->entities->playerLifes == 0)
		App->entities->ResetMap(App->scene->map_number);

		else if (collider->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT)
			lives--;
	}

	damage_cd += 1;
	if (damage_cd == 50)
		damage_cd = 0;

	if (lives <= 0)
		delete_entity = true;

}

void Entity_Ninja::LoadAnimation(pugi::xml_node& animation, Animation* ninja)
{
	for (pugi::xml_node frame = animation.child("frame"); frame; frame = frame.next_sibling("frame"))
	{
		ninja->PushBack({ frame.attribute("x").as_int(),frame.attribute("y").as_int(),frame.attribute("w").as_int(),frame.attribute("h").as_int() });

	}
	ninja->speed = animation.attribute("speed").as_float();
	ninja->loop = animation.attribute("loop").as_bool();
}

bool Entity_Ninja::Load(pugi::xml_node& data)
{
	if (data.child("position") != NULL)
	{
		position.x = data.child("position").attribute("x").as_int();
		position.y = data.child("position").attribute("y").as_int();
	}
	return true;
}

bool Entity_Ninja::Save(pugi::xml_node& data)const
{
	data.append_child("position").append_attribute("x") = position.x;
	data.child("position").append_attribute("y") = position.y;

	return true;
}

bool Entity_Ninja::Radar()
{
	return (original_pos.x < player_pos.x + range && original_pos.x > player_pos.x - range && original_pos.y < player_pos.y + range && original_pos.y > player_pos.y - range);
}