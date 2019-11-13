#pragma once
#include "Vector2D.h"
#include "Entity.h"
#include <memory>
#include <stdint.h>
class CollisionSystemImpl;

class CollisionMasker
{
	static uint32_t counter;
public:
	template<typename T>
	static uint32_t id()
	{
		static uint32_t _id = counter++;
		return _id;
	}
};

class EntityLayers
{
	template <typename... Ts>
	static typename std::enable_if<sizeof...(Ts) == 0>::type GetEntityMaskA(uint64_t& mask) { }

	template <typename T, typename... Ts>
	static void GetEntityMaskA(uint64_t& mask) {

		uint32_t id = CollisionMasker::id<T>();
		mask |= 1ULL << id;
		GetEntityMaskA<Ts...>(mask);
	}
public:
	template<typename... Ts>
	static uint64_t GetEntityMask()
	{
		uint64_t mask = 0;
		GetEntityMaskA<Ts...>(mask);
		return mask;
	}
	template <typename T>
	static uint64_t GetEntityLayer()
	{
		return CollisionMasker::id<T>();
	}
};

class CollisionSystem
{
	std::unique_ptr<CollisionSystemImpl> impl;
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
	void RegisterCollider(const FG::Vector2D& pos, const FG::Vector2D& size, FG::Entity* entity, bool dynamic);
	void TestCollisions();
	void Clear();

};

