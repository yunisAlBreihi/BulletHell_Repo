#pragma once
#include "float3.h"
#include "VAO.h"
struct LineVertex
{
	LineVertex(const float& ax, const float& ay, const float& bx, const float& by, const float3& color, const float& size) : ax(ax), ay(ay), bx(bx), by(by), color(color), size(size)
	{
		if (vao.vaoStructure.size() == 0)
		{
			vao.AddInfo(VAOInfo(0, 4, NULL));
			vao.AddInfo(VAOInfo(1, 4, 4 * sizeof(float)));
		}
	}



	float ax, ay, bx, by;
	float3 color;
	float size;
	static VAO vao;
};

