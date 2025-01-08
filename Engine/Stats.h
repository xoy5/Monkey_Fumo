#pragma once
#include "Vec2.h"

struct Stats
{
	Vec2 pos;
	Vec2 GetPosCenter() const {
		return pos + Vec2{25.0f, 25.0f};
	}
	Vec2 vel{ 0.0f, 0.0f };
	float hp = 100;
	int hpMax = 100;
	int coins = 2137;
	float speedRun = 100;

	// sprint
	float moveElapsedTime = 2.0f;
	float moveCondition = 2.0f;
	float movePower = 0.75f;
	float moveRegeneration = 2.5f;
	
	// upgrades
	bool bananaYellow = true;
	bool bananaBlack = true;


	// banana stasts
	int quantity = 1;
	float speed = 350.0f;
	float minSpeed = 175.0f;
	static constexpr float reduceBananaSpeed = 0.997f; // 0.995 or 0.992 by default
	float range = 800.0f;

	// by type
	int damage[3] = { 1, 5, 20 };

	// time
	float shootCooldown = 0.4f;
	float shootElapsedTime = 0.0f;

}; 