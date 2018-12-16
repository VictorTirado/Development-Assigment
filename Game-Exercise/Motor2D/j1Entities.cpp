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
#include "SelectCharacter.h"
#include "j1Entitites.h"
#include "Entity.h"
#include "j1FadeToBlack.h"
#include "Brofiler\Brofiler.h"
#include "Entity_Player.h"
#include "Entity_Book.h"
#include "Entity_Bat.h"
#include "Entity_Ninja.h"
#include "Entity_Gaara.h"
#include "GUI_Image.h"
#include "GUI_Label.h"
#include "MainMenu.h"

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
	return ret;
}

bool j1Entities::PreUpdate()
{
	bool ret = true;
	for (uint i = 0; i < entities.Count(); i++)
	{
		if (entities[i]->delete_entity == true)
		{		
				delete (entities[i]);
				entities[i] = nullptr;
				entities.Pop(entities[i]);
		}
	}
	
	
	return ret;
}

bool j1Entities::Update(float dt)
{
	BROFILER_CATEGORY("ModuleEntitiesUpdate", Profiler::Color::LawnGreen);

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
	BROFILER_CATEGORY("ModuleEntitiesPostUpdate", Profiler::Color::Chartreuse);

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
			delete entities[i];
			entities[i] = nullptr;
			entities.Pop(entities[i]);
		}
	}
	entities.Clear();
}

bool j1Entities::SpawnEntities(int x, int y, Entities_Type type)
{
	BROFILER_CATEGORY("ModuleEntitiesSpawnEntitiesFunction", Profiler::Color::Gainsboro);

	bool ret = false;
	switch (type)
	{
	case Entities_Type::PLAYER: {
		player = new Entity_Player(x, y);
		player->entity_type = Entities_Type::PLAYER;
		entities.PushBack(player);
		playerLifes = 4;
		ret = true;
		break;
	}
	case Entities_Type::GAARA_PLAYER: {
		gaara = new Entity_Gaara(x, y);
		gaara->entity_type = Entities_Type::GAARA_PLAYER;
		entities.PushBack(gaara);
		playerLifes = 4;
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
		if (entities[i]->entity_type == Entities_Type::PLAYER || App->characters->type == 1)
		{
			pugi::xml_node player_stats = data.child("player");
			entities[i]->Load(player_stats);
		}
		if (entities[i]->entity_type == Entities_Type::GAARA_PLAYER || App->characters->type == 2)
		{
			pugi::xml_node player_stats = data.child("player");
			entities[i]->Load(player_stats);
		}
		if (entities[i]->entity_type == Entities_Type::NINJA)
		{
			pugi::xml_node ninja_stats = data.child("ninja");
			entities[i]->Load(ninja_stats);
		}
		if (entities[i]->entity_type == Entities_Type::BAT)
		{
			pugi::xml_node bat_stats = data.child("bat");
			entities[i]->Load(bat_stats);
		}
		if (entities[i]->entity_type == Entities_Type::BOOK)
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
		if (entities[i]->entity_type == Entities_Type::PLAYER )
		{
			pugi::xml_node player_stats = data.append_child("player");
			entities[i]->Save(player_stats);
		}
		if (entities[i]->entity_type == Entities_Type::GAARA_PLAYER)
		{
			pugi::xml_node player_stats = data.append_child("player");
			entities[i]->Save(player_stats);
		}
		if (entities[i]->entity_type == Entities_Type::NINJA)
		{
			pugi::xml_node ninja_stats = data.append_child("ninja");
			entities[i]->Save(ninja_stats);
		}
		if (entities[i]->entity_type == Entities_Type::BAT)
		{
			pugi::xml_node bat_stats = data.append_child("bat");
			entities[i]->Save(bat_stats);
		}
		if (entities[i]->entity_type == Entities_Type::BOOK)
		{
			pugi::xml_node book_stats = data.append_child("book");
			entities[i]->Save(book_stats);
		}
	}

	return ret;
}
void j1Entities::ResetMap(int map)
{
	App->map->CleanUp();
	if (App->scene->map_number == 1)
	{
		App->map->Load("Map4.tmx");
	}
	else if (App->scene->map_number == 2)
	{
		App->map->Load("ForestMap.tmx");
	}
	App->entities->DestroyEntities();
	App->fade_to_black->FadeToBlack(App->scene, App->entities, 3.0f);
	App->map->Spawn();
}

void j1Entities::UpdatePlayerLifes(int lifes)
{
	if (lifes == 4)
		App->scene->hearts = (GUI_Image*)App->gui->AddImage(20, 20, &App->scene->hearts3, nullptr, App->scene, nullptr); 

	if(lifes == 3)
		App->scene->hearts = App->gui->AddImage(20, 20, &App->scene->hearts2, nullptr, App->scene, nullptr);

	if(lifes == 2)
		App->scene->hearts = App->gui->AddImage(20, 20, &App->scene->hearts1, nullptr, App->scene, nullptr);

	if(lifes == 1)
		App->scene->hearts = App->gui->AddImage(20, 20, &App->scene->hearts0, nullptr, App->scene, nullptr);

	if (lifes == 0) {
		App->fade_to_black->FadeToBlack(App->scene, App->main_menu, 3.0f);
		App->map->CleanUp();
		App->gui->DestroyAllUi();
		App->scene->active = false;
		App->main_menu->active = true;
		App->main_menu->Start();
		App->scene->first_update = true;
		App->entities->DestroyEntities();
		
		lifes = 4;
	}
}

int j1Entities::HurtingPlayer()
{
	playerLifes -= 1;

	return playerLifes;
}

void j1Entities::UpdateScore(int score_player)
{
	//switch (type)
	//{
	//case Entities_Type::BAT:
	//	score = score + 50;
	//	score_text = App->gui->AddLabel(300, 20, (p2SString)score, App->scene, nullptr);
	//	break;

	//case Entities_Type::NINJA:
	//	score = score + 100;
	//	score_text = App->gui->AddLabel(300, 20, (p2SString)score, App->scene, nullptr);
	//	break;
	//}

	App->scene->score_text = (Gui_Label*)App->gui->AddLabel(300, 20, (p2SString)score_player, App->scene, nullptr);
}

int j1Entities::ScorePlayer()
{
	score += 50;

	return score;
}

