#pragma once
#include "ft2build.h"
#include FT_FREETYPE_H
#include "float4.h"
#include <iostream>
#include <vector>
class FontLoader
{
public:
	FT_Library  library;

	void Init()
	{
		auto error = FT_Init_FreeType(&library);
		if (error)
		{
			//error log - lib init is borka borka
		}

	}

	unsigned char* LoadFont(const char* fileName, int& width, int& height, std::vector<unsigned char>& bufferData, float4& textureData)
	{
		FT_Face face;
		auto error = FT_New_Face(library, fileName, 0, &face);

		if (error == FT_Err_Unknown_File_Format)
		{
			//error log - not correct fileformat
		}

		error = FT_Set_Char_Size(
			face,    /* handle to face object           */
			0,       /* char_width in 1/64th of points  */
			100 * 64,   /* char_height in 1/64th of points */
			1000,     /* horizontal device resolution    */
			1000);   /* vertical device resolution      */

		error = FT_Set_Pixel_Sizes(
			face,   /* handle to face object */
			0,      /* pixel_width           */
			150);   /* pixel_height          */

		auto glyph_index = FT_Get_Char_Index(face, 'A');
		error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		error = FT_Render_Glyph(face->glyph,   /* glyph slot  */
			FT_Render_Mode::FT_RENDER_MODE_NORMAL); /* render mode */
		auto bitmap = face->glyph->bitmap;
		bufferData.insert(bufferData.end(), face->glyph->bitmap.buffer, face->glyph->bitmap.buffer + face->glyph->bitmap.rows * face->glyph->bitmap.width);
		width += face->glyph->metrics.width;
		height += face->glyph->metrics.height;

		glyph_index = FT_Get_Char_Index(face, 'E');
		error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		error = FT_Render_Glyph(face->glyph,   /* glyph slot  */
			FT_Render_Mode::FT_RENDER_MODE_NORMAL); /* render mode */
		bitmap = face->glyph->bitmap;
		width += face->glyph->metrics.width;
		height += face->glyph->metrics.height;
		bufferData.insert(bufferData.end(), face->glyph->bitmap.buffer, face->glyph->bitmap.buffer + face->glyph->bitmap.rows * face->glyph->bitmap.width);


		textureData.x = 1.0f;
		textureData.y = 1.0f;
		textureData.z = 1;
		textureData.w = 1;

		return bufferData.data();
	}

};

