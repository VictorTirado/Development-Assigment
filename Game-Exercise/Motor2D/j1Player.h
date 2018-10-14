#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Animation.h"

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
	void OnCollision(Collider*, Collider*);
	

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
	iPoint player_position = { 0,0 };
	
	SDL_Texture* graphics = nullptr;
	p2SString path = nullptr;
	p2SString fx_path = nullptr;
	bool firstUpdate = true;
	bool is_backwards = false;

	bool is_falling = true;
	bool is_jumping = false;
	bool is_teleporting = false;

	uint gid = 0;

	bool check = false;

	bool can_tp = false;
	bool is_tp = false;
	

	Collider* player_collider = nullptr;
};
#endif