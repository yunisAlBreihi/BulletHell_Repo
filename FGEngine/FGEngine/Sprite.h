#pragma once
#include "float4.h"
#include "Texture2D.h"
#include "Vector2D.h"
namespace FG
{
	class Sprite 
	{
	public:
		Sprite() {}
		Vector2D size;
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
		//textureData.x is 1.0f / texture width * width of the texture in pixels
		//textureData.x is 1.0f / texture height * height of the texture in pixels
		//ex. a texture with size 2048x2048, with 256x256 sized sprites 
		//x = 1.0f / 2048.0f * 256.0f;
		//y = 1.0f / 2048.0f * 256.0f;
		//z and w  = number of sprites in a row/col
		//in this example, it would be 8
		//2048 / 256 = 8;
		//index is the index of the sprite you want to use
		//rect is used for the same thing, but if you don't want to calculate the index and instead want to just say the pixel coordinates of the sprite
		//no index or rect means you use index 0, if you set the texture data to (textureWidth, textureHeight, 1, 1), you render the whole texture
		Sprite LoadSprite(const char* filePath, float4 textureData, const int index);
		Sprite LoadSprite(const char* filePath, float4 textureData); // uses index 0
		Sprite LoadSprite(unsigned char* buffer, int width, int height, float4 textureData);
	/*	Sprite LoadSprite(const char* filePath, float4 textureData, const float4& rect);*/

	};
}
