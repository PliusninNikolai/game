#ifndef HERO_H
#define HERO_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"
#include "sprite_animation.h"
#include "game_level.h"

const glm::vec2 HERO_VELOCITY(500.0f, -750.0f);

class Hero : public GameObject
{
public:
	bool Jumping;
	bool Falling;
	bool IsGround;
	bool Attack = false;
	bool Appear = true;
	bool DisAppear = false;

	Hero();
	Hero(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D sprite, float radiusCollision);

	void Animation(SpriteAnimation* idle, SpriteAnimation* walk, SpriteAnimation* attack, SpriteAnimation* die,SpriteAnimation* appear, SpriteAnimation* disappear);
	void UpdateDirection(float dt);
	void Reset(glm::vec2 position, glm::vec2 velocity);
	bool CheckCollision(GameObject& go);
	void Draw(SpriteRenderer& renderer);
private:
	float CalculateYVelocity(float dt);
};

#endif 
