#ifndef __j1ENTITIES_H__
#define __j1ENTITIES_H__

#include "j1Module.h"
#include "p2DynArray.h"
#include "j1Timer.h"

class Entity_Player;
class Entity_Book;
class Entity_Bat;
class Entity_Ninja;
class Entity_Gaara;

enum Entities_Type
{
	PLAYER,
	GAARA_PLAYER,
	BOOK,
	BAT,
	NINJA,
	ENEMY,
	NONE,
};

class Entity;
class Player;
class Book;
class Bat;
class Ninja;
class Gaara;

class j1Entities : public j1Module
{

public:
	j1Entities();
	~j1Entities();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool CleanUp();
	void DestroyEntities();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool SpawnEntities(int x, int y, Entities_Type type);
	void OnCollision(Collider* c1, Collider* c2);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	
	void ResetMap(int map);

	void UpdatePlayerLifes(int lifes);
	int HurtingPlayer();

	void UpdateScore(int score_player);
	int ScorePlayer();

	void UpdateTime(float current_time);
	float GetTime();

	p2DynArray<Entity*> entities;
	
	Entity_Player* player;
	Entity_Gaara* gaara;
	Entity_Book* book;
	Entity_Bat* bat;
	Entity_Ninja* ninja;
	
	p2SString textures;
	int playerLifes = 4;
	int score = 0;
	int time = 0;
	j1Timer time_playing;
	GUI* time_text = nullptr;
	float player_time = 0.0f;
};


#endif // __j1ENTITIES_H__
