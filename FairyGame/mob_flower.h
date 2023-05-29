#ifndef MOB_FLOWER_H
#define MOB_FLOWER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"
#include "sprite_animation.h"

class MobFlower : public GameObject
{
public:
	bool Attack;
	float RadiusCheckHero;
	float CooldownAttack;
	SpriteAnimation idle;
	SpriteAnimation attack;
	SpriteAnimation die;

	MobFlower();
	MobFlower(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D sprite, float radiusCollision, SpriteAnimation animationIdle, SpriteAnimation animationAttack, SpriteAnimation animationDie, float radiusCheckHero = 800.0f, float rotataion = 0.0f, float cooldownAttack = 2.0f);
	void Animation();
	void Update(float dt);
	bool CheckHero(GameObject& hero);
	void Draw(SpriteRenderer& renderer);
	void Reset();
};

#endif
