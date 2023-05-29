#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"


// ����� BallObject ������� �� ������ GameObject.
// ������ ����������� ���������� � ��������� ���� � ���, � ������� �� ������ GameObject, ������������ ��������� �������������� �������
class BallObject : public GameObject
{
public:
    // ��������� ����	
    bool Stuck;

    // ������������
    BallObject();
    BallObject(glm::vec2 pos, glm::vec2 velocity, Texture2D sprite, float radiusCollision);

    // ���������� ���, ��������� ��� � �������� ������ ���� (�� ����������� ������� ����); ���������� ����� �������
    glm::vec2 Move(float dt, unsigned int window_width);

    // ���������� ��� � �������� ��������� � �������� ���������� � ���������
    void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif