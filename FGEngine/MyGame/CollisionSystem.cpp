#include "CollisionSystem.h"
#include <vector>
#include <xmmintrin.h>
#include <smmintrin.h>

uint32_t CollisionMasker::counter = 0;

#pragma region IMPL
class CollisionSystemImpl
{
	class SpatialObject
	{
	public:
		bool dynamic;
		float x, y, w, h;
		FG::Entity* entity;
		uint64_t mask;
		uint64_t collidesWith;
	};

	__m128 c;
	__m128 w;
std::vector<std::vector<SpatialObject>> buckets;

public:
	CollisionSystemImpl() : c(_mm_set_ps(0, 0, 0, 0)), w(_mm_set_ps(0, 0, 0, 0))
	{
	}

	bool isColliding(const SpatialObject& a, const SpatialObject& b) const
	{
		return (a.x + a.w >= b.x &&
			b.x + b.w >= a.x &&
			a.y + a.h >= b.y &&
			b.y + b.h >= a.y);
	}

	void Setup(const int worldX, const int worldY, const float bucketSize)
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

	void RegisterCollider(const FG::Vector2D& pos, const FG::Vector2D& size, FG::Entity* entity, bool dynamic, uint64_t mask, uint64_t collidesWith)
	{
		SpatialObject object;
		object.x = pos.x;
		object.y = pos.y;
		object.w = size.x;
		object.h = size.y;
		object.entity = entity;
		object.dynamic = dynamic;
		object.mask = mask;
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

	void Clear()
	{
		for (int i = 0; i < buckets.size(); i++)
		{
			buckets[i].clear();
		}
	}

	void TestCollisions()
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

					bool aCollidesWithB = (a.collidesWith >> b.mask) & 1U;
					bool bCollidesWithA = (b.collidesWith >> a.mask) & 1U;
					if (!aCollidesWithB && !bCollidesWithA)
					{
						continue;
					}
					if (a.dynamic || b.dynamic)
					{
						if (isColliding(a, b))
						{
							if (aCollidesWithB)
							{
								a.entity->OnCollision(b.entity);
							}
							if (bCollidesWithA)
							{
								b.entity->OnCollision(a.entity);
							}
						}
					}
				}
			}
		}
		Clear();
	}
};

#pragma endregion


CollisionSystem* CollisionSystem::system = new CollisionSystem();

CollisionSystem::CollisionSystem()
{
	impl = std::make_unique<CollisionSystemImpl>();
}

void CollisionSystem::Setup(const int worldX, const int worldY, const float bucketSize)
{
	impl->Setup(worldX, worldY, bucketSize);
}

void CollisionSystem::RegisterCollider(const FG::Vector2D& pos, const FG::Vector2D& size, FG::Entity* entity, bool dynamic, uint64_t mask, uint64_t collidesWith)
{
	impl->RegisterCollider(pos, size, entity, dynamic, mask, collidesWith);
}

void CollisionSystem::TestCollisions()
{
	impl->TestCollisions();
}

void CollisionSystem::Clear()
{
	impl->Clear();
}
