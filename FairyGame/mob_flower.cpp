#include "mob_flower.h"

MobFlower::MobFlower()
    : GameObject(), Attack(false) { }

MobFlower::MobFlower(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D sprite, float radiusCollision, SpriteAnimation animationIdle, SpriteAnimation animationAttack, SpriteAnimation animationDie, float radiusCheckHero, float rotation, float cooldownAttack)
    : GameObject(pos, size, sprite, glm::vec3(1.0f), velocity, radiusCollision, rotation), Attack(false), idle(animationIdle), attack(animationAttack), die(animationDie), RadiusCheckHero(radiusCheckHero), CooldownAttack(cooldownAttack)  {}

void MobFlower::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

void MobFlower::Reset()
{
    this->Destroyed = false;
    this->die.IsPlaying = true;
    this->die.theEnd = false;
    this->CooldownAttack = 2.0f;
}


void MobFlower::Animation()
{
    if (this->Destroyed)
    {
        this->die.animation(*this);
    }
    else if (attack.theEnd)
    {
        this->CooldownAttack = 2.0f;
        this->Attack = false;
        this->attack.theEnd = false;
    }
    else if (this->Attack && !attack.theEnd)
        this->attack.animation(*this);
    else
        this->idle.animation(*this);
}

void MobFlower::Update(float dt)
{
    if (!this->Destroyed)
    {
        this->CooldownAttack -= dt;
    }
    else
        this->CooldownAttack = 0.0f;
}

bool MobFlower::CheckHero(GameObject& hero)
{
    glm::vec2 centerOne(hero.Position.x + (hero.Size.x / 2.0f), hero.Position.y + (hero.Size.y / 2.0f));
    glm::vec2 centerTwo(this->Position.x + (this->Size.x / 2.0f), this->Position.y + (this->Size.y / 2.0f));

    bool collisionX = centerOne.x + hero.RadiusCollision >= centerTwo.x - this->RadiusCheckHero && centerTwo.x + this->RadiusCheckHero >= centerOne.x - hero.RadiusCollision;

    bool collisionY = centerOne.y + hero.RadiusCollision >= centerTwo.y - this->RadiusCheckHero/2 && centerTwo.y + this->RadiusCheckHero/2 >= centerOne.y - hero.RadiusCollision;

    return collisionX && collisionY;
}

