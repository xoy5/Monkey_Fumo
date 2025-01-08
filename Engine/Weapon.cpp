#include <random>
#include <algorithm>
#include <assert.h>
#include <math.h>

#include "Stats.h"
#include "Weapon.h"
#include "Enemy.h"
#include "SpriteEffect.h"
#include "Rect.h"

void Weapon::Shoot(const Vec2& pos, const Vec2& scopePos, Stats& stats)
{
	if (stats.shootElapsedTime >= stats.shootCooldown)
	{
		assert(stats.quantity >= 0);
		stats.shootElapsedTime = 0;
		//////////////////////////// RNG /////////////////////////////
		int iOfBanana = stats.bananaBlack ? 2 : stats.bananaYellow ? 1 : 0;
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int>randomBanana(0, iOfBanana);
		//////////////////////////////////////////////////////////////

		// first banana
		int r = randomBanana(rng);
		bananas.emplace_back(Banana{ pos - bananaSpriteCenter, (scopePos - pos).GetNormalize(), stats.damage[r], stats.speed, bananaTypes[r] });

		// the rest of the bananas
		const float toRangeVec = stats.range / (scopePos - pos).GetLength();

		for (size_t i = 1; i < stats.quantity; i++)
		{
			r = randomBanana(rng);
			float angleIter = static_cast<float>((static_cast<int>(i) + 1) / 2) * (i % 2 == 0 ? 0.1f : -0.1f); // 0.1; -0.1; 0.2; -0.2; 0.3; -0.3; ...
			Vec2 dir = (scopePos - pos).GetNormalize(); 

			float rotatedX = dir.x * cos(angleIter) - dir.y * sin(angleIter);
			float rotatedY = dir.x * sin(angleIter) + dir.y * cos(angleIter);
			Vec2 dirNewBanana(rotatedX, rotatedY);

			bananas.emplace_back(Banana{ pos - bananaSpriteCenter, dirNewBanana, stats.damage[r], stats.speed, bananaTypes[r] });
		}
	}
}

void Weapon::Update(float dt, Stats & stats, std::vector<Enemy>& enemy)
{
	stats.shootElapsedTime += dt; // cooldown
	for (size_t i = 0; i < 3; i++)
	{
		bananaAnimation[i].Update(dt);
	}

	// clean vector bananas
	for (size_t i = 0; i < bananas.size(); ++i)
	{
		if (!(Graphics::GetScreenRect().Contains(Vei2(bananas[i].pos))) || stats.range <= (bananas[i].pos - bananas[i].beg).GetLength())
		{
			bananas[i].hit = true;
		}
		else
		{
			for (size_t j = 0; j < enemy.size(); ++j)
			{
				if (bananas[i].hit) break;
				const auto pos = Vei2(bananas[i].pos);
				bananas[i].hit = enemy[j].GetRect().IsOverlappingWith(RectI{ pos.x, pos.x + (int)bananaSpriteCenter.x * 2, pos.y, pos.y + (int)bananaSpriteCenter.y * 2 - 1 });
				if (bananas[i].hit)
				{
					enemy[j].Hit( bananas[i].dir, stats.damage[ static_cast<int>(bananas[i].type) ]);
				}
			}
		}
	}

	bananas.erase(std::remove_if(bananas.begin(), bananas.end(), [](const Banana& banana) {
		return banana.hit;
	}), bananas.end());

	// move and reduce
	for (size_t i = 0; i < bananas.size(); ++i)
	{
		bananas[i].pos += bananas[i].dir * bananas[i].speed * dt;

		float distance = (bananas[i].pos - bananas[i].beg).GetLength();
		bananas[i].speed = std::max(bananas[i].speed * stats.reduceBananaSpeed, stats.minSpeed);
	}
}

void Weapon::Draw(Graphics& gfx) const
{
	for (const Banana& banana : bananas)
	{
		//gfx.DrawSprite((int)banana.pos.x, (int)banana.pos.y, bananaSprite[static_cast<int>(banana.type)], SpriteEffect::Chroma{});
		bananaAnimation[(int)banana.type].Draw(banana.pos - bananaSpriteCenter, gfx);
	}
}
