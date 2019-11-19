#pragma once
#include <type_traits>
#include <stdint.h>


class EntityTypeCounter
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

		uint32_t id = EntityTypeCounter::id<T>();
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
		return EntityTypeCounter::id<T>();
	}
};
