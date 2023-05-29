#ifndef BULLET_H
#define BULLET_H

#include "game_object.h"

class Bullet : public GameObject
{
public:
    float TimeToLife = 0.0f;
    Bullet();
    Bullet(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D sprite, float radiusCollision, float timeLife, bool destroyed = true);
    void Update(float dt);
    void Spawn(glm::vec2 pos, glm::vec2 velocity, float timeToLife);
    bool CheckCollision(GameObject& go);
    void Draw(SpriteRenderer& sprite);
};

#endif 
