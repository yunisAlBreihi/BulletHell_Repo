#include "Renderer.h"
#include "float4.h"

#include "glew.h"
#include "wglew.h"
#include <vector>
#include "Shader.h"
#include "Camera.h"
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

struct TextVertex
{
	TextVertex(float x, float y, float sx, float sy, float id): x(x), y(y), sx(sx), sy(sy), i(id) { }
	float x = 0, y = 0, sx = 0, sy = 0, i = 0;

};

struct QuadVertex
{
	QuadVertex(float x, float y, float sx, float sy, Color borderColor, Color fillCol) : x(x), y(y), sx(sx), sy(sy) { QuadVertex(); }
	float x, y, sx, sy;
	static VAO vao;

	QuadVertex()
	{
		if (vao.vaoStructure.size() == 0)
		{
			vao.AddInfo(VAOInfo(0, 4, NULL));
		}
	}
};

VAO QuadVertex::vao = VAO();

struct SpriteVertex
{
	SpriteVertex(float x, float y, float sx, float sy, float r, float i) : x(x), y(y), sx(sx), sy(sy), r(r), i(i) {
		SpriteVertex();
	}

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

#pragma warning(pop)
#pragma warning(pop)

class RenderImpl
{
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

	RenderImpl();
	void ResetBatches() { batches.clear(); }
	void Swap()
	{
		SDL_GL_SwapWindow(window);
	}
public:
	~RenderImpl();
	RenderImpl(SDL_Window* window);

	void AddBatch(Batch batch) { batches.emplace_back(batch); }

	void UseFont(const Font& font)
	{

	}

	void RenderQuad(const FG::Vector2D& position, const FG::Vector2D& size, const Color& color, const Color& fillColor)
	{
		QuadVertex vertex;
		vertex.x = position.x;
		vertex.y = position.y;
		vertex.sx = size.x;
		vertex.sy = size.y;
		quadVertices.emplace_back(vertex);
	}

	void RenderText(const FG::Vector2D& position, const int textSize, const std::string& text)
	{
		//for each character get character information
		for (int i = 0; i < text.size(); i++)
		{
			int index = 0;
			float characterYPos = 0;
			float characterXPos = 0;
			textVertices.push_back(TextVertex(position.x + i + characterYPos, position.y + characterYPos, textSize, textSize, index));
		}
	}

	void Render(const FG::Vector2D& position, const FG::Sprite& sprite)
	{
		SpriteVertex vertex;
		vertex.i = sprite.spriteIndex << 16 | sprite.textureIndex & 0xffff;
		vertex.x = position.x;
		vertex.y = position.y;
		vertex.r = 0;
		vertex.sx = sprite.GetScale().x;
		vertex.sy = sprite.GetScale().y;
		vertices.emplace_back(vertex);
	}

	void Present(const Camera* const camera)
	{
		if (vertices.size() > 0)
		{
			if (!vbo.Initialized())
			{
				vbo.Init(vertices.data(), (GLuint)vertices.size(), (GLuint)sizeof(SpriteVertex), SpriteVertex::vao);
				batch.shaderHandle = shader.handle;
				batch.textureArray = 0;
				batch.vao = vbo.Vao();
				batch.vbo = vbo.Vbo();
			}
			else
			{
				vbo.BufferData(vertices.data(), (GLuint)vertices.size());
			}

			batch.count = vertices.size();
			AddBatch(batch);
		}

		if (quadVertices.size() > 0)
		{
			if (!quadVBO.Initialized())
			{
				quadVBO.Init(quadVertices.data(), (GLuint)quadVertices.size(), (GLuint)sizeof(QuadVertex), QuadVertex::vao);
				quadBatch.vao = quadVBO.Vao();
				quadBatch.vbo = quadVBO.Vbo();
				quadBatch.shaderHandle = quadShader.handle;
			}
			else
			{
				quadVBO.BufferData(quadVertices.data(), (GLuint)quadVertices.size());
			}
			quadBatch.count = quadVertices.size();
			AddBatch(quadBatch);
		}

		for (auto batch : batches)
		{
			glUseProgram(batch.shaderHandle);
			unsigned int loc = glGetUniformLocation(batch.shaderHandle, "vp");
			glUniformMatrix4fv(loc, 1, GL_FALSE, camera->GetVP().c);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D_ARRAY, 1);
			loc = glGetUniformLocation(batch.shaderHandle, "textureArray");
			glUniform1i(loc, 0);

			loc = glGetUniformLocation(batch.shaderHandle, "tilemapDataArray");
			if (loc != 0)
			{
				int count = 0;
				float* data = Texture2DHandler::getTextureArrayData(count);
				glUniform4fv(loc, count, data);
			}
			glBindVertexArray(batch.vao);
			glDrawArrays(GL_POINTS, 0, batch.count);
		}
		Swap();
		vertices.clear();
		batches.clear();
		quadVertices.clear();
	}

private:
	std::vector<SpriteVertex> vertices;
	std::vector<TextVertex> textVertices;
	std::vector<QuadVertex> quadVertices;
	std::vector<Batch> batches;
	SDL_Window* window;
	RenderImpl::Batch batch;
	Batch quadBatch;
	VBO vbo;
	VBO quadVBO;

	Shader quadShader;
	Shader shader;
};

RenderImpl::~RenderImpl()
{

}

RenderImpl::RenderImpl(SDL_Window* window)
{

	this->window = window;
	SDL_GLContext gContext = SDL_GL_CreateContext(window);
	if (gContext == NULL)
	{
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
	}

	//	wglSwapIntervalEXT(0);
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
	}

	quadVBO = VBO();
	vbo = VBO();
	SDL_GL_SetSwapInterval(0);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE_ARB);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	shader.LoadShaders("..//Shader//vertexShader.vert", "..//Shader//fragmentShader.frag", "..//Shader//geometryShader.geo");
	quadShader.LoadShaders("..//Shader//borderRectGeometry.vert", "..//Shader//borders.frag", "..//Shader//borderRectGeometry.geo");
}

Renderer::Renderer(SDL_Window* window)
{
	renderImpl = std::make_unique<RenderImpl>(window);
}

Renderer::~Renderer()
{
}

void Renderer::Clear(const float4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Render(const FG::Vector2D& position, const FG::Sprite& sprite)
{
	renderImpl->Render(position, sprite);
}

void Renderer::UseFont(const Font& font)
{
	renderImpl->UseFont(font);
}

void Renderer::RenderQuad(const FG::Vector2D& position, const FG::Vector2D& size, const Color& borderColor, const Color& fillColor)
{
	renderImpl->RenderQuad(position, size, borderColor, fillColor);
}

void Renderer::RenderText(const FG::Vector2D& position, const int textSize, const std::string& text)
{
	renderImpl->RenderText(position, textSize, text);
}

void Renderer::Present(const Camera *const camera)
{
	renderImpl->Present(camera);
}


