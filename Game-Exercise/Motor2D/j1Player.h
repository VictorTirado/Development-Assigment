#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Animation.h"
//#include "ModuleCollision.h"

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


	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
	
	void LoadAnimation(pugi::xml_node&, Animation* player);
public:
	Animation idle;
	Animation run;

	SDL_Texture* graphics = nullptr;

	

};
#endif