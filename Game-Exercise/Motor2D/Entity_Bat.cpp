#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "Entity_Bat.h"
#include "j1Window.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Entitites.h"
#include "j1Scene.h"
#include "j1Pathfinding.h"

#include "j1FadeToBlack.h"
#include "Brofiler\Brofiler.h"
#include "Entity_Player.h"


Entity_Bat::Entity_Bat(int x, int y):Entity(x, y)
{
	sprites = App->tex->Load("textures/Bat.png");
	pugi::xml_document bat_file;
	pugi::xml_node bat;
	bat = App->LoadEntities(bat_file, Entities::BAT_ENTITY);

	path = bat.child("folder").attribute("path").as_string();

	for (pugi::xml_node animations = bat.child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		p2SString name = animations.attribute("name").as_string();
		if (name == "idle")
			LoadAnimation(animations, &idle);
		if (name == "idleRight")
			LoadAnimation(animations, &idleRight);
	}

	animation = &idle;
}

Entity_Bat::~Entity_Bat()
{
	App->tex->UnLoad(sprites);
	sprites = nullptr;
	X = nullptr;
}


void Entity_Bat::Update(float dt)
{
	BROFILER_CATEGORY("EntityBatUpdate", Profiler::Color::Maroon);
	if (firstUpdate == true)
	{
		lives = 1;
		X = App->tex->Load("textures/x.png");
		original_pos= App->map->WorldToMap(position.x, position.y);
		collider = App->collision->AddCollider({ 0, 0, 29, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, App->entities);
		firstUpdate = false;
	}

	bat_pos = App->map->WorldToMap(position.x, position.y);
	player_pos = App->entities->player->player_pos;
	player_pos.x += 1;
	player_pos.y -= 1;

	if (Radar() == false && original_pos == bat_pos)
	{
		animation = &idle;
		speed.x = 0;
		speed.y = 0;
	}
	if (Radar() == true) {
		if (App->pathfinding->CreatePath(bat_pos, player_pos,BAT) != -1 && App->fade_to_black->IsFading() == false)
		{
			const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
			if (App->scene->collision_debug == true)
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
				if (path_to_follow.x < bat_pos.x)
				{
					animation = &idle;
					speed.x = -60 * dt;
				}
				else if (path_to_follow.x > bat_pos.x)
				{
					animation = &idleRight;
					speed.x = 60 * dt;
				}
				if (path_to_follow.y < bat_pos.y)
				{
					speed.y = -60 * dt;
				}
				else if (path_to_follow.y > bat_pos.y)
				{
					speed.y = +60 * dt;
				}
			}
		}
	}
	else if (bat_pos != original_pos)
	{
		if (App->pathfinding->CreatePath(bat_pos, original_pos,BAT) != -1)
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
				if (path_to_follow.x < bat_pos.x)
				{
					animation = &idle;
					speed.x = -60 * dt;

				}
				else if (path_to_follow.x > bat_pos.x)
				{
						animation = &idleRight;
					speed.x = 60 * dt;
				}
				if (path_to_follow.y < bat_pos.y)
				{
					speed.y = -60 * dt;
				}
				if (path_to_follow.y > bat_pos.y)
				{
					speed.y = +60 * dt;
				}
			}
		}
	}
	position += speed;
}





void Entity_Bat::OnCollision(Collider* collider)
{
	if (App->scene->is_god == false)
	{
		if(collider->type == COLLIDER_TYPE::COLLIDER_PLAYER && damage_cd == 0)
			App->entities->player->HurtPlayer();

		if (collider->type == COLLIDER_TYPE::COLLIDER_PLAYER && App->entities->player->player_lifes == 0)
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

void Entity_Bat::LoadAnimation(pugi::xml_node& animation, Animation* bat)
{
	for (pugi::xml_node frame = animation.child("frame"); frame; frame = frame.next_sibling("frame"))
	{
		bat->PushBack({ frame.attribute("x").as_int(),frame.attribute("y").as_int(),frame.attribute("w").as_int(),frame.attribute("h").as_int() });

	}
	bat->speed = animation.attribute("speed").as_float();
	bat->loop = animation.attribute("loop").as_bool();
}

bool Entity_Bat::Load(pugi::xml_node& data)
{
	if (data.child("position") != NULL)
	{
		position.x = data.child("position").attribute("x").as_int();
		position.y = data.child("position").attribute("y").as_int();
	}
	return true;
}

bool Entity_Bat::Save(pugi::xml_node& data)const
{
	data.append_child("position").append_attribute("x") = position.x;
	data.child("position").append_attribute("y") = position.y;

	return true;
}

bool Entity_Bat::Radar()
{
	return (original_pos.x < player_pos.x + range && original_pos.x > player_pos.x - range && original_pos.y < player_pos.y + range && original_pos.y > player_pos.y - range);
}