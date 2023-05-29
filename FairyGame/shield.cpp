#include "shield.h"

Shield::Shield()
{}

Shield::Shield(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity, float radiusCollision, float rotation, bool destroyed, States state, float timeLife)
	: GameObject(pos, size, sprite, color, velocity, radiusCollision, rotation), State(state), TimeLife(timeLife)
{
	this->Destroyed = destroyed;
}

void Shield::Update(GameObject& target, float dt)
{
	this->Position = target.Position;
	if(TimeLife > 0.0f)
	this->TimeLife -= dt;
}


void Shield::Animation(SpriteAnimation* appear, SpriteAnimation* idle, SpriteAnimation* disappear, SpriteAnimation* disappearAttack)
{
	switch (this->State)
	{
	case Shield::States::APPEAR:
		this->Destroyed = false; 
		disappear->CurrentFrame = 0;
		idle->CurrentFrame = 0;
		disappearAttack->CurrentFrame = 0;
		appear->animation(*this);
		if (appear->theEnd)
		{
			appear->theEnd = false;
			appear->IsPlaying = true;
			this->State = States::IDLE;
		}
		break;
	case Shield::States::IDLE:
		if (!this->Destroyed)
		{
			if (this->TimeLife > 0.0f)
			{
				idle->animation(*this);
			}
			else
				this->State = States::DISAPPEAR;
		}
		break;
	case Shield::States::DISAPPEAR:
		disappear->animation(*this);
		if (disappear->theEnd)
		{
			idle->CurrentFrame = 0;
			appear->CurrentFrame = 0;
			disappear->theEnd = false;
			disappear->IsPlaying = true;
			this->Destroyed = true;
		}
		break;
	case Shield::States::DISAPPEAR_ATTACK:
		disappearAttack->animation(*this);
		if (disappearAttack->theEnd)
		{
			idle->CurrentFrame = 0;
			appear->CurrentFrame = 0;
			disappear->CurrentFrame = 0;
			disappearAttack->theEnd = false;
			disappearAttack->IsPlaying = true;
			
			this->Destroyed = true;
		}
		break;
	default:
		break;
	}
}
