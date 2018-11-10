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

	void OnCollision(Collider* collider);

public:

	p2SString path = nullptr;
	Animation idle;
	bool firstUpdate = true;
};

#endif