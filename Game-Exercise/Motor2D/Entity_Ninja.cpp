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

#include "j1FadeToBlack.h"
#include "Brofiler\Brofiler.h"
#include "Entity_Player.h"


Entity_Ninja::Entity_Ninja(int x, int y) :Entity(x, y)
{

	sprites = App->tex->Load(App->entities->textures.GetString());
	pugi::xml_document ninja_file;
	pugi::xml_node ninja;
	ninja = App->LoadEntities(ninja_file, Entities::NINJA_ENTITY);

	path = ninja.child("folder").attribute("path").as_string();

	for (pugi::xml_node animations = ninja.child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		p2SString name = animations.attribute("name").as_string();
		if (name == "idle")
			LoadAnimation(animations, &idle);
	}

	animation = &idle;
}

Entity_Ninja::~Entity_Ninja() 
{
	CleanUp();
}

bool Entity_Ninja::PreUpdate()
{
	BROFILER_CATEGORY("EntityNinjaPreUpdate", Profiler::Color::Azure);
	bool ret = true;

	return ret;
}

void Entity_Ninja::Update(float dt)
{
	BROFILER_CATEGORY("EntityNinjaUpdate", Profiler::Color::PowderBlue);
	if (firstUpdate == true) {
		sprites = App->tex->Load("textures/Enemy_Ninja.png");
		collider = App->collision->AddCollider({ 0, 0, 33, 47 }, COLLIDER_TYPE::COLLIDER_ENEMY, App->entities);
		firstUpdate = false;
	}
}

bool Entity_Ninja::PostUpdate()
{
	BROFILER_CATEGORY("EntityNinjaPostUpdate", Profiler::Color::Ivory);
	bool ret = true;
	return ret;
}

bool Entity_Ninja::CleanUp()
{
	LOG("Unloading ninja");

	App->tex->UnLoad(sprites);
	if (App->entities->ninja->collider != nullptr)
	{
		App->entities->ninja->collider->to_delete = true;
		App->entities->ninja->collider = nullptr;
	}
	sprites = nullptr;

	return true;
}

void Entity_Ninja::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_TYPE::COLLIDER_PLAYER) {
		LOG("COLLISION");
		App->entities->ninja->CleanUp();
	}
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
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	return true;
}

bool Entity_Ninja::Save(pugi::xml_node& data)const
{
	data.append_child("position").append_attribute("x") = position.x;
	data.child("position").append_attribute("y") = position.y;

	return true;
}