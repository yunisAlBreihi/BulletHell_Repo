#pragma once
#include "Vector2D.h"
#include "Entity.h"
#include <memory>
#include <stdint.h>
#include "EntityType.h"
#include <vector>
#include <xmmintrin.h>
#include <smmintrin.h>
#include "tbb/tbb.h"

class SpatialObject
{
public:
	bool dynamic;
	float x, y, w, h;
	FG::Entity* entity;
	uint64_t mask;
	uint64_t collidesWith;
};
class CollisionSystem
{
	bool isColliding(const SpatialObject& a, const SpatialObject& b) const;
	void GetBucketIdSSE(const float* px, const float* py, const __m128& c, const __m128& w, float* indices);


	__m128 c;
	__m128 w;
	std::vector<std::vector<SpatialObject>> buckets;
	tbb::concurrent_vector<std::pair<FG::Entity*, FG::Entity*>> collisionPairs;

	CollisionSystem();
	static CollisionSystem* system;
public:
	~CollisionSystem() = default;

	static CollisionSystem* GetInstance()
	{
		if (system == nullptr)
		{
			system = new CollisionSystem();
		}
		return system;
	}

	void Setup(const int worldX, const int worldY, const float bucketSize);
	void RegisterCollider(const FG::Vector2D& pos, const FG::Vector2D& size, FG::Entity* entity, uint64_t layer, bool dynamic);
	void TestCollisions();
	void Clear();

};

