#include "game_level.h"

#include <fstream>
#include <sstream>


void GameLevel::Load(const char* file)
{
    this->Bricks.clear();

    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> TileData;
    if (fstream)
    {
        while (std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode)
                row.push_back(tileCode);
            TileData.push_back(row);
        }
        if (TileData.size() > 0)
            this->init(TileData);
    }
}

void GameLevel::Draw(SpriteRenderer& renderer, glm::vec2 playerPos)
{
    for (auto& tile : this->Hills)
    {
        if (tile.Position.x < playerPos.x + 235.0f - 2500.0f || tile.Position.x > playerPos.x + 235.0f + 2500.0f)
            continue;
        else if (tile.Position.y < playerPos.y + 235.0f - 1500.0f || tile.Position.y > playerPos.y + 235.0f + 1500.0f)
            continue;
        if (!tile.Destroyed)
            tile.Draw(renderer);
    }
    for (GameObject& tile : this->Thorns)
        if (tile.Position.x < playerPos.x + 235.0f - 1050.0f || tile.Position.x > playerPos.x + 235.0f + 1050.0f)
            continue;
        else if (tile.Position.y < playerPos.y + 235.0f - 750.0f || tile.Position.y > playerPos.y + 235.0f + 750.0f)
            continue;
        else
        {
            if (!tile.Destroyed)
                tile.Draw(renderer);
        }
    for (GameObject& tile : this->Bricks)
        if (tile.Position.x < playerPos.x + 235.0f - 1050.0f || tile.Position.x > playerPos.x + 235.0f + 1050.0f)
            continue;
        else if (tile.Position.y < playerPos.y + 235.0f - 750.0f || tile.Position.y > playerPos.y + 235.0f + 750.0f)
            continue;
        else
        {
            if (!tile.Destroyed)
                tile.Draw(renderer);
        }
    for (GameObject& tile : this->Coins)
        if (tile.Position.x < playerPos.x + 235.0f - 1050.0f || tile.Position.x > playerPos.x + 235.0f + 1050.0f)
            continue;
        else if (tile.Position.y < playerPos.y + 235.0f - 750.0f || tile.Position.y > playerPos.y + 235.0f + 750.0f)
            continue;
        else
        {
            if (!tile.Destroyed)
                tile.Draw(renderer);
        }

}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData)
{
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); 
	
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            if (tileData[y][x] == 0)
                continue;
            else if (tileData[y][x] <= 14) // земля
            {
                glm::vec2 pos((WidthBrick * x) - x, (HeightBrick * y) - y);
                glm::vec2 size(WidthBrick, HeightBrick);
                if (tileData[y][x] == 1)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("block_earth"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }                
                else if (tileData[y][x] == 2)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("block_earth_top"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }             
                else if (tileData[y][x] == 3)
                {
                    glm::vec2 size(100, 50);
                    GameObject obj(pos, size, ResourceManager::GetTexture("block_platform"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }  
                else if (tileData[y][x] == 4)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("block_earth_left"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }  
                else if (tileData[y][x] == 5)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("block_earth_top_left"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }  
                else if (tileData[y][x] == 6)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("block_earth_top_right"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }  
                else if (tileData[y][x] == 7)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("block_earth_right"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }
                else if (tileData[y][x] == 8)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("block_earth_corner_top"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }
                else if (tileData[y][x] == 9)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("block_earth_corner_top2"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }    
                else if (tileData[y][x] == 10)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("block_earth_corner_bot"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }    
                else if (tileData[y][x] == 11)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("block_earth_corner_bot2"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }
                else if (tileData[y][x] == 12)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("block_earth_bot"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }            
                else if (tileData[y][x] == 13)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("earth_corner_top_3"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                } 
                else if (tileData[y][x] == 14)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("earth_corner_top_4"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Bricks.push_back(obj);
                }
            }
            else if (tileData[y][x] <= 17)
            {
                glm::vec2 pos((WidthBrick * x) - x, (HeightBrick * y) - y);
                glm::vec2 size(WidthBrick, HeightBrick);
                if (tileData[y][x] == 15)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("thorn_left"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Thorns.push_back(obj);
                }
                else if (tileData[y][x] == 16)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("thorn"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Thorns.push_back(obj);
                }
                else if (tileData[y][x] == 17)
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("thorn_right"), glm::vec3(1.0f, 1.0f, 1.0f));
                    this->Thorns.push_back(obj);
                }
            }
            else if (tileData[y][x] == 88)
            {   
                glm::vec2 pos(WidthBrick * x, HeightBrick * y - 1200);
                glm::vec2 size(1200.0f, 1337.0f);
                this->Hills.push_back(GameObject(pos, size, ResourceManager::GetTexture("stone"), glm::vec3(1.0f, 1.0f, 1.0f)));
            }
            else if (tileData[y][x] == 99)
            {
                glm::vec2 pos((WidthBrick* x) - x + 25.0f, (HeightBrick* y) - y);
                glm::vec2 size(WidthCoin, HeightCoin);
                GameObject obj(pos, size, ResourceManager::GetTexture("coin"), glm::vec3(1.0f, 1.0f, 1.0f));
                this->Coins.push_back(obj);
            }     
        }
    }
}
