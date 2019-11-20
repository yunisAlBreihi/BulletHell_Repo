#pragma once

#include <Application.h>
#include <Time.h>
#include <memory>
#include "BasicTimer.h"
#include "Spawner.h"
#include "EnemyDoubleWaveSweep.h"
namespace FG
{
	class Window;
	class InputManager;
	class EntityManager;
	class ResourceManager;
}

class Camera;
class Renderer;
class Player;

class GameApplication : public FG::Application
{
public:
	virtual bool Initialize() override;
	virtual void Run() override;
	virtual void Shutdown() override;

private:
	FG::Window* window = nullptr;
	FG::InputManager* inputManager = nullptr;
	FG::EntityManager* entityManager = nullptr;
	FG::ResourceManager* resourceManager = nullptr;
	std::unique_ptr<Renderer> renderer;
	FG::Time time;
	Player* player;

	//For Enemy spawners
	BasicTimer DoubleWaveSweepTimer;
	Spawner<EnemyDoubleWaveSweep> DoubleWaveSweepSpawner;
	float DoubleWaveSweepMaxTime = 0.3f;

	template<typename T>
	void SpawnWaves(float dt, Spawner<T>* spawner, BasicTimer* timer,FG::Vector2D spawnPosition);

	void SpawnXTimes(float& spawnTimer, float minSpawnTime, float spawnerMaxTime, int spawnCount, FG::Vector2D spawnPosition);
	void SpawnXTimesRandom(float& spawnTimer, float spawnerMaxTime, int spawnCount, FG::Vector2D spawnPosition);
};

FG::Application* FG::CreateApplication()
{
	return new GameApplication();
}


