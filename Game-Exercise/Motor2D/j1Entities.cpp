#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Entitites.h"
#include "Entity.h"
#include "j1FadeToBlack.h"

#include "Entity_Player.h"
#include "Entity_Book.h"
#include "Entity_Bat.h"

j1Entities::j1Entities() : j1Module()
{
	name.create("entities");

}

j1Entities::~j1Entities()
{}


bool j1Entities::Awake(pugi::xml_node& config)
{
	textures = config.child("folder").attribute("path").as_string();
	bool ret = true;
	return ret;
}

bool j1Entities::Start()
{
	bool ret = true;
	SpawnEntities(0, 0, PLAYER);
	SpawnEntities(0, 0, BOOK);
	SpawnEntities(0, 0, BAT);

	return ret;
}

bool j1Entities::PreUpdate()
{
	bool ret = true;
	
	return ret;
}

bool j1Entities::Update(float dt)
{
	for (uint i = 0; i < entities.Count(); i++)
	{
		if (entities.At(i) != nullptr)
			entities[i]->Update(dt);
	}
	for (uint i = 0; i < entities.Count(); i++)
	{
		if (entities[i] != nullptr)
			entities[i]->Draw(entities[i]->sprites);
	}
	
	bool ret = true;
	
	return ret;
}

bool j1Entities::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool j1Entities::CleanUp()
{
	App->entities->player->CleanUp();
	return true;
}

bool j1Entities::SpawnEntities(int x, int y, Entities_Type type)
{
	bool ret = false;
	switch (type)
	{
	case Entities_Type::PLAYER: {
		player = new Entity_Player(x, y);
		player->entity_type = Entities_Type::PLAYER;
		entities.PushBack(player);
		ret = true;
		break;
	}
	case Entities_Type::BOOK: {
		book = new Entity_Book(x, y);
		book->entity_type = Entities_Type::BOOK;
		entities.PushBack(book);
		ret = true;
		break;
	}
	case Entities_Type::BAT: {
		bat = new Entity_Bat(x, y);
		bat->entity_type = Entities_Type::BAT;
		entities.PushBack(bat);
		ret = true;
		break;
	}

	}

	return true;
}


void j1Entities::OnCollision(Collider* c1, Collider* c2)
{
	
	for(int i =0 ;i<entities.Count();i++)
	{
		if(entities[i]->GetCollider() == c1)
		entities[i]->OnCollision(c2); 
	}

}


bool j1Entities::Load(pugi::xml_node& data)
{
	bool ret = true;
	if (data.child("map") != NULL)
		App->scene->map_number = data.child("map").attribute("level").as_int();

	if (App->scene->map_number == 2 && data.child("map") != NULL)
	{
		App->fade_to_black->FadeToBlack(App->scene, App->scene, 3.0f);
		App->map->CleanUp();
		App->map->Load("ForestMap.tmx");
		App->entities->player->position.x = data.child("position").attribute("x").as_int();
		App->entities->player->position.y = data.child("position").attribute("y").as_int();
	}
	else if (App->scene->map_number == 1 && data.child("map") != NULL)
	{
		App->fade_to_black->FadeToBlack(App->scene, App->scene, 3.0f);
		App->map->CleanUp();
		App->map->Load("Map2.tmx");
		App->entities->player->position.x = data.child("position").attribute("x").as_int();
		App->entities->player->position.y = data.child("position").attribute("y").as_int();
	}
	

	return ret;
}

bool j1Entities::Save(pugi::xml_node& data)const
{
	bool ret = true;

	data.append_child("map").append_attribute("level") = App->scene->map_number;
	data.append_child("position").append_attribute("x") = App->entities->player->position.x;
	data.child("position").append_attribute("y") = App->entities->player->position.y;


	return ret;
}
