#include "game_object.h"

GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), RadiusCollision(1.0f), ChekCollision(1.0f, 1.0f), Destroyed(false) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity, float radiusCollision, float rotation, bool destroyed)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(rotation), Sprite(sprite), RadiusCollision(radiusCollision), ChekCollision(radiusCollision * 2.0f, radiusCollision * 2.0f), Destroyed(destroyed) { }

void GameObject::Draw(SpriteRenderer& renderer)
{
    if(!this->Destroyed)
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}
