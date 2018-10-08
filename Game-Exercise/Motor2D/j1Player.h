#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Animation.h"
//#include "ModuleCollision.h"
#define MOVEMENT_SPEED 1





class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	bool Start();
	bool CleanUp();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	void LoadAnimation(pugi::xml_node&, Animation* player);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
public:
	Animation idle;
	Animation idleBackwards;
	Animation runBackwards;
	Animation run;
	Animation teleport;
	Animation jutsu;
	Animation* current_animation = nullptr;
	iPoint player_position;

	


	SDL_Texture* graphics;
	p2SString path;
	bool firstUpdate = true;
	bool is_backwards = false;

	bool is_jumping = false;
	uint player_position_y0;
	uint initial_velocity = 25;
	uint gravity = 5;
	float jumping_time = 0.0f;

	Collider* collider;

	
};
#endif