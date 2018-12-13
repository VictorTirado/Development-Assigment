#ifndef __j1BOOK_H__
#define __j1BOOK_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Animation.h"
#include "Entity.h"


class Entity_Book: public Entity
{
public:
	Entity_Book(int x,int y);
	~Entity_Book();

	
	
	void Update(float dt);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	void OnCollision(Collider* collider);

	void UpdateBookUI(bool book_caught);

public:
	
	Animation idle;
	bool is_caught = false;
	bool firstUpdate = true;
};
#endif