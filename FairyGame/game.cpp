#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "ball_object.h"
#include "hero.h"
#include "sprite_animation.h"
#include "mob_flower.h"
#include "Bullet.h"
#include "shield.h"
#include "text_renderer.h"
#include <iostream>
#include <irrKlang/irrKlang.h>
using namespace irrklang;


ISoundEngine* SoundEngine = createIrrKlangDevice();

SpriteRenderer* Renderer;
SpriteRenderer* RendererWindow;

TextRenderer* Text;

SpriteAnimation* AnimationHeroIdle;
SpriteAnimation* AnimationHeroAttack;
SpriteAnimation* AnimationHeroWalk;
SpriteAnimation* AnimationHeroDie;
SpriteAnimation* AnimationHeroAppear;
SpriteAnimation* AnimationHeroDisappear;

SpriteAnimation* AnimationTree;
SpriteAnimation* AnimationPortal;

SpriteAnimation* AnimationCoin;

SpriteAnimation* AnimationMonsterAttack;
SpriteAnimation* AnimationMonsterIdle;
SpriteAnimation* AnimationMonsterDie;

SpriteAnimation* AnimationShieldAppear;
SpriteAnimation* AnimationShieldIdle;
SpriteAnimation* AnimationShieldDisappear;
SpriteAnimation* AnimationShieldDisappearAttack;

GameObject* Tree;
GameObject* Portal;


Shield* ShieldPlayer;
Hero* Player;
std::vector<MobFlower> Flowers;
Bullet* MobBullet;
Bullet* HeroBullet;
std::vector<GameObject> coins;

bool theEnd = false;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_MENU), Keys(), KeysProcessed(), Width(width), Height(height), Level(0)
{

}

Game::~Game()
{
    delete Text;
    delete Tree;
    delete Portal;
    delete MobBullet;
    delete HeroBullet;
    delete ShieldPlayer;
    delete Renderer;
    delete RendererWindow;
    delete Player;
    delete AnimationCoin;
    delete AnimationHeroIdle;
    delete AnimationHeroWalk;
    delete AnimationHeroAttack;
    delete AnimationHeroDie;
    delete AnimationHeroAppear;
    delete AnimationHeroDisappear;
    delete AnimationMonsterIdle;
    delete AnimationMonsterAttack;
    delete AnimationMonsterDie;
    delete AnimationShieldAppear;
    delete AnimationShieldIdle;
    delete AnimationShieldDisappear;
    delete AnimationShieldDisappearAttack;
    delete SoundEngine;
}

void CoinAnimationResourceManager()
{
    std::vector<std::string> coinIdle;
    std::string png = ".png";
    for (int i = 0; i < 130; i++)
    {
        std::string s = "../textures/coin/icon_idle_" + std::to_string(i) + png;
        std::string t = "coin_idle" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        coinIdle.push_back(t);
    }

    AnimationCoin = new SpriteAnimation(60, coinIdle);
}

void HeroAnimationResourceManager()
{
    std::vector<std::string> heroIdle;
    std::string png = ".png";
    for (int i = 0; i < 80; i++)
    {
        std::string s = "../textures/hero/idle/hero_idle_" + std::to_string(i) + png;
        std::string t = "hero_idle" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        heroIdle.push_back(t);
    }

    std::vector<std::string> heroWalk;
    for (int i = 0; i < 80; i++)
    {
        std::string s = "../textures/hero/walk/hero_walk_" + std::to_string(i) + png;
        std::string t = "hero_walk" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        heroWalk.push_back(t);
    }    

    std::vector<std::string> heroAttack;
    for (int i = 0; i < 60; i++)
    {
        std::string s = "../textures/hero/attack/hero_attack_" + std::to_string(i) + png;
        std::string t = "hero_attack" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        heroAttack.push_back(t);
    } 
    
    std::vector<std::string> heroDie;
    for (int i = 0; i < 54; i++)
    {
        std::string s = "../textures/hero/die/hero_die_" + std::to_string(i) + png;
        std::string t = "hero_die" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        heroDie.push_back(t);
    }    
    
    std::vector<std::string> heroAppear;
    for (int i = 0; i < 196; i++)
    {
        std::string s = "../textures/hero/appear/hero_appear_" + std::to_string(i) + png;
        std::string t = "hero_appear" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        heroAppear.push_back(t);
    }   
    std::vector<std::string> heroDisappear;
    for (int i = 0; i < 64; i++)
    {
        std::string s = "../textures/hero/disappear/hero_disappear_" + std::to_string(i) + png;
        std::string t = "hero_disappear_" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        heroDisappear.push_back(t);
    }

    AnimationHeroIdle = new SpriteAnimation(60, heroIdle);
    AnimationHeroWalk = new SpriteAnimation(60, heroWalk);
    AnimationHeroAttack = new SpriteAnimation(60, heroAttack, false);
    AnimationHeroDie = new SpriteAnimation(60, heroDie, false);
    AnimationHeroAppear = new SpriteAnimation(60, heroAppear, false);
    AnimationHeroDisappear = new SpriteAnimation(60, heroDisappear, false);
}

void TreeAnimationResourceManager()
{
    std::vector<std::string> treeAppear;
    std::string png = ".png";
    for (int i = 0; i < 178; i++)
    {
        std::string s = "../textures/tree/tree_hero_appear_" + std::to_string(i) + png;
        std::string t = "tree_appear" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        treeAppear.push_back(t);
    }

    AnimationTree = new SpriteAnimation(60, treeAppear, false);
}

void PortalAnimationResourceManager()
{
    std::vector<std::string> PortalIdle;
    std::string png = ".png";
    for (int i = 0; i < 140; i++)
    {
        std::string s = "../textures/portal/portal_" + std::to_string(i) + png;
        std::string t = "portal_" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        PortalIdle.push_back(t);
    }

    AnimationPortal = new SpriteAnimation(60, PortalIdle);
}

void MonsterAnimationResourceManager()
{
    std::vector<std::string> monsterIdle;
    std::string png = ".png";
    for (int i = 0; i < 80; i++)
    {
        std::string s = "../textures/monster/monster_idle/monster_idle_" + std::to_string(i) + png;
        std::string t = "monster_idle" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        monsterIdle.push_back(t);
    }  
    std::vector<std::string> monsterAttack;
    for (int i = 0; i < 42; i++)
    {
        std::string s = "../textures/monster/monster_attack/monster_attack_" + std::to_string(i) + png;
        std::string t = "monster_attack" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        monsterAttack.push_back(t);
    }
    std::vector<std::string> monsterDie;
    for (int i = 0; i < 66; i++)
    {
        std::string s = "../textures/monster/monster_die/monster_die_" + std::to_string(i) + png;
        std::string t = "monster_die" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        monsterDie.push_back(t);
    }

    AnimationMonsterIdle = new SpriteAnimation(60, monsterIdle);
    AnimationMonsterAttack = new SpriteAnimation(60, monsterAttack, false);
    AnimationMonsterDie = new SpriteAnimation(60, monsterDie, false);
}

void ShieldAnimationResourceManager()
{
    std::vector<std::string> shieldIdle;
    std::string png = ".png";
    for (int i = 0; i < 80; i++)
    {
        std::string s = "../textures/hero/shield/shield_idle/shield_idle_" + std::to_string(i) + png;
        std::string t = "shield_idle" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        shieldIdle.push_back(t);
    }  
    std::vector<std::string> shieldAppear;
    for (int i = 0; i < 76; i++)
    {
        std::string s = "../textures/hero/shield/shield_appear/shield_appear_" + std::to_string(i) + png;
        std::string t = "shield_appear" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        shieldAppear.push_back(t);
    }
    std::vector<std::string> shieldDisappear;
    for (int i = 0; i < 54; i++)
    {
        std::string s = "../textures/hero/shield/shield_disappear/shield_disappear_" + std::to_string(i) + png;
        std::string t = "shield_disappear" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        shieldDisappear.push_back(t);
    }   
    std::vector<std::string> shieldDisappearAttack;
    for (int i = 0; i < 28; i++)
    {
        std::string s = "../textures/hero/shield/shield_disappear_attack/shield_disappear_attack_" + std::to_string(i) + png;
        std::string t = "shield_disappear_attack" + std::to_string(i);
        ResourceManager::LoadTexture(s.c_str(), true, t);
        shieldDisappearAttack.push_back(t);
    }
    
    AnimationShieldIdle = new SpriteAnimation(60, shieldIdle);
    AnimationShieldAppear = new SpriteAnimation(60, shieldAppear, false);
    AnimationShieldDisappear = new SpriteAnimation(60, shieldDisappear, false);
    AnimationShieldDisappearAttack = new SpriteAnimation(60, shieldDisappearAttack, false);
}

void EarthResourceManager()
{
    ResourceManager::LoadTexture("../textures/Earth/earth.png", false, "block_earth");
    ResourceManager::LoadTexture("../textures/Earth/earth_top.png", true, "block_earth_top");
    ResourceManager::LoadTexture("../textures/Earth/earth_left.png", true, "block_earth_left");
    ResourceManager::LoadTexture("../textures/Earth/earth_right.png", true, "block_earth_right");
    ResourceManager::LoadTexture("../textures/Earth/earth_top_left.png", true, "block_earth_top_left");
    ResourceManager::LoadTexture("../textures/Earth/earth_top_right.png", true, "block_earth_top_right");
    ResourceManager::LoadTexture("../textures/Earth/platform.png", true, "block_platform");
    ResourceManager::LoadTexture("../textures/Earth/earth_corner_top.png", true, "block_earth_corner_top");
    ResourceManager::LoadTexture("../textures/Earth/earth_corner_top2.png", true, "block_earth_corner_top2");
    ResourceManager::LoadTexture("../textures/Earth/earth_corner_bot.png", true, "block_earth_corner_bot");
    ResourceManager::LoadTexture("../textures/Earth/earth_corner_bot2.png", true, "block_earth_corner_bot2");
    ResourceManager::LoadTexture("../textures/Earth/earth_bot.png", true, "block_earth_bot");
    ResourceManager::LoadTexture("../textures/Earth/earth_corner_top_3.png", true, "earth_corner_top_3");
    ResourceManager::LoadTexture("../textures/Earth/earth_corner_top_4.png", true, "earth_corner_top_4");
    ResourceManager::LoadTexture("../textures/Thorn/thorn.png", true, "thorn");
    ResourceManager::LoadTexture("../textures/Thorn/thorn2.png", true, "thorn_right");
    ResourceManager::LoadTexture("../textures/Thorn/thorn3.png", true, "thorn_left");
}

void SpawnFlowers()
{
    Flowers.push_back(MobFlower(glm::vec2(3500.0f, 1345.0f), glm::vec2(632.0f, 629.0f), glm::vec2(0.0f), ResourceManager::GetTexture("monster"), 150.0f, *AnimationMonsterIdle, *AnimationMonsterAttack, *AnimationMonsterDie));
    Flowers.push_back(MobFlower(glm::vec2(6500.0f, 1345.0f), glm::vec2(632.0f, 629.0f), glm::vec2(0.0f), ResourceManager::GetTexture("monster"), 150.0f, *AnimationMonsterIdle, *AnimationMonsterAttack, *AnimationMonsterDie));
    Flowers.push_back(MobFlower(glm::vec2(2500.0f, 2735.0f), glm::vec2(632.0f, 629.0f), glm::vec2(0.0f), ResourceManager::GetTexture("monster"), 150.0f, *AnimationMonsterIdle, *AnimationMonsterAttack, *AnimationMonsterDie, 800.0f, 180.0f));
    Flowers.push_back(MobFlower(glm::vec2(6180.0f, 3425.0f), glm::vec2(632.0f, 629.0f), glm::vec2(0.0f), ResourceManager::GetTexture("monster"), 150.0f, *AnimationMonsterIdle, *AnimationMonsterAttack, *AnimationMonsterDie));
    Flowers.push_back(MobFlower(glm::vec2(8815.0f, 2630.0f), glm::vec2(632.0f, 629.0f), glm::vec2(0.0f), ResourceManager::GetTexture("monster"), 150.0f, *AnimationMonsterIdle, *AnimationMonsterAttack, *AnimationMonsterDie));
    Flowers.push_back(MobFlower(glm::vec2(11115.0f, 2635.0f), glm::vec2(632.0f, 629.0f), glm::vec2(0.0f), ResourceManager::GetTexture("monster"), 150.0f, *AnimationMonsterIdle, *AnimationMonsterAttack, *AnimationMonsterDie));
    Flowers.push_back(MobFlower(glm::vec2(8925.0f, 1445.0f), glm::vec2(632.0f, 629.0f), glm::vec2(0.0f), ResourceManager::GetTexture("monster"), 150.0f, *AnimationMonsterIdle, *AnimationMonsterAttack, *AnimationMonsterDie));

}

void Game::Init()
{
   
    ResourceManager::LoadShader("../shaders/sprite.vs", "../shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::LoadShader("../shaders/window.vs", "../shaders/window.frag", nullptr, "window");

    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    ResourceManager::GetShader("window").Use().SetInteger("image", 0);
    ResourceManager::GetShader("window").SetMatrix4("projection", projection);

    ResourceManager::GetShader("sprite").SetMatrix4("view", view);

    EarthResourceManager();
    Text = new TextRenderer(this->Width, this->Height);
    Text->Load("../fonts/ocraext.TTF", 24);
    
    ResourceManager::LoadTexture("../textures/bg.png", true, "background");
    ResourceManager::LoadTexture("../textures/cloud_1.png", true, "cloud_1");
    ResourceManager::LoadTexture("../textures/cloud_2.png", true, "cloud_2");
    ResourceManager::LoadTexture("../textures/tree/tree_hero_appear_0.png", true, "tree_hero_appear_0");
    

    ResourceManager::LoadTexture("../textures/stone.png", true, "stone");

    ResourceManager::LoadTexture("../textures/hero/hero_fairy.png", true, "hero_fairy");

    ResourceManager::LoadTexture("../textures/monster/monster_idle/monster_idle_0.png", true, "monster");
    ResourceManager::LoadTexture("../textures/monster_1_bomb.png", true, "monster_1_bomb");
    ResourceManager::LoadTexture("../textures/particles/part3.png", true, "hero_bullet");

    ResourceManager::LoadTexture("../textures/particles/part2.png", true, "particle");
    ResourceManager::LoadTexture("../textures/coin.png", true, "coin");
    ResourceManager::LoadTexture("../textures/portal/portal_0.png", true, "portal");
    ResourceManager::LoadTexture("../textures/hero/shield/shield.png", true, "shield");
    ResourceManager::LoadTexture("../textures/decoration1.png", true, "decoration1");


    CoinAnimationResourceManager();
    HeroAnimationResourceManager();
    ShieldAnimationResourceManager();
    MonsterAnimationResourceManager();
    TreeAnimationResourceManager();
    PortalAnimationResourceManager();

    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    RendererWindow = new SpriteRenderer(ResourceManager::GetShader("window"));

    
    GameLevel one; one.Load("../levels/one.lvl");
    this->Levels.push_back(one);
    this->Level = 0;


    Portal = new GameObject(glm::vec2(12000.0f, 825.0f), glm::vec2(470.0f, 470.0f), ResourceManager::GetTexture("portal"));
    Tree = new GameObject(glm::vec2(1600.0f, 1070.0f), glm::vec2(862.0f, 752.0f), ResourceManager::GetTexture("tree_hero_appear_0"));
    Player = new Hero(glm::vec2(2000.0f, 1220.0f), PLAYER_SIZE, glm::vec2(0.0f), ResourceManager::GetTexture("hero_fairy"), 180.0f);
    ShieldPlayer = new Shield(glm::vec2(2000.0f, 1220.0f), glm::vec2(500.0f), ResourceManager::GetTexture("shield"));

    HeroBullet = new Bullet(glm::vec2(Player->Position.x - 50.0f, Player->Position.y + 140.0f), BULLET_SIZE, BULLET_VELOCITY, ResourceManager::GetTexture("hero_bullet"), 50.0f, 6.0f);
    MobBullet = new Bullet(glm::vec2(0.0f), BULLET_SIZE, BULLET_VELOCITY, ResourceManager::GetTexture("monster_1_bomb"), 50.0f, 6.0f);
    SpawnFlowers();

    SoundEngine->play2D("../audio/main_sound.mp3", true);
}

Collision CheckCollision(Hero& one, GameObject& two);
Direction VectorDirection(glm::vec2 closestd);
void SpawnHeroBullet();
void MobAt(MobFlower& Flower);

void Game::Update(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        if (AnimationHeroDie->theEnd)
        {
            AnimationHeroDie->theEnd = false;
            AnimationHeroDie->IsPlaying = true;
            Player->Reset(glm::vec2(2000.0f, 1220.0f), glm::vec2(0.0f, 0.0f));
            this->ResetLevel();
            this->State = GAME_RESTART;
        }
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ResourceManager::GetShader("sprite").SetMatrix4("view", view);
        Player->UpdateDirection(dt);
        ShieldPlayer->Update(*Player, dt);
        if (Player->Attack && AnimationHeroAttack->CurrentFrame == 40)
            SpawnHeroBullet();
        for (auto& Flower : Flowers)
        {
            Flower.Update(dt);
            if (!Flower.Destroyed && Flower.CooldownAttack < 0.0f && MobBullet->Destroyed)
                MobAt(Flower);
            if (HeroBullet->CheckCollision(Flower) && !Flower.Destroyed && !HeroBullet->Destroyed)
            {
                HeroBullet->Destroyed = true;
                Flower.Destroyed = true;
                SoundEngine->play2D("../audio/monster_die.mp3", false);
            }
        }
        MobBullet->Update(dt);
        HeroBullet->Update(dt);
        this->CheckDamageHero();
        this->DoCollisions();
        this->GetCoin();
        if (AnimationHeroDisappear->theEnd)
            this->State = GAME_WIN;
        if (Player->Position.x > Portal->Position.x)
        {
            if (!theEnd)
            {
                SoundEngine->play2D("../audio/hero_disappear.mp3", false);
                Player->DisAppear = true;
                theEnd = true;
            }
        }
    }
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE && !Player->Destroyed && !Player->Appear && !Player->DisAppear)
    {
        if (this->Keys[GLFW_KEY_A])
        {
                Player->Rotation = 180.0f;
                Player->Velocity.x = -HERO_VELOCITY.x;
        }
        if (this->Keys[GLFW_KEY_D])
        {
                Player->Rotation = 0.0f; 
                Player->Velocity.x = HERO_VELOCITY.x;
        }
        if (!this->Keys[GLFW_KEY_A] && !this->Keys[GLFW_KEY_D])
            Player->Velocity.x = 0.0f;
        if (this->Keys[GLFW_KEY_W])
        {
            if (Player->Jumping || Player->Falling)
                return;

            Player->Velocity.y = HERO_VELOCITY.y;
            Player->Jumping = true;
            this->KeysProcessed[GLFW_KEY_W] = true;
        }
        if (this->Keys[GLFW_KEY_E] && !this->KeysProcessed[GLFW_KEY_E])
        {
            this->KeysProcessed[GLFW_KEY_E] = true;
            if (HeroBullet->TimeToLife > 0)
                return;
            if (AnimationHeroAttack->theEnd)
            {
                AnimationHeroAttack->IsPlaying = true;
                AnimationHeroAttack->theEnd = false;
            }
            SoundEngine->play2D("../audio/hero_attack.mp3", false);
            Player->Attack = true;
        }
        if (this->Keys[GLFW_KEY_Q] && !this->KeysProcessed[GLFW_KEY_Q])
        {
            this->KeysProcessed[GLFW_KEY_Q] = true;
            if (ShieldPlayer->TimeLife > 0.0f)
                return;
            ShieldPlayer->TimeLife = 5.0f;
            SoundEngine->play2D("../audio/shield_appear.mp3", false);
            ShieldPlayer->State = Shield::States::APPEAR;
        }
    }

    if (this->State == GAME_MENU || this->State == GAME_RESTART)
    {
        if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
        {
            SoundEngine->play2D("../audio/hero_appear.mp3", false);
            this->KeysProcessed[GLFW_KEY_ENTER] = true;
            this->State = GAME_ACTIVE;
        }
    }
}

void SpawnHeroBullet()
{
    if (Player->Rotation == 180.0f)
    {
        HeroBullet->Spawn(glm::vec2(Player->Position.x - 50.0f, Player->Position.y + 140.0f), BULLET_VELOCITY, 2.0f);
    }
    else
    {
        HeroBullet->Spawn(glm::vec2(Player->Position.x + Player->Size.x, Player->Position.y + 140.0f), -BULLET_VELOCITY, 2.0f);
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        
        cameraPos = glm::vec3(Player->Position.x - (this->Width - Player->Size.x) / 2, Player->Position.y - (this->Height - Player->Size.y) / 2, 0.0f);

        Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(Player->Position.x - this->Width/2, Player->Position.y - this->Height / 2), glm::vec2(3840, 2160), 0.0f);
        Renderer->DrawSprite(ResourceManager::GetTexture("decoration1"), glm::vec2(11450.0f, 600.0f), glm::vec2(1155, 671), 0.0f);
       

        Tree->Draw(*Renderer);
        Portal->Draw(*Renderer);
        
        AnimationCoin->animation(this->Levels[this->Level].Coins);
        AnimationTree->animation(*Tree);
        AnimationPortal->animation(*Portal);
        ShieldPlayer->Animation(AnimationShieldAppear, AnimationShieldIdle, AnimationShieldDisappear, AnimationShieldDisappearAttack);
        ShieldPlayer->Draw(*Renderer);
        Player->Animation(AnimationHeroIdle, AnimationHeroWalk, AnimationHeroAttack, AnimationHeroDie, AnimationHeroAppear, AnimationHeroDisappear);
        Player->Draw(*Renderer);       
        for (MobFlower& Flower : Flowers)
        {
            Flower.Draw(*Renderer);
            Flower.Animation();
        }
        MobBullet->Draw(*Renderer);
        HeroBullet->Draw(*Renderer);
        this->Levels[this->Level].Draw(*Renderer, Player->Position);

    }
    else if (this->State == GAME_MENU)
    {
        RendererWindow->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(2000, 1100), 0.0f);
        Text->RenderText("Press ENTER to start", this->Width / 2.0f - 130.0f, this->Height / 2.0f - 100.0f, 1.0f);
        Text->RenderText("Press W A D to move", this->Width / 2.0f - 130.0f, this->Height / 2.0f - 50.0f, 1.0f);
        Text->RenderText("Press E to attack", this->Width / 2.0f - 130.0f, this->Height / 2.0f, 1.0f);
        Text->RenderText("Press Q to protection", this->Width / 2.0f - 130.0f, this->Height / 2.0f + 50.0f, 1.0f);
        Text->RenderText("Press ESC to quit", this->Width / 2.0f - 130.0f, this->Height / 2.0f + 100.0f, 1.0f);
    } 
    else if (this->State == GAME_WIN)
    {
        RendererWindow->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(2000, 1100), 0.0f);
        Text->RenderText("You Winner!!!", this->Width / 2.0f - 50.0f, this->Height / 2.0f - 50.0f, 1.0f);
        Text->RenderText("Your coins: " + std::to_string(totalCoins), this->Width / 2.0f - 60.0f, this->Height / 2.0f , 1.0f);

    }
    else if (this->State == GAME_RESTART)
    {
        RendererWindow->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(2000, 1100), 0.0f);
        Text->RenderText("You Dead :C", this->Width / 2.0f - 50.0f, this->Height / 2.0f - 50.0f, 1.0f);
        Text->RenderText("Press Enter to restart", this->Width / 2.0f - 130.0f, this->Height / 2.0f, 1.0f);
    }
}

void Game::DoCollisions()
{
    for (GameObject& box : this->Levels[this->Level].Hills)
    {
        Collision collision = CheckCollision(*Player, box);
        if (std::get<0>(collision))
        {
            Direction dir = std::get<1>(collision);
            glm::vec2 diff_vector = std::get<2>(collision);
            if (dir == LEFT || dir == RIGHT)
            {
                // Перемещение
                float penetration = Player->RadiusCollision - std::abs(diff_vector.x);
                if (dir == LEFT)
                {
                    Player->Position.x += penetration;
                }
                else
                {
                    Player->Position.x -= penetration;
                }
            }
            else
            {
                float penetration = Player->RadiusCollision - std::abs(diff_vector.y);
                if (dir == UP)
                {
                    if (penetration > 10.0f)
                        Player->Position.y -= penetration;
                    Player->IsGround = true;
                    Player->Falling = false;
                    return;
                }
                else
                {
                    Player->Position.y += penetration;
                    Player->Falling = true;
                    Player->Jumping = false;
                }
            }
        }
        else
        {
            Player->IsGround = false;
            Player->Falling = true;
        }
    }
    for (GameObject& box : this->Levels[this->Level].Bricks)
    {
        if (box.Position.x > Player->Position.x + Player->Size.x || box.Position.x + box.Size.x < Player->Position.x)
            continue;

        if (box.Position.y + box.Size.y < Player->Position.y || box.Position.y > Player->Position.y + Player->Size.y)
            continue;
            Collision collision = CheckCollision(*Player, box);
            if (std::get<0>(collision))
            {
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT) 
                {
                    // Перемещение
                    float penetration = Player->RadiusCollision - std::abs(diff_vector.x);
                    if (dir == LEFT)
                    {
                        Player->Position.x += penetration; 
                    }
                    else
                    {
                        Player->Position.x -= penetration;
                    }
                }
                else 
                {
                    float penetration = Player->RadiusCollision - std::abs(diff_vector.y);
                    if (dir == UP)
                    {
                        if (penetration > 10.0f)
                            Player->Position.y -= penetration;
                        Player->IsGround = true;
                        Player->Falling = false;
                        return;
                    }
                    else
                    {
                        Player->Position.y += penetration;
                        Player->Falling = true;
                        Player->Jumping = false;
                    }
                }
            }
            else
            {
                Player->IsGround = false;
                Player->Falling = true;
            }
    }  

}

void Game::GetCoin()
{
    for (GameObject& coin : this->Levels[this->Level].Coins)
    {
        if (coin.Position.x > Player->Position.x + Player->Size.x || coin.Position.x + coin.Size.x < Player->Position.x)
            continue;

        if (coin.Position.y + coin.Size.y < Player->Position.y || coin.Position.y > Player->Position.y + Player->Size.y)
            continue;
        if (Player->CheckCollision(coin))
        {
            if (!coin.Destroyed)
            {
                SoundEngine->play2D("../audio/coin.mp3", false);
                coin.Destroyed = true;
                totalCoins++;
            }
        }
    }   
}

void MobAt(MobFlower& Flower)
{
    Flower.attack.IsPlaying = true;
    if (Flower.CheckHero(*Player))
    {
        Flower.Attack = true; 
        if (Flower.attack.CurrentFrame == 32)
        {
            SoundEngine->play2D("../audio/monster_attack.mp3", false);
            if (Flower.Rotation == 0.0f)
            {
                MobBullet->Spawn(glm::vec2(Flower.Position.x + 100.0f, Flower.Position.y + 190.0f), BULLET_VELOCITY, 2.0f);
            }
            else
            {
                MobBullet->Spawn(glm::vec2(Flower.Position.x + 370.0f, Flower.Position.y + 190.0f), -BULLET_VELOCITY, 2.0f);
            }
        }
    }
}

void Game::HeroDead()
{
    if (!Player->Destroyed)
    {
        SoundEngine->play2D("../audio/hero_die.mp3", false);
        Player->Destroyed = true;
    }
}

void Game::CheckDamageHero()
{
    if (MobBullet->CheckCollision(*ShieldPlayer))
    {
        if (!MobBullet->Destroyed && !ShieldPlayer->Destroyed)
        {
            SoundEngine->play2D("../audio/shield_disappear_attack.mp3", false);
            MobBullet->Destroyed = true;
            ShieldPlayer->State = Shield::States::DISAPPEAR_ATTACK;
        }
    }
    if (Player->CheckCollision(*MobBullet))
    {
        if (!MobBullet->Destroyed)
        {
            MobBullet->Destroyed = true; 
            HeroDead();
        }
    }
    for (auto& Flower : Flowers)
        if (Player->CheckCollision(Flower) && !Flower.Destroyed)
        {
            HeroDead();
        }
    for (GameObject& thorn : this->Levels[this->Level].Thorns)
    {
        if (thorn.Position.x > Player->Position.x + Player->Size.x || thorn.Position.x + thorn.Size.x < Player->Position.x)
            continue;

        if (thorn.Position.y + thorn.Size.y < Player->Position.y || thorn.Position.y > Player->Position.y + Player->Size.y)
            continue;
        if (Player->CheckCollision(thorn))
        {
            HeroDead();
        }
    }
}

void Game::ResetLevel()
{
    this->totalCoins = 0;
    for (auto& Flower : Flowers)
        Flower.Reset();
    for (auto& coin : this->Levels[this->Level].Coins)
        coin.Destroyed = false;
    MobBullet->Destroyed = true;
    HeroBullet->Destroyed = true;
}

Collision CheckCollision(Hero& one, GameObject& two) 
{
    glm::vec2 center(one.Position.x + (one.Size.x /2.0f), one.Position.y + (one.Size.y /2.0f));


    glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);


    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);


    glm::vec2 closest = aabb_center + clamped;


    difference = closest - center;

    if (glm::length(difference) < one.RadiusCollision) 
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	
        glm::vec2(1.0f, 0.0f),	
        glm::vec2(0.0f, -1.0f),	
        glm::vec2(-1.0f, 0.0f)	
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}
