#pragma once
#include <string>
#include <vector> 

#include "Graphics.h"
#include "Animation.h"
#include "Surface.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Vec2.h"
#include "SpriteEffect.h"
#include "Stats.h"

class Character
{
private:
	enum class Sequence
	{
		WalkingLeft,
		WalkingRight,
		WalkingUp,
		WalkingDown,
		StandingLeft,
		StandingRight,
		StandingUp,
		StandingDown,
		Count
	};

public:
	Character(const Vec2& pos, const std::string & nameFile);
	void Draw(Graphics& gfx, const Vei2 & mousePos) const;
	void SetDirection(const Vec2& dir);
	void Update(float dt, std::vector<Enemy> & enemies, const Keyboard & kbd, const Mouse & mouse);
	void ActivateEffect();
	Stats& GetStats();
	const Stats& GetStats() const;
	RectI GetRect() const;

private:
	// other
	Weapon weapon; 
	Stats stats;

	// effect
	static constexpr float effectDuration = 0.045f;
	float effectTime = 0.0f;
	bool effectActive = false;

	// draw information
	const Vei2 monkeyPosCenter { 25, 25 };
	std::vector<Animation> animations;
	Surface sprite;
	Sequence iCurSequence = Sequence::StandingDown;
};
