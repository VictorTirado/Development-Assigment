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


	bool CleanUp();
	bool PreUpdate();
	void Update(float dt);
	bool PostUpdate();

	void OnCollision(Collider* collider);

public:

	Animation idle;
	bool firstUpdate = true;
};

#endif
