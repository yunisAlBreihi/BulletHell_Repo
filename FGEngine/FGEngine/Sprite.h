#pragma once
#include "float4.h"
#include "Texture2D.h"
#include "Vector2D.h"
#include "Window.h"
namespace FG
{
	class SpriteFactory;

	class Sprite 
	{
	private:
		Vector2D textureSize;
		Vector2D size;

	public:
		Sprite();
		friend class SpriteFactory;
		void SetScale(const Vector2D& scale) {
			SetScale(scale.x, scale.y);
		}

		void SetScale(const float x, const float y) {
			size.x = textureSize.x * x;
			size.y = textureSize.y * y;
		}


		const Vector2D GetScale() const { return size;};
		uint16_t spriteIndex;							 
		uint16_t textureIndex;

		void SetIndex(uint16_t index)
		{
			spriteIndex = index;
		}
	};
	
	class SpriteFactory
	{
	private:
		void _LoadSprite(const char* filePath, int rows, int columns, Sprite& sprite);
	public:
		SpriteFactory();

		Sprite LoadSprite(const char* filePath);
		Sprite LoadSprite(const char* filePath, int rows, int columns, const int index);
		Sprite LoadSprite(const char* filePath, int rows, int columns); // uses index 0

		std::unordered_map<std::string, Sprite> sprites;


	};
}
