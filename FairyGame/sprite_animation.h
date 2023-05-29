#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

#include "sprite_renderer.h"
#include "game_object.h"
#include "resource_manager.h"
#include <vector>
#include <ctime>

class SpriteAnimation
{
public:
    int FrameRate;
	std::vector<std::string> Sprites;
    float SecPerFrame;
    double NextFrameTime;
    int CurrentFrame;
    bool IsPlaying = true;
    bool Loop;
    bool theEnd = false;

    SpriteAnimation();
    SpriteAnimation(int frameRate, std::vector<std::string> sprites, bool loop = true);

    void animation(GameObject& go);
    void animation(std::vector<GameObject>& gos);
};

#endif