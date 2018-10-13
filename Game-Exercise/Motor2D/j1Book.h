#ifndef __j1BOOK_H__
#define __j1BOOK_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Animation.h"


class j1Book: public j1Module
{
public:
	j1Book();
	~j1Book();

	bool Start();
	bool CleanUp();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	void LoadAnimation(pugi::xml_node&, Animation* player);
	void OnCollision(Collider* collider);

public:
	iPoint book_position;
	Animation idle;
	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Collider* book_collider = nullptr;
	bool is_caught = false;
	bool firstUpdate = true;
};
#endif