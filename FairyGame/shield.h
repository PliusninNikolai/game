#ifndef SHIELD_H
#define SHIELD_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"
#include "sprite_animation.h"

class Shield : public GameObject
{
public:
	enum class States
	{
		APPEAR,
		IDLE,
		DISAPPEAR,
		DISAPPEAR_ATTACK
	};

	float TimeLife;
	States State;

	Shield();
	Shield(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), float radiusCollision = 150.0f, float rotation = 0.0f, bool destroyed = true, States state = States::IDLE, float timeLife = 2.0f);
	void Animation(SpriteAnimation* appear, SpriteAnimation* idle, SpriteAnimation* disappear, SpriteAnimation* disappearAttack);
	void Update(GameObject& target, float dt);
};

#endif 