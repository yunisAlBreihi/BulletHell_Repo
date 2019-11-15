#pragma once
#include "Vector2D.h"
#include "Entity.h"
#include <memory>
#include <stdint.h>
#include "EntityType.h"
class CollisionSystemImpl;



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
	void RegisterCollider(const FG::Vector2D& pos, const FG::Vector2D size, FG::Entity* entity, bool dynamic);
	void TestCollisions();
	void Clear();

};

