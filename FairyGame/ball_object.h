#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"


// Класс BallObject получен из класса GameObject.
// Помимо необходимой информации о состоянии мяча в нем, в отличие от класса GameObject, присутствуют некоторые дополнительные функции
class BallObject : public GameObject
{
public:
    // Состояние мяча	
    bool Stuck;

    // Конструкторы
    BallObject();
    BallObject(glm::vec2 pos, glm::vec2 velocity, Texture2D sprite, float radiusCollision);

    // Перемещаем мяч, удерживая его в пределах границ окна (за исключением нижнего края); возвращаем новую позицию
    glm::vec2 Move(float dt, unsigned int window_width);

    // Возвращаем мяч в исходное состояние с заданным положением и скоростью
    void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif