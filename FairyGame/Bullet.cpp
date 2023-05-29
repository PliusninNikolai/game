#include "Bullet.h"

Bullet::Bullet()
	:GameObject()
{
}

Bullet::Bullet(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D sprite, float radiusCollision, float timeLife, bool destroyed)
    :GameObject(pos, size, sprite, glm::vec3(1.0f), velocity, radiusCollision, 0.0f, destroyed), TimeToLife(timeLife)
{
}


void Bullet::Update(float dt)
{
    if (!this->Destroyed)
    {
        this->TimeToLife -= dt;
        if (this->TimeToLife >= 0.0f)
            this->Position.x += this->Velocity.x * dt;
        else
            this->Destroyed = true;
    }
    else
        this->TimeToLife = 0.0f;
}

void Bullet::Spawn(glm::vec2 pos, glm::vec2 velocity, float timeToLife)
{
    this->Position = pos;
    this->Velocity = velocity;
    this->TimeToLife = timeToLife;
    this->Destroyed = false;
}

bool Bullet::CheckCollision(GameObject& go)
{
    glm::vec2 centerOne(go.Position.x + (go.Size.x / 2.0f), go.Position.y + (go.Size.y / 2.0f));
    glm::vec2 centerTwo(this->Position.x + (this->Size.x / 2.0f), this->Position.y + (this->Size.y / 2.0f));

    bool collisionX = centerOne.x + go.RadiusCollision >= centerTwo.x - 75.0f && centerTwo.x + 75.0f >= centerOne.x - go.RadiusCollision;

    bool collisionY = centerOne.y + go.RadiusCollision >= centerTwo.y - 50.0f && centerTwo.y + 50.0f >= centerOne.y - go.RadiusCollision;

    return collisionX && collisionY;
}

void Bullet::Draw(SpriteRenderer& renderer)
{
    if(!this->Destroyed)
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}
