#include "texture2D.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glew.h"


bool Texture2DHandler::dirty = false;
std::unordered_map<std::string, unsigned int> Texture2DHandler::textures = std::unordered_map<std::string, unsigned int>();
std::unordered_map<std::string, uint16_t> Texture2DHandler::textureArrayMap = std::unordered_map<std::string, uint16_t>();
float4 Texture2DHandler::textureArrayData[nTextures] = { 0 };

uint16_t Texture2DHandler::textureArrayPosition = 0;
GLuint Texture2DHandler::textureArray = 0;

Texture2DHandler::Texture2DHandler()
{
	textureArray = 0;

	for (int i = 0; i < nTextures; i++)
	{
		textureArrayData[i] = float4();
	}
}

void Texture2DHandler::LoadTexture(const char* fileName, Texture2D& texture)
{
	int width, height, comp;
	unsigned char* imageData;

	imageData = stbi_load(fileName, &width, &height, &comp, STBI_rgb_alpha);

	if (imageData == nullptr)
	{
		std::cout << "Could not load texture file" << std::endl;
		return;
	}
	int widthInBytes = width * 4;
	unsigned char* top = NULL;
	unsigned char* bottom = NULL;
	unsigned char temp = 0;
	int halfHeight = height / 2;
	for (int row = 0; row < halfHeight; row++)
	{
		top = imageData + (size_t)row * widthInBytes;
		bottom = imageData + ((size_t)height - row - 1) * widthInBytes;
		for (int col = 0; col < widthInBytes; col++)
		{
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}

	glGenTextures(1, &texture.textureHandle);
	glBindTexture(GL_TEXTURE_2D, texture.textureHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	//glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2DHandler::LoadTexture(char* pixels, int width, int height, Texture2D& texture)
{
	glGenTextures(1, &texture.textureHandle);
	glBindTexture(GL_TEXTURE_2D, texture.textureHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels);

	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2DHandler::LoadTextureNoFlip(const char* fileName, Texture2D& texture)
{
	int width, height, comp;
	unsigned char* imageData;

	imageData = stbi_load(fileName, &width, &height, &comp, STBI_rgb_alpha);

	if (imageData == nullptr)
	{
		std::cout << "Could not load texture file" << std::endl;
	}

	glGenTextures(1, &texture.textureHandle);
	glBindTexture(GL_TEXTURE_2D, texture.textureHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2DHandler::FreeTexture(Texture2D& texture)
{
	glDeleteTextures(1, &texture.textureHandle);
}

uint16_t Texture2DHandler::LoadTextureIntoArray(const char* filename, const int& rows, const int& columns, float& width, float& height, float& aspectRatio)
{
	if (textureArrayMap.find(filename) != textureArrayMap.end())
	{
		

		return textureArrayMap.at(filename);
	}
	if (textureArrayPosition >= nTextures)
	{
		std::cout << "max number of textures in array reached!" << std::endl;
		return -1;
	}

	int textureWidth, textureHeight, comp;
	unsigned char* imageData;

	imageData = stbi_load(filename, &textureWidth, &textureHeight, &comp, STBI_rgb_alpha);

	if (imageData == nullptr)
	{
		std::cout << "Could not load texture file" << std::endl;
		return -1;
	}/*
	int widthInBytes = width * 4;
	unsigned char* top = NULL;
	unsigned char* bottom = NULL;
	unsigned char temp = 0;
	int halfHeight = height / 2;
	for (int row = 0; row < halfHeight; row++)
	{
		top = imageData + (size_t)row * widthInBytes;
		bottom = imageData + ((size_t)height - row - 1) * widthInBytes;
		for (int col = 0; col < widthInBytes; col++)
		{
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}*/

	if (textureArray == 0)
	{
		glGenTextures(1, &textureArray);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
		glTexStorage3D(GL_TEXTURE_2D_ARRAY,
			1,                    //5 mipmaps
			GL_RGBA8,               //Internal format
			textureSize, textureSize,           //width,height
			nTextures                   //Number of layers
		);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
		0,                      //Mipmap number
		0, 0, textureArrayPosition, //xoffset, yoffset, zoffset
		textureWidth, textureHeight, 1,          //width, height, depth
		GL_RGBA,                 //format
		GL_UNSIGNED_BYTE,       //type
		imageData); //pointer to data
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	stbi_image_free(imageData);

	textureArrayMap.emplace(filename, textureArrayPosition);
	width = (float)textureWidth / (float)textureSize;
	height = (float)textureHeight / (float)textureSize;
	textureArrayData[textureArrayPosition] = float4((1.0f / (float)rows) * width, (1.0f / (float)columns) * height, rows ,columns);
	textureArrayPosition++;
	dirty = true;

	if (textureWidth != textureHeight)
	{
		if (textureWidth > textureHeight)
		{
			aspectRatio = (float)textureWidth / (float)textureHeight;
		}
		else
		{
			aspectRatio = (float)textureWidth / (float)textureHeight;
		}
	
	}
	else
	{
		aspectRatio = 1.0f;
	}


	return textureArrayPosition - 1;
}

uint16_t Texture2DHandler::LoadTextureIntoArray(unsigned char* buffer, float width, float height, const float4& textureData)
{
	if (textureArray == 0)
	{
		glGenTextures(1, &textureArray);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
		glTexStorage3D(GL_TEXTURE_2D_ARRAY,
			1,                    //5 mipmaps
			GL_RGBA8,               //Internal format
			textureSize, textureSize,           //width,height
			nTextures                   //Number of layers
		);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
		0,                      //Mipmap number
		0, textureSize - height, textureArrayPosition, //xoffset, yoffset, zoffset
		width, height, 1,          //width, height, depth
		GL_RGBA,                 //format
		GL_UNSIGNED_BYTE,       //type
		buffer); //pointer to data
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	textureArrayData[textureArrayPosition] = textureData;
	textureArrayPosition++;
	dirty = true;
	return textureArrayPosition - 1;
}

void Texture2DHandler::UnloadTextureArray()
{
	glDeleteTextures(nTextures, &textureArray);
}
