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

#include "Entity_Player.h"


Entity_Ninja::Entity_Ninja(int x, int y) :Entity(x, y)
{
	idle.PushBack({ 4,1,33,47 });
	idle.PushBack({ 0,0,0,0 });
	idle.speed = 0.05f;
	idle.loop = true;

	animation = &idle;
}

Entity_Ninja::~Entity_Ninja() {}

bool Entity_Ninja::PreUpdate()
{
	bool ret = true;

	return ret;
}

void Entity_Ninja::Update(float dt)
{
	if (firstUpdate == true) {
		sprites = App->tex->Load("textures/Enemy_Ninja.png");
		position.x = 200;
		position.y = 100;
		collider = App->collision->AddCollider({ 0, 0, 33, 47 }, COLLIDER_TYPE::COLLIDER_ENEMY, App->entities);
		firstUpdate = false;
	}
}

bool Entity_Ninja::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool Entity_Ninja::CleanUp()
{
	LOG("Unloading book");

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