#pragma once
#include "VAO.h"
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

	void Hey();

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
