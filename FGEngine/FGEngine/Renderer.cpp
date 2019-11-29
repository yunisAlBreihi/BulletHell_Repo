#include "Renderer.h"

Renderer::Renderer(SDL_Window* window)
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

	lineVBO = VBO();
	quadVBO = VBO();
	textVBO = VBO();
	vbo = VBO();
	SDL_GL_SetSwapInterval(0);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE_ARB);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	shader.LoadShaders("..//Shader//sprite.vert", "..//Shader//sprite.frag", "..//Shader//sprite.geo");
	quadShader.LoadShaders("..//Shader//rect.vert", "..//Shader//rect.frag", "..//Shader//rect.geo");
	lineShader.LoadShaders("..//Shader//line.vert", "..//Shader//line.frag", "..//Shader//line.geo");
	textShader.LoadShaders("..//Shader//text.vert", "..//Shader//text.frag", "..//Shader//text.geo");
}

void Renderer::RenderText(const FG::Vector2D& position, const float size, const std::string& text)
{
	for (int i = 0; i < text.size(); i++)
	{
		//TODO: Get pixelsize from camera
		auto pixelSize = size / 20.0f;
		TextVertex vertex(position.x + i * pixelSize, position.y, pixelSize, text[i]);

		textVertices.push_back(vertex);
	}
}
void Renderer::Render(const FG::Vector2D& position, const FG::Sprite& sprite)
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
void Renderer::RenderLine(const FG::Vector2D& a, const FG::Vector2D& b, const float3& color, const float& size)
{
	LineVertex vertex(a.x, a.y, b.x, b.y, color, size);
	lineVertices.push_back(vertex);
}

void Renderer::ResetBatches()
{
	 batches.clear(); 
}

void Renderer::Swap()
{
	SDL_GL_SwapWindow(window);
}

Renderer::~Renderer()
{
	SDL_DestroyWindow(window);
}

void Renderer::Clear(const float4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::RenderQuad(const FG::Vector2D& position, const FG::Vector2D& size, const Color& fillColor, const Color& borderColor)
{
	QuadVertex vertex(position.x, position.y, size.x, size.y, borderColor, fillColor);
	quadVertices.emplace_back(vertex);
}

void Renderer::Present(const Camera* const camera)
{
	if (vertices.size() > 0)
	{
		if (!vbo.Initialized())
		{
			vbo.Init(vertices.data(), (GLuint)vertices.size(), (GLuint)sizeof(SpriteVertex), SpriteVertex::vao);
			spriteBatch.shaderHandle = shader.handle;
			spriteBatch.textureArray = 0;
			spriteBatch.vao = vbo.Vao();
			spriteBatch.vbo = vbo.Vbo();
		}
		else
		{
			vbo.BufferData(vertices.data(), (GLuint)vertices.size());
		}

		spriteBatch.count = vertices.size();
		AddBatch(spriteBatch);
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

	if (lineVertices.size() > 0)
	{
		if (!lineVBO.Initialized())
		{
			lineVBO.Init(lineVertices.data(), (GLuint)lineVertices.size(), (GLuint)sizeof(LineVertex), LineVertex::vao);
			lineBatch.vao = lineVBO.Vao();
			lineBatch.vbo = lineVBO.Vbo();
			lineBatch.shaderHandle = lineShader.handle;
		}
		else
		{
			lineVBO.BufferData(lineVertices.data(), (GLuint)lineVertices.size());
		}
		lineBatch.count = lineVertices.size();
		AddBatch(lineBatch);
	}

	if (textVertices.size() > 0)
	{
		if (!textVBO.Initialized())
		{
			textVBO.Init(textVertices.data(), (GLuint)textVertices.size(), (GLuint)sizeof(TextVertex), TextVertex::vao);
			textBatch.vao = textVBO.Vao();
			textBatch.vbo = textVBO.Vbo();
			textBatch.shaderHandle = textShader.handle;
		}
		else
		{
			textVBO.BufferData(textVertices.data(), (GLuint)textVertices.size());
		}
		textBatch.count = textVertices.size();
		AddBatch(textBatch);
	}

	for (auto batch : batches)
	{
		glUseProgram(batch.shaderHandle);
		auto loc = glGetUniformLocation(batch.shaderHandle, "vp");
		glUniformMatrix4fv(loc, 1, GL_FALSE, camera->GetVP().c);


		loc = glGetUniformLocation(batch.shaderHandle, "texArray");
		if (loc != -1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D_ARRAY, 1);
			glUniform1i(loc, 0);
		}

		loc = glGetUniformLocation(batch.shaderHandle, "textureArray");
		if (loc != -1)
		{
			glActiveTexture(GL_TEXTURE0 + 1);
			glBindTexture(GL_TEXTURE_2D_ARRAY, 2);
			glUniform1i(loc, 1);
		}

		loc = glGetUniformLocation(batch.shaderHandle, "tilemapDataArray");
		if (loc != -1)
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
	lineVertices.clear();
	textVertices.clear();
	quadVertices.clear();
}