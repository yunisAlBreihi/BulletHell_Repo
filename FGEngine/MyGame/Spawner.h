#pragma once
#include "EntityManager.h"
template <typename T>
class Spawner
{
public:
	template <typename... Args>
	void Execute(Args&& ... args);




};

template<typename T>
template<typename ...Args>
inline void Spawner<T>::Execute(Args&& ...args)
{
	FG::EntityManager::Instance()->CreateEntity<T>(args...);
}
