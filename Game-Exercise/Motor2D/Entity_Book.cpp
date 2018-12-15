#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "Entity_Book.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Entitites.h"
#include "j1Scene.h"
#include "j1Gui.h"
#include "j1FadeToBlack.h"
#include "GUI_Image.h"
#include "Entity_Player.h"
#include "Entity_Gaara.h"



Entity_Book::Entity_Book(int x, int y) : Entity(x, y)
{
	
	idle.PushBack({2,13,28,29});
	idle.PushBack({ 0,0,0,0});
	idle.speed = 0.05f;
	idle.loop = true;

	animation = &idle;
	
	
}

Entity_Book::~Entity_Book()
{
	App->tex->UnLoad(sprites);
}





void Entity_Book::Update(float dt)
{

	if (firstUpdate == true) {
		sprites = App->tex->Load("textures/Objects.png");
		collider = App->collision->AddCollider({ 0, 0, 28, 25 }, COLLIDER_TYPE::COLLIDER_POWER_UP, App->entities);
		firstUpdate = false;
	}

}




void Entity_Book::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_TYPE::COLLIDER_PLAYER) {
		LOG("COLLISION");
		if (App->entities->player != nullptr)
		{
			App->entities->player->can_tp = true;
		}
		else if (App->entities->gaara != nullptr)
		{
			App->entities->gaara->can_tp = true;
		}
		is_caught = true;
		delete_entity = true;
		UpdateBookUI(is_caught);
	}
}


bool Entity_Book::Load(pugi::xml_node& data)
{
	App->entities->player->can_tp = data.child("book").attribute("caught").as_bool();
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	return true;
}

bool Entity_Book::Save(pugi::xml_node& data)const
{
	data.append_child("book").append_attribute("caught") = App->entities->player->can_tp;
	data.append_child("position").append_attribute("x") = position.x;
	data.child("position").append_attribute("y") = position.y;

	return true;
}

void Entity_Book::UpdateBookUI(bool book_caught)
{
	if(book_caught)
		App->scene->book_caught_ui = App->gui->AddImage(200, 20, &App->scene->book_caught_rect, nullptr,nullptr, nullptr);

	if(!book_caught)
		App->scene->book_caught_ui = App->gui->AddImage(200, 20, &App->scene->book_not_caught_rect, nullptr,nullptr, nullptr);
}

