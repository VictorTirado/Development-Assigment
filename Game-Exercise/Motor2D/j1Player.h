#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Animation.h"
//#include "ModuleCollision.h"

enum ENTITY_TYPES
{
	NO_TYPE,
	PLAYER,
};

struct PlayerInfo
{
	ENTITY_TYPES type = ENTITY_TYPES::NO_TYPE;
	int x = 0;
	int y = 0;
	uint player_hp = 0;
};

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

	bool AddPlayer(ENTITY_TYPES, int, int);
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
	
	void SpawnPlayer(const PlayerInfo&);
	void LoadAnimation(pugi::xml_node&, Animation* player);
public:
	Animation idle;
	Animation run;
	Animation teleport;
	Animation jutsu;
	Animation* current_animation = nullptr;
	iPoint player_position;

	PlayerInfo player_data;
	j1Player* player_spawn;

	SDL_Texture* graphics;

};
#endif