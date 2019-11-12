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
	void RegisterCollider(const FG::Vector2D& pos, const FG::Vector2D& size, FG::Entity* entity, bool dynamic, uint64_t objectLayer, uint64_t collidesWith);
	void TestCollisions();
	void Clear();

private:

	template <typename... Ts>
	typename std::enable_if<sizeof...(Ts) == 0>::type GetCollisionMaskA(uint64_t& mask) { }

	template <typename T, typename... Ts>
	void GetCollisionMaskA(uint64_t& mask) {

		uint32_t id = CollisionMasker::id<T>();
		mask |= 1ULL << id;
		GetCollisionMaskA<Ts...>(mask);
	}
public:
	template<typename... Ts>
	uint64_t GetCollisionMask()
	{
		uint64_t mask;
		GetCollisionMaskA<Ts...>(mask);
		return mask;
	}
	template <typename T>
	uint64_t GetObjectLayer()
	{
		return CollisionMasker::id<T>();
	}

};

