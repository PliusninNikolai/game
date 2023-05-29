#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"
#include "sprite_animation.h"


class GameLevel
{
public:
    std::vector<GameObject> Bricks;
    std::vector<GameObject> Coins;
    std::vector<GameObject> Thorns;
    std::vector<GameObject> Hills;
    float WidthBrick = 100.0f;
    float HeightBrick = 100.0f;
    float WidthCoin = 52.0f;
    float HeightCoin = 52.0f;


    GameLevel() { }

    void Load(const char* file);

    void Draw(SpriteRenderer& renderer, glm::vec2 playerPos);
private:
    void init(std::vector<std::vector<unsigned int>> tileData);
};

#endif
