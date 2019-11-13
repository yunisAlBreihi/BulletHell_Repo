#pragma once
#include <unordered_map>
#include "float4.h"
#include "GL/glew.h"
struct Texture2D
{
	unsigned int textureHandle;
};

class Texture2DHandler
{
	static bool dirty;

public:
	Texture2DHandler();

	static void LoadTexture(const char* fileName, Texture2D& texture);
	static void LoadTexture(char* pixels, int width, int height, Texture2D& texture);
	static void LoadTextureNoFlip(const char* fileName, Texture2D& texture);
	static void FreeTexture(Texture2D& texture);

	static uint16_t LoadTextureIntoArray(const char* filename, const float4& textureData);
	static void UnloadTextureArray();

	const static uint16_t nTextures = 16;
	static const int textureSize = 2048;

	static std::unordered_map<std::string, unsigned int> textures;
	static std::unordered_map<std::string, uint16_t> textureArrayMap;
	static float4 textureArrayData[nTextures];

	static uint16_t textureArrayPosition;
	static GLuint textureArray;

	static void SetDirty(const bool value)
	{
		dirty = value;
	}

	static bool GetDirty()
	{
		return dirty;
	}

	static float* getTextureArrayData(int& size)
	{
		size = (textureArrayPosition + 1) * 4;
		return (float*)textureArrayData;
	}
};
