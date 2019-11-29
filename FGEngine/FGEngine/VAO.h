#pragma once
#include <vector>
#include <stdint.h>
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