#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Animation.h"
#include "Entity.h"



class Entity_Player : public Entity
{
public:
	Entity_Player(int x,int y);
	~Entity_Player();

	void Update(float dt);


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
	Animation throwKunai;
	Animation throwKunaiBackwards;
	
	p2SString path = nullptr;
	p2SString deathfx_path = nullptr;
	p2SString teleportfx_path = nullptr;
	p2SString kunai_path = nullptr;
	bool firstUpdate = true;
	bool is_backwards = false;

	bool is_falling = true;
	bool is_jumping = false;
	bool is_teleporting = false;

	uint gid = 0;
	iPoint player_pos;
	bool check = false;

	bool can_tp = false;
	bool is_tp = false;
	bool is_shooting = false;

	enum Collision_Type
	{
		NONE,
		COLLISION_WALL = 51,
		COLLISION_FLOOR = 53,
		COLLISION_DEATH = 71,
		COLLISION_CHANGE_MAP =72,

	};

	iPoint old_player_position;
	iPoint velocity;
};
#endif