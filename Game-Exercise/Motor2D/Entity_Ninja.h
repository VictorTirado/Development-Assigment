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

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	void OnCollision(Collider* collider);
	void LoadAnimation(pugi::xml_node&, Animation*);


public:

	Animation idle;
	bool firstUpdate = true;
	p2SString path = nullptr;

};

#endif
