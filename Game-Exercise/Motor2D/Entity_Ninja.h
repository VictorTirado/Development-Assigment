#ifndef __j1NINJA_H__
#define __j1NINJA_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Animation.h"
#include "Entity.h"

class Entity_Ninja : public Entity
{
public:
	Entity_Ninja(int x, int y);
	~Entity_Ninja();

	void Update(float dt);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	void OnCollision(Collider* collider);
	void LoadAnimation(pugi::xml_node&, Animation*);

	bool Radar();

public:
	bool firstUpdate = true;
	Animation idle;
	Animation idleRight;
	Animation runLeft;
	Animation runRight;
	
	p2SString path = nullptr;
	
	iPoint original_pos;
	iPoint ninja_pos;
	iPoint player_pos;
	iPoint speed = iPoint(0, 0);
	iPoint path_to_follow;

	uint range = 10;
	uint gid = 0;

};

#endif
