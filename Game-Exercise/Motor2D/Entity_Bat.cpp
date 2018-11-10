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
		/*position.x = 400;
		position.y = 700;*/
		collider = App->collision->AddCollider({ 0, 0, 29, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, App->entities);
		firstUpdate = false;
	}
}

bool Entity_Bat::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool Entity_Bat::CleanUp()
{
	LOG("Unloading bat");

	App->tex->UnLoad(sprites);
	if (App->entities->bat->collider != nullptr)
	{
		App->entities->bat->collider->to_delete = true;
		App->entities->bat->collider = nullptr;
	}
	sprites = nullptr;

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