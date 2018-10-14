#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Book.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Scene.h"

#include "j1FadeToBlack.h"



j1Book::j1Book() : j1Module()
{
	name.create("book");

	idle.PushBack({2,13,28,29});
	idle.PushBack({ 0,0,0,0});
	idle.speed = 0.05f;
	idle.loop = true;

	current_animation = &idle;
}

j1Book::~j1Book()
{}


bool j1Book::Start()
{
	bool ret = true;

	graphics = App->tex->Load("textures/Objects.png");

	firstUpdate = true;	
	return ret;
}

bool j1Book::PreUpdate()
{
	bool ret = true;

	return ret;
}

bool j1Book::Update(float dt)
{
	bool ret = true;
	if (firstUpdate == true)
	{
		book_position.x = App->map->spawn_book.x;
		book_position.y = App->map->spawn_book.y;
		book_collider = App->collision->AddCollider({ book_position.x, book_position.y, 28, 25 }, COLLIDER_TYPE::COLLIDER_POWER_UP, this);
		firstUpdate = false;
	}
	
	if(graphics!=nullptr)
	App->render->Blit(graphics, book_position.x, book_position.y, (&current_animation->GetCurrentFrame()));

	return ret;
}

bool j1Book::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool j1Book::CleanUp()
{
	LOG("Unloading book");

	App->tex->UnLoad(graphics);
	if (book_collider != nullptr)
	{
		book_collider->to_delete = true;
		book_collider = nullptr;
	}
	graphics = nullptr;

	return true;
}




void j1Book::OnCollision(Collider* collider)
{
	LOG("COLLISION");
	App->player->can_tp = true;
	CleanUp();
}


