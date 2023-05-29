#include "hero.h"

Hero::Hero()
    : GameObject(), Jumping(false), Falling(false), IsGround(false){ }

Hero::Hero(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D sprite, float radiusCollision)
    : GameObject(pos, size, sprite, glm::vec3(1.0f), velocity, radiusCollision), Jumping(false), Falling(false), IsGround(false){}

void Hero::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

void Hero::Animation(SpriteAnimation* idle, SpriteAnimation* walk, SpriteAnimation* attack, SpriteAnimation* die, SpriteAnimation* appear, SpriteAnimation* disappear)
{
    if (this->Appear)
    {
        appear->animation(*this);
        if (appear->theEnd)
        {
            this->Appear = false;
            appear->theEnd = false;
            appear->IsPlaying = true;
        }
    }
    else if (this->DisAppear)
    {
        this->Velocity = glm::vec2(0.0f);
        disappear->animation(*this);
    }
    else if (this->Destroyed)
    {
        this->Velocity = glm::vec2(0.0f);
         die->animation(*this);
    }
    else if (this->Attack && !attack->theEnd)
        attack->animation(*this);
    else if (this->Velocity.x != 0)
        walk->animation(*this);
    else
        idle->animation(*this);
}

void Hero::UpdateDirection(float dt)
{
    this->Velocity.y = CalculateYVelocity(dt);
    this->Falling = Velocity.y >= 0.0f;
    this->Jumping = Velocity.y < -0.1f;
    this->Position.y += this->Velocity.y * dt;
    this->Position.x += this->Velocity.x * dt;
}

float Hero::CalculateYVelocity(float dt)
{
    float yVelocity = this->Velocity.y;

    if (this->Jumping)
    {
        yVelocity += (800.0f * dt);
        return yVelocity;
    }
    else if (this->IsGround)
    {
        this->Velocity.y = 0.0f;
        return 0.0f;
    }
    else if (this->Falling)
    {
        yVelocity = 400.0f;
        return yVelocity;
    }
    else
        return yVelocity;
}

void Hero::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Rotation = 0.0f;
    this->Position = position;
    this->Velocity = velocity;
    this->IsGround = false;
    this->Falling = false;
    this->Jumping = false;
    this->Destroyed = false;
    this->Appear = true;
    this->DisAppear = false;
}

bool Hero::CheckCollision(GameObject& go)
{
    glm::vec2 centerOne(go.Position.x + (go.Size.x / 2.0f), go.Position.y + (go.Size.y / 2.0f));
    glm::vec2 centerTwo(this->Position.x + (this->Size.x / 2.0f), this->Position.y + (this->Size.y / 2.0f));

    bool collisionX = centerOne.x + go.RadiusCollision >= centerTwo.x - 50.0f && centerTwo.x + 50.0f >= centerOne.x - go.RadiusCollision;

    bool collisionY = centerOne.y + go.RadiusCollision >= centerTwo.y - 125.0f && centerTwo.y + 125.0f >= centerOne.y - go.RadiusCollision;

    return collisionX && collisionY;
}
