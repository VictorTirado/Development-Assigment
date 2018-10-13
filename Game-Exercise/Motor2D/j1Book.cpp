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

//#include "j1Particles.h"
#include "j1FadeToBlack.h"
//#include "ModuleCollision.h"


j1Book::j1Book() : j1Module()
{
	book_position.x = 240;
	book_position.y = 576;
	//name.create("book");
	//pugi::xml_document player_file;
	//pugi::xml_node player;
	//player = App->LoadPlayer(player_file);

	////path = player.child("folder").attribute("path").as_string();
	//for (pugi::xml_node animations = player.child("animation"); animations; animations = animations.next_sibling("animation"))
	//{
	//	p2SString name = animations.attribute("name").as_string();
	//	if (name == "idle")
	//		LoadAnimation(animations, &idle);
	//	
	//}

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

	//graphics = App->tex->Load(path.GetString());
	graphics = App->tex->Load("textures/Objects.png");
	book_collider = App->collision->AddCollider({ book_position.x, book_position.y, 28, 25 }, COLLIDER_TYPE::COLLIDER_POWER_UP, this);
	
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
	LOG("Unloading player");

	App->tex->UnLoad(graphics);
	graphics = nullptr;

	return true;
}


void j1Book::LoadAnimation(pugi::xml_node& animation, Animation* player)
{
	for (pugi::xml_node frame = animation.child("frame"); frame; frame = frame.next_sibling("frame"))
	{
		player->PushBack({ frame.attribute("x").as_int(),frame.attribute("y").as_int(),frame.attribute("w").as_int(),frame.attribute("h").as_int() });

	}
	player->speed = animation.attribute("speed").as_float();
	player->loop = animation.attribute("loop").as_bool();
}

void j1Book::OnCollision(Collider* collider)
{
	LOG("COLLISION");
	App->player->can_tp = true;
	CleanUp();
}


