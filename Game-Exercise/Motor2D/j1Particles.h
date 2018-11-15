#ifndef __j1PARTICLES_H__
#define __j1PARTICLES_H__

#include "j1Module.h"
#include "Animation.h"

#include "j1Collision.h"
#include "p2Point.h"


#define MAX_ACTIVE_PARTICLES 500


struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update(float dt);
};

class j1Particles : public j1Module
{
public:
	j1Particles();
	~j1Particles();

	bool Start();
	bool Update(float dt);
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:
	Animation* current_animation = nullptr;
	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:

	int cd = 0;
	Particle kunai_particle;
	Particle kunai_particle_backwards;

};

#endif // __MODULEPARTICLES_H__