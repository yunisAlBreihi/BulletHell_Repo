#pragma once
#include <stdint.h>

class Batch
{
public:
	Batch() {}
	Batch(uint32_t vao, uint32_t vbo, uint32_t count, uint32_t shaderHandle) {}
	~Batch() {}
	uint32_t vao = 0;
	uint32_t vbo = 0;
	uint32_t count = 0;
	uint32_t shaderHandle = 0;
	uint32_t textureArray = 0;
};