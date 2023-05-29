#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_level.h"


enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_RESTART
};

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision; 

static glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
static glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


const glm::vec2 PLAYER_SIZE(470.0f, 470.0f);

const glm::vec2 BULLET_SIZE(100.0f, 100.0f);

const glm::vec2 BULLET_VELOCITY(-600.0f, 0.0f);




class Game
{
public:
    
    GameState State;
    bool Keys[1024];
    bool KeysProcessed[1024];
    unsigned int Width, Height;
    std::vector<GameLevel> Levels;
    unsigned int Level;
    unsigned int Lives = 3;
    unsigned int totalCoins = 0;

    
    Game(unsigned int width, unsigned int height);

    ~Game();

    void Init();

    
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void DoCollisions();
    void HeroDead();
    void GetCoin();
    void CheckDamageHero();
    void ResetLevel();
};

#endif

