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
		
		friend class SpriteFactory;
		void SetScale(const Vector2D& scale) {
			size.x = textureSize.x * scale.x;
			size.y = textureSize.y * scale.y;
		}

		const Vector2D GetScale() const { return size *FG::Window::aspectRatio;};
		uint16_t spriteIndex;							 
		uint16_t textureIndex;

		void SetIndex(uint16_t index)
		{
			spriteIndex = index;
		}
	};
	
	class SpriteFactory
	{
	public:
		Sprite LoadSprite(const char* filePath);
		Sprite LoadSprite(const char* filePath, int rows, int columns, const int index);
		Sprite LoadSprite(const char* filePath, int rows, int columns); // uses index 0
	};
}
