#include <math.h>
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "p2Log.h"
//#include "ModuleAudio.h"
#include "j1Particles.h"
#include "Entity_Player.h"
#include "j1Collision.h"
#include "Brofiler\Brofiler.h"
#include "SDL/include/SDL_timer.h"

j1Particles::j1Particles()
{
	name.create("particles");

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	kunai_particle.anim.PushBack({ 0, 0, 20, 7 });
	kunai_particle.anim.loop = false;
	kunai_particle.anim.speed = 0.3f;

	kunai_particle_backwards.anim.PushBack({ 31, 0, 20, 7 });
	kunai_particle_backwards.anim.loop = false;
	kunai_particle_backwards.anim.speed = 0.3f;

}

j1Particles::~j1Particles()
{
}

// Load assets
bool j1Particles::Start()
{
	LOG("Loading particles");
	graphics = App->tex->Load("textures/Kunai.png");

	return true;
}

// Unload assets
bool j1Particles::CleanUp()
{
	LOG("Unloading particles");
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}
	return true;
}

// Update: draw background
bool j1Particles::Update(float dt)
{
	BROFILER_CATEGORY("ModuleParticlesUpdate", Profiler::Color::PaleGreen);
	bool ret = true;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update(dt) == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here

			}
		}
	}

	return ret;
}

void j1Particles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	BROFILER_CATEGORY("AddParticlesUpdate", Profiler::Color::DeepPink);
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}

}

void j1Particles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}


Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update(float dt)
{
	BROFILER_CATEGORY("ParticlesUpdate", Profiler::Color::Moccasin);
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);


	return ret;
}