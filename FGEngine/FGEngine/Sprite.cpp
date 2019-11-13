#include "Sprite.h"
#include "Logger.h"
#include "Camera.h"
#include "Texture2D.h"
namespace FG
{

	Sprite SpriteFactory::LoadSprite(const char* filePath, float4 textureData, const int index)
	{
		Sprite sprite;
		sprite.textureIndex = Texture2DHandler::LoadTextureIntoArray(filePath, textureData);
		sprite.spriteIndex = index;
		return sprite;
	}
	Sprite SpriteFactory::LoadSprite(const char* filePath, float4 textureData)
	{
		Sprite sprite;
		sprite.textureIndex = Texture2DHandler::LoadTextureIntoArray(filePath, textureData);
		sprite.spriteIndex = 0;
		return sprite;
	}

	uint16_t CalculateIndexFromRect(const float4& rect)
	{
		//TODO: Implement;
		return 0;
	}

}
