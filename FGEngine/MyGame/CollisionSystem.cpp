#include "CollisionSystem.h"

CollisionSystem* CollisionSystem::system = new CollisionSystem();

CollisionSystem::CollisionSystem()
{

}

bool CollisionSystem::isColliding(const SpatialObject& a, const SpatialObject& b) const
{
	return (a.x + a.w >= b.x &&
		b.x + b.w >= a.x &&
		a.y + a.h >= b.y &&
		b.y + b.h >= a.y);
}

void CollisionSystem::Setup(const int worldX, const int worldY, const float bucketSize)
{
	float bucketSizeF = 1.0f / (float)bucketSize;
	c = _mm_set_ps(bucketSizeF, bucketSizeF, bucketSizeF, bucketSizeF);
	float width = worldX / bucketSize;
	w = _mm_set_ps(width, width, width, width);
	buckets.resize((double)width * (double)width);
}


void GetBucketIdSSE(const float* px, const float* py, const __m128& c, const __m128& w, float* indices)
{
	__m128* a = (__m128*)px;
	__m128* b = (__m128*)py;
	__m128 d = _mm_mul_ps(*a, c);
	__m128 f = _mm_mul_ps(*b, c);
	__m128 a2 = _mm_floor_ps(d);
	__m128 b2 = _mm_floor_ps(f);
	__m128 b3 = _mm_mul_ps(b2, w);
	__m128 res = _mm_add_ps(a2, b3);
	_mm_store_ps(indices, res);
}

void CollisionSystem::RegisterCollider(const FG::Vector2D& pos, const FG::Vector2D& size, FG::Entity* entity, bool dynamic)
{
	SpatialObject object;
	object.x = pos.x;
	object.y = pos.y;
	object.w = size.x;
	object.h = size.y;
	object.entity = entity;
	object.dynamic = dynamic;

	const static int indexCount = 4;
	const float px[4] = { pos.x, pos.x + size.x, pos.x, pos.x + size.x };
	const float py[4] = { pos.y, pos.y, pos.y + size.y, pos.y + size.y };
	float indices[4];

	GetBucketIdSSE(px, py, c, w, indices);
	bool duplicate = false;
	for (int i = 0; i < indexCount; i++)
	{
		if (!(indices[i] < buckets.size()) || indices[i] < 0)
		{
			//TODO: deal with indices outside of the bounds
			continue;
		}
		for (int j = 0; j < i; j++)
		{
			if (indices[i] == indices[j])
			{
				duplicate = true;
				break;
			}
		}
		if (!duplicate)
		{
			buckets[indices[i]].emplace_back(object);
		}
		duplicate = false;
	}
}


void CollisionSystem::TestCollisions()
{
	for (int bucket = 0; bucket < buckets.size(); bucket++)
	{
		std::vector<SpatialObject> objectsToTest = buckets[bucket];
		for (int i = 0; i < ((int)objectsToTest.size()) - 1; i++)
		{
			SpatialObject a = objectsToTest[i];
			for (int j = i + 1; j < objectsToTest.size(); j++)
			{
				SpatialObject b = objectsToTest[j];
				if (a.entity == b.entity)
				{
					continue;
				}
				if (a.dynamic || b.dynamic)
				{
					if (isColliding(a, b))
					{
						a.entity->OnCollision(b.entity);
						b.entity->OnCollision(a.entity);
					}
				}
			}
		}
	}
	Clear();
}

void CollisionSystem::Clear()
{
	for (int i = 0; i < buckets.size(); i++)
	{
		buckets[i].clear();
	}
}
