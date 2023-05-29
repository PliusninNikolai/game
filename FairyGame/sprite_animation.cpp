#include "sprite_animation.h"

SpriteAnimation::SpriteAnimation()
{
}

SpriteAnimation::SpriteAnimation(int frameRate, std::vector<std::string> sprites, bool loop)
	: FrameRate(frameRate), Sprites(sprites), Loop(loop)
{
	SecPerFrame = 1.0f / FrameRate;
	CurrentFrame = 0;
	NextFrameTime = (double)clock() / CLOCKS_PER_SEC;
}

void SpriteAnimation::animation(GameObject& go)
{
	if (IsPlaying) 
	{
		if (NextFrameTime > ((double)clock() / CLOCKS_PER_SEC) + 0.001)
		{
			return;
		}
		NextFrameTime = (double)clock() / CLOCKS_PER_SEC;
		if (CurrentFrame >= Sprites.size())
		{
			if (Loop)
			{
				this->CurrentFrame = 0;
			}
			else
			{
				this->CurrentFrame = 0;
				this->theEnd = true;
				this->IsPlaying = false;
			}
			return;
		}
		go.Sprite = ResourceManager::GetTexture(Sprites[CurrentFrame]);
		NextFrameTime += SecPerFrame;
		CurrentFrame++;
	}
}

void SpriteAnimation::animation(std::vector<GameObject>& gos)
{
	if (IsPlaying)
	{
		if (NextFrameTime > glfwGetTime()) return;
		NextFrameTime = glfwGetTime();
		if (CurrentFrame >= Sprites.size())
		{
			this->CurrentFrame = 0;
		}
		for (GameObject& go : gos)
		go.Sprite = ResourceManager::GetTexture(Sprites[CurrentFrame]);
		NextFrameTime += SecPerFrame;
		CurrentFrame++;
	}
}
