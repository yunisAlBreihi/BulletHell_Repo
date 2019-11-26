#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdint.h>
#include "glew.h"


class FontLoader
{
public:
	FT_Library  library;

	void Init();

	GLuint LoadFont(const char* fileName, GLuint fontSize);

	void UnloadFont(GLuint handle);

private:
	uint32_t nGlyphs;
};

