#include "Sprite.h"
#include "Logger.h"
#include "Camera.h"
#include "Texture2D.h"
namespace FG
{

	uint16_t CalculateIndexFromRect(const float4& rect)
	{
		//TODO: Implement;
		return 0;
	}

	Sprite SpriteFactory::LoadSprite(const char* filePath)
	{
		return Sprite();
	}

	Sprite SpriteFactory::LoadSprite(const char* filePath, int rows, int columns, const int index)
	{
		Sprite sprite;

		float width = 0;
		float height = 0;
		float aspectRatio = 0;

		sprite.textureIndex = Texture2DHandler::LoadTextureIntoArray(filePath, rows, columns, width, height, aspectRatio);
		sprite.spriteIndex = index;
		sprite.textureSize = FG::Vector2D(aspectRatio, 1.0f);
		sprite.SetScale(FG::Vector2D(1.0f, 1.0f));
		return sprite;
	}

	Sprite SpriteFactory::LoadSprite(const char* filePath, int rows, int columns)
	{
		Sprite sprite;
		float width = 0;
		float height = 0;
		float aspectRatio = 0;

		sprite.textureIndex = Texture2DHandler::LoadTextureIntoArray(filePath, rows, columns, width, height, aspectRatio);
		sprite.spriteIndex = 0;	
		sprite.textureSize = FG::Vector2D(aspectRatio, 1.0f);
		sprite.SetScale(FG::Vector2D(1.0f, 1.0f));
		return sprite;
	}

}
