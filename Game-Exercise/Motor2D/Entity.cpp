#include "j1App.h"
#include "Entity.h"
#include "j1Collision.h"
#include "j1Entitites.h"
#include "j1Render.h"
#include "j1Scene.h"

#include "Entity_Book.h"
#include "Entity_Bat.h"
#include "Entity_Ninja.h"
#include "Entity_Player.h"

Entity::Entity(int x, int y) : position(x, y)
{
}

Entity::~Entity()
{

}

const Collider* Entity::GetCollider() const
{
	return collider;
}

void Entity::Draw(SDL_Texture* sprites)
{
	SDL_Rect r = animation->GetCurrentFrame();
	if (this->entity_type == PLAYER) {
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
		if(collider!=nullptr)
		collider->SetPos(position.x, position.y);
	}
	if (this->entity_type == BOOK && App->entities->book->collider != nullptr && App->entities->player->can_tp == false)
	{
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
		collider->SetPos(position.x, position.y);
	}
	if (this->entity_type == BAT && App->entities->bat->collider != nullptr)
	{
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
		collider->SetPos(position.x, position.y);
	}

	if (this->entity_type == NINJA && App->entities->ninja->collider != nullptr)
	{
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
		//collider->SetPos(position.x, position.y);
	}
}

void Entity::OnCollision(Collider* collider)
{

}