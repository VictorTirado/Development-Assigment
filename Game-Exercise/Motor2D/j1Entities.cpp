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
#include "Entity_Ninja.h"

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
	App->map->Spawn();


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
	DestroyEntities();
	
	return true;
}
void j1Entities::DestroyEntities()
{
	for (uint i = 0; i < entities.Count(); i++)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->collider->to_delete = true;
			delete entities[i];
			entities[i] = nullptr;
		}
	}
	entities.Clear();
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

	case Entities_Type::NINJA: {
		ninja = new Entity_Ninja(x, y);
		ninja->entity_type = Entities_Type::NINJA;
		entities.PushBack(ninja);
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



	for (int i = 0; i < entities.Count(); i++)
	{
		if (entities[i]->entity_type == PLAYER)
		{
			pugi::xml_node player_stats = data.child("player");
			entities[i]->Load(player_stats);
		}
		if (entities[i]->entity_type == NINJA)
		{
			pugi::xml_node ninja_stats = data.child("ninja");
			entities[i]->Load(ninja_stats);
		}
		if (entities[i]->entity_type == BAT)
		{
			pugi::xml_node bat_stats = data.child("bat");
			entities[i]->Load(bat_stats);
		}
		if (entities[i]->entity_type == BOOK)
		{
			pugi::xml_node book_stats = data.child("book");
			entities[i]->Load(book_stats);
		}

	}
	

	return ret;
}

bool j1Entities::Save(pugi::xml_node& data)const
{
	bool ret = true;

	
	for (int i = 0; i < entities.Count(); i++)
	{
		if (entities[i]->entity_type == PLAYER)
		{
			pugi::xml_node player_stats = data.append_child("player");
			entities[i]->Save(player_stats);
		}
		if (entities[i]->entity_type == NINJA)
		{
			pugi::xml_node ninja_stats = data.append_child("ninja");
			entities[i]->Save(ninja_stats);
		}
		if (entities[i]->entity_type == BAT)
		{
			pugi::xml_node bat_stats = data.append_child("bat");
			entities[i]->Save(bat_stats);
		}
		if (entities[i]->entity_type == BOOK)
		{
			pugi::xml_node book_stats = data.append_child("book");
			entities[i]->Save(book_stats);
		}
	}

	return ret;
}


