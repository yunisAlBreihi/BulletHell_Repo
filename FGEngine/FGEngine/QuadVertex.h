#pragma once
#include "VAO.h"
#include "Color.h"

struct QuadVertex
{
	QuadVertex(float x, float y, float sx, float sy, Color borderColor, Color fillCol) : x(x), y(y), sx(sx), sy(sy), fillColor(fillCol), borderColor(borderColor) { QuadVertex(); }
	float x, y, sx, sy;
	Color fillColor, borderColor;
	static VAO vao;
	
private:
	QuadVertex()
	{
		if (vao.vaoStructure.size() == 0)
		{
			vao.AddInfo(VAOInfo(0, 4, NULL));
			vao.AddInfo(VAOInfo(1, 4, 4 * sizeof(float)));
			vao.AddInfo(VAOInfo(2, 4, 8 * sizeof(float)));
		}
	}
};


