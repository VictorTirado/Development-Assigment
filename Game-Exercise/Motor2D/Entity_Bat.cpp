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
#include "j1Input.h"
#include "j1Window.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Entitites.h"
#include "j1Scene.h"

#include "j1FadeToBlack.h"

#include "Entity_Player.h"


Entity_Bat::Entity_Bat(int x, int y):Entity(x, y)
{
	idle.PushBack({ 213,40,26,35 });
	idle.PushBack({ 0,0,0,0 });
	idle.speed = 0.05f;
	idle.loop = true;

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
		position.x = 100;
		position.y = 100;
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
	LOG("Unloading book");

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