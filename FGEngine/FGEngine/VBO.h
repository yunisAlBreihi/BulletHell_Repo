#pragma once
#include "VAO.h"

class VBO
{
	uint32_t vbo;
	uint32_t vao;
	uint32_t structSize;

	void Destroy();

public:
	bool Initialized() const
	{
		return vbo != 0;
	}

	uint32_t Vbo() const
	{
		return vbo;
	}

	uint32_t Vao() const
	{
		return vao;
	}

	VBO() = default;

	~VBO()
	{
		Destroy();
	}

	void Init(void* arr, const uint32_t& size, const uint32_t& structSize, VAO vaoStructure);

	void BufferData(void* arr, const uint32_t& size);

};



inline void VBO::Init(void* arr, const uint32_t& size, const uint32_t& structSize, VAO vaoStructure)
{
	if (!(vbo == vao == 0))
	{
		Destroy();
	}
	this->structSize = structSize;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * structSize, (void*)arr, GL_STREAM_DRAW);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	for (int i = 0; i < vaoStructure.vaoStructure.size(); i++)
	{
		auto vaoStruct = vaoStructure.vaoStructure[i];
		glVertexAttribPointer(vaoStruct.pos, vaoStruct.count, GL_FLOAT, GL_FALSE, structSize, (GLvoid*)vaoStruct.offset);
		glEnableVertexAttribArray(vaoStruct.pos);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

inline void VBO::BufferData(void* arr, const uint32_t& size)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * structSize, arr, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

inline void VAO::AddInfo(const VAOInfo& info)
{
	vaoStructure.emplace_back(info);
}

inline void VBO::Destroy()
{
	if (vbo != 0)
	{
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
}
