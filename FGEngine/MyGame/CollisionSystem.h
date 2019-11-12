#pragma once
#include "Vector2D.h"
#include "Entity.h"
#include <vector>
#include <xmmintrin.h>
#include <smmintrin.h>

class CollisionSystem
{
	CollisionSystem();

	class SpatialObject
	{
	public:
		bool dynamic;
		float x, y, w, h;
		FG::Entity* entity;
	};
	bool isColliding(const SpatialObject& a, const SpatialObject& b) const;
	static CollisionSystem* system;
public:
	static CollisionSystem* GetInstance()
	{
		if (system == nullptr)
		{
			system = new CollisionSystem();
		}
		return system;
	}

	void Setup(const int worldX, const int worldY, const float bucketSize);
	void RegisterCollider(const FG::Vector2D& pos, const FG::Vector2D& size, FG::Entity* entity, bool dynamic);
	void TestCollisions();
	void Clear();

	__m128 c;
	__m128 w;
	std::vector<std::vector<SpatialObject>> buckets;
};

