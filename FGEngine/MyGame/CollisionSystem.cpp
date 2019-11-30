#include "CollisionSystem.h"

uint32_t EntityTypeCounter::counter = 0;
using Range = tbb::blocked_range<int>;
using namespace tbb;
struct BoxTest
{
	inline bool isColliding(const SpatialObject& a, const SpatialObject& b) const
	{
		return (a.x + a.w >= b.x &&
			b.x + b.w >= a.x &&
			a.y + a.h >= b.y &&
			b.y + b.h >= a.y);
	}

	void operator()(const SpatialObject& objectToTest, const std::vector<SpatialObject>& objectsToTest, tbb::concurrent_vector<std::pair<FG::Entity*, FG::Entity*>>& collisionPairs, const int index)
	{
		for (int i = index + 1; i < objectsToTest.size(); i++)
		{
			SpatialObject b = objectsToTest[i];

			int aCollidesWithB = (objectToTest.collidesWith >> b.mask) & 1U;
			int bCollidesWithA = (b.collidesWith >> objectToTest.mask) & 1U;
			if (aCollidesWithB && bCollidesWithA)
			{
				if (objectToTest.dynamic || b.dynamic)
				{
					if (isColliding(objectToTest, b))
					{
						collisionPairs.emplace_back(std::make_pair(objectToTest.entity, b.entity));
					}
				}
			}
		}
	}
};


CollisionSystem* CollisionSystem::system = new CollisionSystem();

bool CollisionSystem::isColliding(const SpatialObject& a, const SpatialObject& b) const
{
	return (a.x + a.w >= b.x &&
		b.x + b.w >= a.x &&
		a.y + a.h >= b.y &&
		b.y + b.h >= a.y);
}

void CollisionSystem::GetBucketIdSSE(const float* px, const float* py, const __m128& c, const __m128& w, float* indices)
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

CollisionSystem::CollisionSystem():  c(_mm_set_ps(0, 0, 0, 0)), w(_mm_set_ps(0, 0, 0, 0))
{
	collisionPairs.reserve(100);
}

void CollisionSystem::Setup(const int worldX, const int worldY, const float bucketSize)
{
	float bucketSizeF = 1.0f / (float)bucketSize;
	c = _mm_set_ps(bucketSizeF, bucketSizeF, bucketSizeF, bucketSizeF);
	float width = worldX / bucketSize;
	w = _mm_set_ps(width, width, width, width);
	buckets.resize((double)width * (double)width);
}

void CollisionSystem::RegisterCollider(const FG::Vector2D& pos, const FG::Vector2D& size, FG::Entity* entity, uint64_t layer, bool dynamic)
{
	uint64_t collidesWith = entity->collidesWith;
	SpatialObject object;
	object.x = pos.x;
	object.y = pos.y;
	object.w = size.x;
	object.h = size.y;
	object.entity = entity;
	object.dynamic = dynamic;
	object.mask = layer;
	object.collidesWith = collidesWith;

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
			//skip indices which are out of bounds
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
	BoxTest boxTest;
	parallel_for(Range(0, buckets.size()), [&boxTest, this](const Range& r)
		{
			for (int i = r.begin(); i < r.end(); i++)
			{
				parallel_for(Range(0, buckets[i].size()), [&i, &boxTest, this](const Range& r2)
					{
						for (int j = r2.begin(); j < r2.end(); j++)
						{
							boxTest(buckets[i][j], buckets[i], collisionPairs, j);
						}
					});
			}
		});

	auto size = collisionPairs.size();
	for (int i = 0; i < size; i++)
	{
		auto a = collisionPairs[i].first;
		auto b = collisionPairs[i].second;

		a->OnCollision(b);
		b->OnCollision(a);

	}
	collisionPairs.clear();
	Clear();
}

void CollisionSystem::Clear()
{
	for (int i = 0; i < buckets.size(); i++)
	{
		buckets[i].clear();
	}
}