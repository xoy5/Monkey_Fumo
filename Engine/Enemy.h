#pragma once
#include "Rect.h"
#include "Surface.h" 
#include "Graphics.h"
#include "SpriteEffect.h"
#include "Vec2.h"

#include <string>

class Enemy {
public:
	Enemy(const std::string& filename, const Vec2& pos);
	void Update(float dt, const Vec2 & monkeyPos);
	void Hit(const Vec2& bananaDir, int dmg);
	void Draw(Graphics& gfx) const;
	void ActivateEffect();
	RectI GetRect() const;
	int GetHp() const;
private:
	Surface sprite;
	static constexpr int spriteWidth = 74;
	static constexpr int spriteHeight = 74;
	Vec2 pos;
	Vec2 curDir = { 0.0f, 0.0f };
	float speed = 1.25f;

	int hp = 100;

	static constexpr float changeTimeDir = 0.7f;
	float changeTimeCur = 0.0f;

	// effect
	static constexpr float effectDuration = 0.045f;
	float effectTime = 0.0f;
	bool effectActive = false;

	// effectHit
	static constexpr float effectDurationHit = 0.05f;
	float effectTimeHit = 0.0f;
	bool effectActiveHit = false;
};