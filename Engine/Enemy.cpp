#include "Enemy.h"
#include <random>
#include <cmath>

Enemy::Enemy(const std::string& filename, const Vec2& pos)
	:
	sprite(Surface(filename)),
	pos(pos)
{}

void Enemy::Update(float dt, const Vec2& monkeyPos)
{
	changeTimeCur += dt;

	if (effectActive) // effect ( like take damage )
	{
		effectTime += dt;
		if (effectTime >= effectDuration)
		{
			effectActive = false;
		}
	}

	if (effectActiveHit)
	{
		effectTimeHit += dt;
		if (effectTimeHit >= effectDurationHit)
		{
			effectActiveHit = false;
		}
	}

	if (changeTimeCur > changeTimeDir && !effectActiveHit)
	{
		changeTimeCur -= changeTimeDir;

		std::mt19937 rng(std::random_device{}());
		std::uniform_real_distribution<float>dir{-1.0f, 1.0f};

		curDir = ((monkeyPos - (pos + Vec2{spriteWidth / 2.0f, spriteHeight / 2.0f})).GetNormalize() + Vec2{dir(rng), dir(rng)})* (std::abs((float)(101 - hp) / 100.0f) + 1.0f)* speed;
	}
	else if (effectActiveHit)
	{
		curDir = ((pos + Vec2{spriteWidth / 2.0f, spriteHeight / 2.0f}) - monkeyPos).GetNormalize()* (std::abs((float)(101 - hp) / 100.0f) + 1.0f)* speed;;
	}
	pos += curDir;
}

void Enemy::Hit(const Vec2& bananaDir, int dmg)
{
	hp -= dmg;
	ActivateEffect();
}

void Enemy::Draw(Graphics& gfx) const
{
	effectActive ? gfx.DrawSprite((int)pos.x, (int)pos.y, sprite, SpriteEffect::Substitution{Colors::Red}) :
		gfx.DrawSprite((int)pos.x, (int)pos.y, sprite, SpriteEffect::Chroma{});
}

void Enemy::ActivateEffect()
{
	effectActive = true;
	effectTime = 0.0f;
	effectActiveHit = true;
	effectTimeHit = 0.0f;
}

RectI Enemy::GetRect() const
{
	return RectI(pos.x, pos.x + spriteWidth, pos.y, pos.y + spriteHeight);
}

int Enemy::GetHp() const
{
	return hp;
}
