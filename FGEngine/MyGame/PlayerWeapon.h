#pragma once
#include "Vector2D.h"
#include <stdint.h>

static float SINGLE_LIGHT_SPEED = 10.0f;
static float SINGLE_DARK_SPEED = 10.0f;
static float BURST_LIGHT_SPEED = 20.0f;
static float BURST_DARK_SPEED = 20.0f;
static float LAZER_LIGHT_SPEED = 10.0f;

struct SingleLightWeapon 
{
	static void Shoot(const FG::Vector2D& startPos, const FG::Vector2D& dir, const uint64_t collidesWith);
};

struct SingleDarkWeapon
{
	static void Shoot(const FG::Vector2D& startPos, const FG::Vector2D& dir, const uint64_t collidesWith);
};

struct BurstDarkWeapon
{
	static void Shoot(const FG::Vector2D& startPos, const FG::Vector2D& dir, const uint64_t collidesWith);
};

struct BurstLightWeapon
{
	static void Shoot(const FG::Vector2D& startPos, const FG::Vector2D& dir, const uint64_t collidesWith);
};

struct LazerLightWeapon
{
	static void Shoot(const FG::Vector2D& startPos, const FG::Vector2D& dir, const uint64_t collidesWith);
};

struct LazerDarkWeapon
{
	static void Shoot(const FG::Vector2D& startPos, const FG::Vector2D& dir, const uint64_t collidesWith);
};