#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Collision.h"
//#include "j1Particles.h"
#include "j1FadeToBlack.h"
//#include "ModuleCollision.h"


j1Player::j1Player() : j1Module()
{
	name.create("player");
	pugi::xml_document player_file;
	pugi::xml_node player;
	player = App->LoadPlayer(player_file);

	player_position.x = 50;
	player_position.y = 250;

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
		if (name == "jutsu")
			LoadAnimation(animations, &jutsu);
		if (name == "jump")
			LoadAnimation(animations, &jump);
		if (name == "fall")
			LoadAnimation(animations, &fall);
	}
	current_animation = &idle;

}

j1Player::~j1Player()
{}


bool j1Player::Start()
{
	bool ret = true;
	
	graphics = App->tex->Load(path.GetString());
	
	collider = App->collision->AddCollider({ player_position.x, player_position.y,37,51 }, COLLIDER_PLAYER, this);

	return ret;
}

bool j1Player::PreUpdate()
{
	bool ret = true;

	

	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;

	if (!is_backwards)
		current_animation = &idle;
	/*while (App->map->data.map_layers.end->data->data[gid] != 51)
	{
		player_position.y += 1;
	}*/
	
	gid = App->map->Get_gid(player_position.x, player_position.y+51);
	App->render->DrawQuad({player_position.x+ 10,player_position.y+45,16,16},0,0,255,255);
	//LOG("GIIIIID %d", gid);
	if (is_backwards)
		current_animation = &idleBackwards;
	
	if (firstUpdate == true) 
	{
		App->render->camera.x = -player_position.x +(App->win->width/2);
		App->render->camera.y = -player_position.y -(App->win->height/2);
		
		firstUpdate = false;
	}
	if (OnCollision(collider,App->map->walkable) == false)
	{
		player_position.y = player_position.y;
	}
	else
	{
		
	}
	if (App->map->data.map_layers.end->data->data[gid +1] != 51)
		player_position.y += 1;

	else
	{
		player_position.y = player_position.y;
		is_falling = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		App->render->camera.x = -player_position.x ;
		App->render->camera.y = -player_position.y - 350;
		player_position.y += MOVEMENT_SPEED;
		LOG("%d camera x", App->render->camera.x);
		LOG("%d camera y", App->render->camera.y);
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		App->render->camera.x = -player_position.x ;
		App->render->camera.y = -player_position.y - 350;
		player_position.y -= MOVEMENT_SPEED;
		LOG("%d camera x", App->render->camera.x);
		LOG("%d camera y", App->render->camera.y);
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		App->render->camera.x = -player_position.x * 3 + (App->win->width / 2);
		App->render->camera.y = -player_position.y - 350;

		current_animation = &runBackwards;
		is_backwards = true;
		player_position.x -= MOVEMENT_SPEED;
		LOG("%d camera x", App->render->camera.x);
		LOG("%d camera y", App->render->camera.y);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		App->render->camera.x = -player_position.x*3 + (App->win->width / 2);
		App->render->camera.y = -player_position.y - 350;
		current_animation = &run;
		is_backwards = false;
		player_position.x += MOVEMENT_SPEED;
		LOG("%d camera x", App->render->camera.x);
		LOG("%d camera y", App->render->camera.y);
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
		current_animation = &jutsu;

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		is_jumping = true;

	if (jumping_time == 0.0f)
	   player_position_y0 = - 1 * player_position.y;


	if (is_jumping)
	{
		current_animation = &jump;
		jumping_time += 0.1f;
		//player_position.y = player_position_y0 - initial_velocity * jumping_time + (jumping_time*jumping_time) * gravity / 2; //Formula to calculate player position in Y axis
		//if (player_position.y > player_position_y0)
		//{
		//	jumping_time = 0.0f;
		//	is_jumping = false;
		//}
		//speed.y = gravity;
		player_position.y -= gravity;

		if (player_position.y > player_position_y0 && jumping_time >= 1.5f)
		{
			player_position.y += 5;
			jumping_time = 0.0f;
			is_jumping = false;
			is_falling = true;
		}
	}
	
	if (is_falling)
		current_animation = &fall;

	
	if (App->map->data.map_layers.end->data->data[gid] == 71)
	{
		player_position.x = 50;
		player_position.y = 250;
	}
	

	collider->SetPos(player_position.x, player_position.y);
	App->render->Blit(graphics, player_position.x, player_position.y, &current_animation->GetCurrentFrame());

	return ret;
}

bool j1Player::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool j1Player::CleanUp()
{
	LOG("Unloading player");
	
	return true;
}


void j1Player::LoadAnimation(pugi::xml_node& animation, Animation* player)
{
	for (pugi::xml_node frame = animation.child("frame"); frame; frame = frame.next_sibling("frame"))
	{
		player->PushBack({frame.attribute("x").as_int(),frame.attribute("y").as_int(),frame.attribute("w").as_int(),frame.attribute("h").as_int()});
		
	}
	player->speed = animation.attribute("speed").as_float();
	player->loop = animation.attribute("loop").as_bool();
}






bool j1Player::Load(pugi::xml_node& data)
{

	if (data.child("map") != nullptr)
	{
		App->scene->map_number = data.child("map").attribute("level").as_int();
	}

	if (App->scene->map_number == 2)
	{
		App->scene->ChangeMap(App->scene->map_number);
	}
	else if (App->scene->map_number == 1)
	{
		App->scene->ChangeMap(App->scene->map_number);
	}

	return true;
}

bool j1Player::Save(pugi::xml_node& data)const
{
	if (data.child("map") == NULL)
	{
		data.append_child("map").append_attribute("level") = App->scene->map_number;
	}
	else
	{
		data.child("map").attribute("level") = App->scene->map_number;
	}

	return true;
}
bool j1Player::OnCollision(Collider* n1, Collider* n2)
{
	
	return true;
}