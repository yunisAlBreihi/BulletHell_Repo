#include "Renderer.h"
#include "float4.h"
//#include "GL/wglew.h"
//#include "GL/glew.h"
#include <vector>

#pragma warning(push)
#pragma warning(disable : 4312)
#pragma warning(push)
#pragma warning(disable : 26451)



struct VAOInfo
{
	VAOInfo(uint32_t pos, uint32_t count, uint32_t offset)
		: pos(pos), count(count), offset(offset) { }
	uint32_t pos, count, offset;
};

class VAO
{
public:
	void AddInfo(const VAOInfo& info);
	std::vector<VAOInfo> vaoStructure;
};

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
struct SpriteVertex
{
	SpriteVertex(float x, float y, float sx, float sy, float r, float i) : x(x), y(y), sx(sx), sy(sy), r(r), i(i) {}

	//8 values
	//x, y, half scales, theta
	//color, sorting layer, index, texture id

	//3 values
	//x, y, indices

	float x = 0, y = 0, sx = 0, sy = 0, r = 0, i = 0;

	static VAO vao;
	SpriteVertex()
	{
		if (vao.vaoStructure.size() == 0)
		{
			vao.AddInfo(VAOInfo(0, 2, NULL));
			vao.AddInfo(VAOInfo(1, 4, 2 * sizeof(float)));
		}
	}
};
VAO SpriteVertex::vao = VAO();

inline void VBO::Init(void* arr, const uint32_t& size, const uint32_t& structSize, VAO vaoStructure)
{
	if (!(vbo == vao == 0))
	{
		Destroy();
	}
	this->structSize = structSize;
	/*glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * structSize, (void*)arr, GL_STREAM_DRAW);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);*/
	for (int i = 0; i < vaoStructure.vaoStructure.size(); i++)
	{
		auto vaoStruct = vaoStructure.vaoStructure[i];
		//glVertexAttribPointer(vaoStruct.pos, vaoStruct.count, GL_FLOAT, GL_FALSE, structSize, (GLvoid*)vaoStruct.offset);
		//glEnableVertexAttribArray(vaoStruct.pos);
	}
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
}

inline void VBO::BufferData(void* arr, const uint32_t& size)
{
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, size * structSize, arr, GL_STREAM_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

inline void VAO::AddInfo(const VAOInfo& info)
{
	vaoStructure.emplace_back(info);
}

inline void VBO::Destroy()
{
	/*glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);*/
}

#pragma warning(pop)
#pragma warning(pop)

class RenderImpl
{
	RenderImpl();
public:
	RenderImpl(HDC window)
	{
		hdc = window;
		//wglSwapIntervalEXT(0);

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	/*glEnable(GL_MULTISAMPLE_ARB);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);*/
	}
	class Batch
	{
	public:
		Batch() {}
		Batch(uint32_t vao, uint32_t vbo, uint32_t count, uint32_t shaderHandle) {}
		uint32_t vao = 0;
		uint32_t vbo = 0;
		uint32_t count = 0;
		uint32_t shaderHandle = 0;
		uint32_t textureArray = 0;
	};
	std::vector<Batch> batches;
	HDC hdc;

	void AddBatch(Batch batch) { batches.emplace_back(batch); }
	void ResetBatches() { batches.clear(); }
	std::vector<SpriteVertex> dynamicVertices;
};

Renderer::Renderer(const HDC& window)
{
	renderImpl = std::make_unique<RenderImpl>(window);
}

void Renderer::Clear(const float4& color)
{
	/*glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);*/
}

void Renderer::Present(const FG::Camera *const camera)
{
	for (auto batch : renderImpl->batches)
	{
		//glUseProgram(batch.shaderHandle);
		//unsigned int loc = glGetUniformLocation(batch.shaderHandle, "vp");
		////glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(camera->GetView() * camera->GetProjection()));

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D_ARRAY, 1);
		//loc = glGetUniformLocation(batch.shaderHandle, "textureArray");
		//glUniform1i(loc, 0);

		//loc = glGetUniformLocation(batch.shaderHandle, "tilemapDataArray");
		//if (loc != 0)
		//{
		//	int count = 0;
		//	//float* data = handler.getTextureArrayData(count);
		//	//glUniform4fv(loc, count, data);
		//}


		//glBindVertexArray(batch.vao);
		//glDrawArrays(GL_POINTS, 0, batch.count);
	}
	//SDL_SwapLayerBuffer
	//wglSwapLayerBuffers(hdc, WGL_SWAP_MAIN_PLANE);
}
