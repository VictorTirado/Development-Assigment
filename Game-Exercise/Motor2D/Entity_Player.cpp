#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1Entitites.h"
#include "SelectCharacter.h"
#include "j1FadeToBlack.h"
#include "j1Particles.h"
#include "j1Pathfinding.h"
#include "Entity_Player.h"
#include "j1Gui.h"
#include "Entity_Book.h"
#include "MainMenu.h"
#include "Brofiler\Brofiler.h"

#include "GUI_Image.h"

Entity_Player::Entity_Player(int x, int y) : Entity(x , y)
{
	sprites = App->tex->Load(App->entities->textures.GetString());
	pugi::xml_document player_file;
	pugi::xml_node player;
	player = App->LoadEntities(player_file, Entities::PLAYER_ENTITY);

	path = player.child("folder").attribute("path").as_string();
	for (pugi::xml_node animations = player.child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		p2SString name = animations.attribute("name").as_string();
		if (name == "idle")
			LoadAnimation(animations, &idle);
		if (name == "idleBackwards")
			LoadAnimation(animations, &idleBackwards);
		if (name == "run")
			LoadAnimation(animations, &run);
		if (name == "runBackwards")
			LoadAnimation(animations, &runBackwards);
		if (name == "teleport")
			LoadAnimation(animations, &teleport);
		if (name == "teleportBackwards")
			LoadAnimation(animations, &teleportBackwards);
		if (name == "jutsu")
			LoadAnimation(animations, &jutsu);
		if (name == "jump")
			LoadAnimation(animations, &jump);
		if (name == "fall")
			LoadAnimation(animations, &fall);
		if (name == "jumpBackwards")
			LoadAnimation(animations, &jumpBackwards);
		if (name == "fallBackwards")
			LoadAnimation(animations, &fallBackwards);
		if (name == "throwKunai")
			LoadAnimation(animations, &throwKunai);
		if (name == "throwKunaiBackwards")
			LoadAnimation(animations, &throwKunaiBackwards);
	}

	deathfx_path = player.child("audio").attribute("path").as_string();
	teleportfx_path = player.child("audio2").attribute("tp_path").as_string();
	kunai_path = player.child("audio3").attribute("kunai_path").as_string();
	animation = &idle;
	App->audio->LoadFx(deathfx_path.GetString());
	App->audio->LoadFx(teleportfx_path.GetString());
	App->audio->LoadFx(kunai_path.GetString());
	collider = App->collision->AddCollider({ 0, 0, 38, 54 }, COLLIDER_TYPE::COLLIDER_PLAYER, App->entities);
}

Entity_Player::~Entity_Player()
{
	App->tex->UnLoad(sprites);
	App->tex->UnLoad(X);
	sprites = nullptr;
	X = nullptr;
}


void Entity_Player::Update(float dt)
{
	BROFILER_CATEGORY("EntityPlayerUpdate", Profiler::Color::SpringGreen);
	if (firstUpdate == true)
	{
		//can_tp = false;
		firstUpdate = false;
	}

	else if (!is_backwards)
		animation = &idle;
	else if (is_backwards)
		animation = &idleBackwards;

	player_pos = App->map->WorldToMap(position.x, position.y);

	//LOGIC
	gid = App->map->Get_gid(position.x + 10, position.y + 51);
	
	if (App->map->data.map_layers.end->data->data[gid + 1] != Collision_Type::COLLISION_CHANGE_MAP || App->map->data.map_layers.end->data->data[gid] == Collision_Type::COLLISION_DEATH)
	{
		if (App->map->data.map_layers.end->data->data[gid + 1] != Collision_Type::COLLISION_WALL && App->map->data.map_layers.end->data->data[gid] != Collision_Type::COLLISION_WALL)
		{
			position.y += 70 * dt;
			is_falling = true;
		}
		else
			is_falling = false;
	}
	if (App->map->data.map_layers.end->data->data[gid] == Collision_Type::COLLISION_DEATH)
	{
		App->map->CleanUp();
		App->entities->DestroyEntities();
		if (App->scene->map_number == 1)
		{
			App->map->Load("Map4.tmx");
			App->map->Spawn();
			can_tp = false;
		}
		else if (App->scene->map_number == 2)
		{
			App->map->Load("ForestMap.tmx");
			App->map->Spawn();
		}
		App->entities->HurtingPlayer();
		App->entities->UpdatePlayerLifes(App->entities->playerLifes);
		App->audio->PlayFx(2); //player's death fx
		App->fade_to_black->FadeToBlack(App->scene, App->entities, 3.0f);
	
	}

	else if (App->map->data.map_layers.end->data->data[gid] == Collision_Type::COLLISION_CHANGE_MAP)
	{
		App->map->CleanUp();
		App->entities->DestroyEntities();
		if (App->scene->map_number == 1)
		{
			if (App->map->Load("ForestMap.tmx"))
			{
				App->map->Spawn();

				int w, h;
				uchar* data = NULL;
				if (App->map->CreateWalkabilityMap(w, h, &data))
					App->pathfinding->SetMap(w, h, data);

				RELEASE_ARRAY(data);

			}
			can_tp = true;
			App->scene->map_number = 2;
			firstUpdate = true;
		}
		else if (App->scene->map_number == 2)
		{
			App->fade_to_black->FadeToBlack(App->scene, App->main_menu, 3.0f);
			App->map->CleanUp();
			App->gui->DestroyAllUi();
			App->scene->active = false;
			App->main_menu->active = true;
			App->main_menu->Start();
			App->scene->first_update = true;
			//App->entities->DestroyEntities();
	
			App->scene->map_number = 1;
			firstUpdate = true;
		
		}
		
		App->fade_to_black->FadeToBlack(App->scene, App->entities, 3.0f);
	}
	//MOVEMENT PLAYER
	else if (App->map->data.map_layers.end != nullptr) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->map->data.map_layers.end->data->data[gid - 1] != COLLISION_FLOOR && App->fade_to_black->IsFading() == false)
		{
			animation = &runBackwards;
			is_backwards = true;
			position.x -= 80 * dt;
		}

		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->map->data.map_layers.end->data->data[gid + 1] != COLLISION_FLOOR && App->fade_to_black->IsFading() == false)
		{
			animation = &run;
			is_backwards = false;
			position.x += 100 * dt;
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->fade_to_black->IsFading() == false)
		{
			if (App->map->data.map_layers.end->data->data[gid] == 51)
				is_jumping = true;
		}
	}


	

	//THROW KUNAI
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		is_shooting = true;
	

	if (is_shooting)
	{
		App->audio->PlayFx(4);
		if (is_backwards)
		{
			animation = &throwKunaiBackwards;
			App->particles->kunai_particle_backwards.speed.x = -800*dt;
			App->particles->AddParticle(App->particles->kunai_particle_backwards, position.x, position.y + 20, COLLIDER_PLAYER_SHOT);
		}

		else
		{
			animation = &throwKunai;
			App->particles->kunai_particle.speed.x = 800 * dt;
			App->particles->AddParticle(App->particles->kunai_particle, position.x + 12, position.y + 20, COLLIDER_PLAYER_SHOT);
		}
		is_shooting = false;
	}

	if(!is_shooting)
	{
		throwKunaiBackwards.Reset();
		throwKunai.Reset();
	}
	
	//JUMP
	if (!is_jumping)
	{
			old_player_position.y = position.y;
			velocity.y = 0;
	}
	  

	if (is_jumping)
	{
		velocity.y = -200*dt;

		if (position.y < old_player_position.y - 60)
		{
			velocity.y = 1*dt;
			is_jumping = false;
		}

	}
	velocity.y += App->map->prop->gravity;
	position.y += velocity.y;
	
	if (is_falling && !is_backwards)
		animation = &fall;

	if (is_falling && is_backwards)
		animation = &fallBackwards;

	if (is_jumping && is_backwards)
		animation = &jumpBackwards;

	if(is_jumping && !is_backwards)
		animation = &jump;

	//TELEPORT
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN && App->map->data.map_layers.end->data->data[gid + 1] == 51 && can_tp)
	{
		is_tp = true;
		App->audio->PlayFx(3); //Teleport fx
	}

	if (is_tp)
	{
		animation = &teleport;
		App->map->prop->tp_time += 0.1f;

		if (App->map->prop->tp_time == 0.6f)
		{
			position.y -= 100;
			is_tp = false;
			App->map->prop->tp_time = 0.0f;
		}
	}

	//GOD MODE  The player can fly and move everywhere and is not affected by gravity
	if (App->scene->is_god)
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && App->fade_to_black->IsFading() == false)
			position.y -= 120*dt;

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && App->fade_to_black->IsFading() == false)
			position.y += 120 * dt;
	}

	if (App->entities->playerLifes == 0)
	{
		App->fade_to_black->FadeToBlack(App->scene, App->main_menu, 3.0f);
		
		App->map->CleanUp();
		App->gui->DestroyAllUi();
		App->main_menu->active = true;
		App->main_menu->Start();
		App->scene->first_update = true;
		App->entities->DestroyEntities();
		App->scene->active = false;
	}
	
	App->render->camera.x = (-position.x * App->win->render_scale) + (App->win->width / 2);
	App->render->camera.y = (-position.y * App->win->render_scale) + (App->win->height / 2);

	App->entities->player_time = App->entities->time_playing.ReadSec();
}


void Entity_Player::LoadAnimation(pugi::xml_node& animation, Animation* player)
{
	for (pugi::xml_node frame = animation.child("frame"); frame; frame = frame.next_sibling("frame"))
	{
		player->PushBack({frame.attribute("x").as_int(),frame.attribute("y").as_int(),frame.attribute("w").as_int(),frame.attribute("h").as_int()});
		
	}
	player->speed = animation.attribute("speed").as_float();
	player->loop = animation.attribute("loop").as_bool();
}

bool Entity_Player::Load(pugi::xml_node& data)
{
	App->map->CleanUp();
	
	if(data.child("map") != NULL)
		App->scene->map_number = data.child("map").attribute("level").as_int();

	if (App->scene->map_number == 2 && data.child("map") != NULL)
	{
		App->fade_to_black->FadeToBlack(App->scene, App->entities, 3.0f);
		App->map->CleanUp();
		App->entities->DestroyEntities();
		if (App->map->Load("ForestMap.tmx"))
		{
			
			int w, h;
			uchar* data = NULL;
			if (App->map->CreateWalkabilityMap(w, h, &data))
				App->pathfinding->SetMap(w, h, data);

			RELEASE_ARRAY(data);
			
		}
		App->map->SpawnEnemies();
		position.x = data.child("position").attribute("x").as_int();
		position.y = data.child("position").attribute("y").as_int();
		App->entities->score = data.child("score").attribute("value").as_int();
		App->entities->SpawnEntities(position.x, position.y, Entities_Type::PLAYER);
	}
	else if (App->scene->map_number == 1 && data.child("map") != NULL)
	{
		App->fade_to_black->FadeToBlack(App->scene, App->entities, 3.0f);
		App->map->CleanUp();
		App->entities->DestroyEntities();
		if(App->map->Load("Map4.tmx"))
		{
			int w, h;
			uchar* data = NULL;
			if (App->map->CreateWalkabilityMap(w, h, &data))
				App->pathfinding->SetMap(w, h, data);
			RELEASE_ARRAY(data);
		}
		App->map->SpawnEnemies();
		App->entities->score = data.child("position").attribute("x").as_int();
		position.x = data.child("position").attribute("x").as_int();
		position.y = data.child("position").attribute("y").as_int();
		App->entities->score = data.child("score").attribute("value").as_int();
		App->entities->SpawnEntities(position.x,position.y, Entities_Type::PLAYER);
	}
	return true;
}

bool Entity_Player::Save(pugi::xml_node& data)const
{
	data.append_child("map").append_attribute("level") = App->scene->map_number;
	data.append_child("position").append_attribute("x") = position.x;
	data.append_child("type").append_attribute("value") = App->characters->type;
	data.child("position").append_attribute("y") = position.y;
	data.append_child("score").append_attribute("value") = App->entities->score;
	return true;
}

void Entity_Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_TYPE::COLLIDER_ENEMY)
	{
		App->fade_to_black->FadeToBlack(App->scene, App->entities, 3.0f);

	}
}



