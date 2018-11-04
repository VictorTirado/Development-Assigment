#ifndef __j1ENTITIES_H__
#define __j1ENTITIES_H__

#include "j1Module.h"
#include "p2DynArray.h"

class Entity_Player;

enum Entities_Type
{
	PLAYER,
	BOOK,
	BAT,
	NINJA,
	NONE,
};

class Entity;
class Player;
class j1Entities : public j1Module
{

public:
	j1Entities();
	~j1Entities();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool CleanUp();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool SpawnEntities(int x, int y, Entities_Type type);
	void OnCollision(Collider* c1, Collider* c2);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	p2DynArray<Entity*> entities;

	Entity_Player* player;

	p2SString textures;
};


#endif // __j1ENTITIES_H__
