#pragma once
#pragma once
#include "GL/glew.h"
#include <string>
#include <vector>
#include "Vector2D.h"
#include <map>

class Shader
{
public:
	GLuint handle = 0;

	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		TESS,
		TESSCONTROL,
		PROGRAM
	};
	__declspec(dllexport)void DeleteProgram();
	__declspec(dllexport)void LoadShaders(const char* vsFilename, const char* fsFilename);
	__declspec(dllexport)void LoadShaders(const char* vsFilename, const char* fsFilename, const char* tesFileName, const char* tescFileName);

	__declspec(dllexport)void LoadShaders(const char* vsFilename, const char* fsFilename, const char* geoShaderName);

	__declspec(dllexport)void CheckCompileErrors(GLuint shader, ShaderType type);
	__declspec(dllexport)std::string FileToString(const std::string& filename);
	__declspec(dllexport)GLint GetUniformLocation(const GLchar* name);
	__declspec(dllexport)void SetUniform(const GLchar* name, const FG::Vector2D& v);
	__declspec(dllexport)void SetUniform(const GLchar* name, const GLfloat f);
	__declspec(dllexport)void SetUniform(const GLchar* name, const GLint i);
	__declspec(dllexport)void SetUniformSampler(const GLchar* name, const GLint slot);
	__declspec(dllexport)void SetUniformBlock(const GLchar* name, const GLint blockIndex);

	std::map<std::string, GLint> mUniformLocations;
	__declspec(dllexport)void Use();
};