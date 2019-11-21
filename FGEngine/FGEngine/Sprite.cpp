#include "Sprite.h"
#include "Logger.h"
#include "Camera.h"
#include "Texture2D.h"
namespace FG
{

	Sprite::Sprite()
	{
		textureSize = { 1.0f, 1.0f };
	}

	uint16_t CalculateIndexFromRect(const float4& rect)
	{
		//TODO: Implement;
		return 0;
	}

	void SpriteFactory::_LoadSprite(const char* filePath, int rows, int columns, Sprite& sprite)
	{
		if (sprites.find(filePath) != sprites.end())
		{
			sprite = sprites.at(filePath);
			return;
		}

		float width = 0;
		float height = 0;
		float aspectRatio = 0;

		sprite.textureIndex = Texture2DHandler::LoadTextureIntoArray(filePath, rows, columns, width, height, aspectRatio);
		sprite.textureSize = FG::Vector2D(1.0f, 1.0f);
		sprite.SetScale(1.0f, 1.0f);

		sprites.emplace(filePath, sprite);
	}

	SpriteFactory::SpriteFactory()
	{
		sprites = std::unordered_map<std::string, Sprite>();
	}

	Sprite SpriteFactory::LoadSprite(const char* filePath)
	{
		Sprite sprite;
		_LoadSprite(filePath, 1, 1, sprite);
		sprite.spriteIndex = 0;
		return sprite;
	}

	Sprite SpriteFactory::LoadSprite(const char* filePath, int rows, int columns, const int index)
	{
		Sprite sprite;
		_LoadSprite(filePath, rows, columns, sprite);
		sprite.spriteIndex = index;
		return sprite;
	}

	Sprite SpriteFactory::LoadSprite(const char* filePath, int rows, int columns)
	{
		Sprite sprite;
		_LoadSprite(filePath, rows, columns, sprite);
		sprite.spriteIndex = 0;
		return sprite;
	}

}
