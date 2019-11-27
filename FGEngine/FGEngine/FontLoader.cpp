#include "FontLoader.h"
#include "Window.h"
#include <vector>
#include <iostream>
void FontLoader::Init()
{
	auto error = FT_Init_FreeType(&library);
	if (error)
	{
		//error log - lib init is borka borka
	}
}

GLuint FontLoader::LoadFont(const char* fileName, GLuint fontSize)
{
	FT_Face face;
	auto error = FT_New_Face(library, fileName, 0, &face);

	if (error == FT_Err_Unknown_File_Format)
	{
		//error log - not correct fileformat
	}
	GLuint textureArrayHandle = 0;

	int glyphSize = 128;
	nGlyphs = 255;

	glGenTextures(1, &textureArrayHandle);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayHandle);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY,
		1,                    //5 mipmaps
		GL_RGBA8,               //Internal format
		glyphSize, glyphSize,           //width,height
		nGlyphs                   //Number of layers
	);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//for each glyph

	error = FT_Set_Char_Size(
		face,    /* handle to face object           */
		0,       /* char_width in 1/64th of points  */
		fontSize * 64,   /* char_height in 1/64th of points */
		1920,     /* horizontal device resolution    */
		1080);   /* vertical device resolution      */

	error = FT_Set_Pixel_Sizes(
		face,   /* handle to face object */
		0,      /* pixel_width           */
		64);   /* pixel_height          */


	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayHandle);

	std::vector<unsigned char> pixels;
	for (int i = 0; i < nGlyphs; i++)
	{
		auto glyph_index = FT_Get_Char_Index(face, (unsigned long)i);
		error = FT_Load_Glyph(face, glyph_index, FT_LOAD_COLOR);
		if (glyph_index != 0)
		{
			error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
			auto bitmap = face->glyph->bitmap;
			bitmap.buffer;
			pixels.resize(bitmap.width * bitmap.rows * 4);
			for (int i = 0; i < bitmap.width * bitmap.rows; i++)
			{
				pixels[i * 4] = bitmap.buffer[i];
				pixels[(i * 4) + 3] = 255;
			}
			if (pixels.size() > 0)
			{
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
					0,                      //Mipmap number
					0, 0, i, //xoffset, yoffset, zoffset
					bitmap.width, bitmap.rows, 1,          //width, height, depth
					GL_RGBA,                 //format
					GL_UNSIGNED_BYTE,       //type
					pixels.data()); //pointer to data
			}
		}
	}

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	return textureArrayHandle;
}

void FontLoader::UnloadFont(GLuint handle)
{
	glDeleteTextures(255, &handle);
}
