#pragma once
#include "VAO.h"

struct TextVertex
{
	TextVertex(float x, float y, float fontSize, float font) : x(x), y(y), fontSize(fontSize), font(font) { TextVertex(); }
	float x = 0;
	float y = 0;
	float fontSize = 0;
	float font = 0;

	static VAO vao;
private:
	TextVertex()
	{
		if (vao.vaoStructure.size() == 0)
		{
			vao.AddInfo(VAOInfo(0, 4, NULL));
		}
	}
};