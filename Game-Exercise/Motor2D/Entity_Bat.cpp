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

#include "Entity_Player.h"


Entity_Bat::Entity_Bat(int x, int y):Entity(x, y)
{
	sprites = App->tex->Load(App->entities->textures.GetString());
	pugi::xml_document bat_file;
	pugi::xml_node bat;
	bat = App->LoadEntities(bat_file, Entities::BAT_ENTITY);

	path = bat.child("folder").attribute("path").as_string();

	for (pugi::xml_node animations = bat.child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		p2SString name = animations.attribute("name").as_string();
		if (name == "idle")
			LoadAnimation(animations, &idle);
	}

	animation = &idle;
}

Entity_Bat::~Entity_Bat(){}

bool Entity_Bat::PreUpdate()
{
	bool ret = true;

	return ret;
}

void Entity_Bat::Update(float dt)
{
	if (firstUpdate == true) {
		sprites = App->tex->Load("textures/Bat.png");
		X = App->tex->Load("textures/x.png");
		original_pos= App->map->WorldToMap(position.x, position.y);
		collider = App->collision->AddCollider({ 0, 0, 29, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, App->entities);
		firstUpdate = false;
	}
	iPoint bat_pos = App->map->WorldToMap(position.x, position.y);
	iPoint player_pos = App->entities->player->player_pos;
	player_pos.x += 1;
	player_pos.y -= 1;
	if (original_pos.x < player_pos.x + range && original_pos.x > player_pos.x - range && original_pos.y < player_pos.y + range && original_pos.y > player_pos.y - range) {
		if (App->pathfinding->CreatePath(bat_pos, player_pos) != -1)
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
					speed.x = -1;

				}
				else if (path_to_follow.x > bat_pos.x)
				{
					speed.x = 1;
				}
				if (path_to_follow.y < bat_pos.y)
				{
					speed.y = -1;
				}
				if (path_to_follow.y > bat_pos.y)
				{
					speed.y = +1;
				}
			}
		}
	}
	else if (bat_pos != original_pos)
	{
		if (App->pathfinding->CreatePath(bat_pos, original_pos) != -1)
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
					speed.x = -1;

				}
				else if (path_to_follow.x > bat_pos.x)
				{
					speed.x = 1;
				}
				if (path_to_follow.y < bat_pos.y)
				{
					speed.y = -1;
				}
				if (path_to_follow.y > bat_pos.y)
				{
					speed.y = +1;
				}
			}
		}
	}
	position += speed;
}

bool Entity_Bat::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool Entity_Bat::CleanUp()
{
	LOG("Unloading bat");

	/*App->tex->UnLoad(sprites);
	if (App->entities->bat->collider != nullptr)
	{
		App->entities->bat->collider->to_delete = true;
		App->entities->bat->collider = nullptr;
	}
	sprites = nullptr;*/

	return true;
}

void Entity_Bat::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_TYPE::COLLIDER_PLAYER) {
		LOG("COLLISION");
		App->entities->bat->CleanUp();
	}
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
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	return true;
}

bool Entity_Bat::Save(pugi::xml_node& data)const
{
	data.append_child("position").append_attribute("x") = position.x;
	data.child("position").append_attribute("y") = position.y;

	return true;
}