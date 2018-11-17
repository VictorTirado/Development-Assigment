#ifndef __j1BAT_H__
#define __j1BAT_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Animation.h"
#include "Entity.h"

class Entity_Bat : public Entity
{
public:
	Entity_Bat(int x, int y);
	~Entity_Bat();


	bool CleanUp();
	bool PreUpdate();
	void Update(float dt);
	bool PostUpdate();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	void OnCollision(Collider* collider);
	void LoadAnimation(pugi::xml_node&, Animation* bat);

	bool Radar();

public:

	p2SString path = nullptr;
	Animation idle;
	Animation idleRight;
	bool firstUpdate = true;
	uint range = 8;

	iPoint speed = iPoint(0,0);
	iPoint path_to_follow;
	iPoint original_pos;

	iPoint bat_pos;
	iPoint player_pos;


};

#endif