#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Animation.h"
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
	bool GodMode();
public:
	Animation idle;
	Animation idleBackwards;
	Animation runBackwards;
	Animation run;
	Animation teleport;
	Animation teleportBackwards;
	Animation jutsu;
	Animation jump;
	Animation fall;
	Animation jumpBackwards;
	Animation fallBackwards;
	Animation* current_animation = nullptr;
	iPoint player_position;

	


	SDL_Texture* graphics = nullptr;
	p2SString path = nullptr;
	bool firstUpdate = true;
	bool is_backwards = false;

	bool is_falling = true;
	bool is_jumping = false;
	bool is_teleporting = false;
	int player_position_y0 = 0;
	uint gravity = 5;
	float jumping_time = 0.0f;
	
	uint gid = 0;

	bool check = false;
};
#endif