#ifndef __j1ENTITIES_H__
#define __j1ENTITIES_H__

#include "j1Module.h"

enum Entities_Type
{
	PLAYER,
	BOOK,
	BAT,
	NINJA,
	NONE,
};
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
};


#endif // __j1ENTITIES_H__
