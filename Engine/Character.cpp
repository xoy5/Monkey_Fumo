#include "Character.h"

Character::Character(const Vec2& pos, const std::string& nameFile)
	:
	sprite(nameFile)
{
	stats.pos = pos;
	for (int i = 0; i < (int)Sequence::StandingLeft; i++)
	{
		animations.emplace_back(0, 50 * i, 50, 50, 5, sprite, 0.2f);
	}
	for (int i = (int)Sequence::StandingLeft; i < (int)Sequence::Count; i++)
	{
		animations.emplace_back(0, 50 * (i - (int)Sequence::StandingLeft), 50, 50, 1, sprite, 0.2f);
	}
}

void Character::Draw(Graphics& gfx, const Vei2 & mousePos) const
{
	// drawing current animation
	if (effectActive) 
	{
		animations[(int)iCurSequence].DrawColor(Vei2(stats.pos) - monkeyPosCenter , gfx, Colors::Blue);
	}
	else
	{
		animations[(int)iCurSequence].Draw(Vei2(stats.pos) - monkeyPosCenter, gfx);
	}
	///////////////////////////////////////////////////////

	weapon.Draw(gfx); // drawing all of bananas
}

void Character::SetDirection(const Vec2& dir)
{
	if (dir.x < 0.0f)
	{
		iCurSequence = Sequence::WalkingLeft;
	}
	else if (dir.x > 0.0f)
	{
		iCurSequence = Sequence::WalkingRight;
	}
	else if (dir.y < 0.0f)
	{
		iCurSequence = Sequence::WalkingUp;
	}
	else if (dir.y > 0.0f)
	{
		iCurSequence = Sequence::WalkingDown;
	}
	else
	{
		if (stats.vel.x < 0.0f)
		{
			iCurSequence = Sequence::StandingLeft;
		}
		else if (stats.vel.x > 0.0f)
		{
			iCurSequence = Sequence::StandingRight;
		}
		else if (stats.vel.y < 0.0f)
		{
			iCurSequence = Sequence::StandingUp;
		}
		else if (stats.vel.y > 0.0f)
		{
			iCurSequence = Sequence::StandingDown;
		}
	}
	stats.vel = dir * stats.speedRun;
}

void Character::Update(float dt, std::vector<Enemy>& enemies, const Keyboard& kbd, const Mouse& mouse)
{
	if (!kbd.KeyIsPressed(VK_SPACE)) // regeneration
	{
		stats.moveElapsedTime = std::min(stats.moveCondition, stats.moveElapsedTime + ( dt / stats.moveRegeneration) );
	}

	stats.pos += stats.vel * dt; // update monkey pos

	animations[(int)iCurSequence].Update(dt); // update obj animation

	if (effectActive) // effect ( like take damage )
	{
		effectTime += dt;
		if (effectTime >= effectDuration)
		{
			effectActive = false;
		}
	}

	weapon.Update(dt, stats, enemies); // update pos of bananas

	if ( mouse.LeftIsPressed() )// shoot bananas
	{
		weapon.Shoot(stats.pos, mouse.GetPos(), stats);
	}

	if (kbd.KeyIsPressed(VK_SPACE) && 0.0f <= stats.moveElapsedTime)
	{
		stats.moveElapsedTime -= dt;
		if (stats.vel.x < 0)
		{
			stats.pos += {-stats.speedRun * dt * stats.movePower, 0};
		}
		else if (stats.vel.x > 0) 
		{
			stats.pos += {stats.speedRun * dt * stats.movePower, 0};
		}
		if (stats.vel.y < 0) 
		{
			stats.pos += {0, -stats.speedRun * dt * stats.movePower};
		}
		else if (stats.vel.y > 0) 
		{
			stats.pos += {0, stats.speedRun * dt * stats.movePower};
		}
	}

	for (const auto& enemy : enemies)
	{
		if (enemy.GetRect().IsOverlappingWith(GetRect()))
		{
			stats.hp -= 0.1f;
		}
	}
}

void Character::ActivateEffect()
{
	effectActive = true;
	effectTime = 0.0f;
}

Stats& Character::GetStats()
{
	return stats;
}

const Stats& Character::GetStats() const
{
	return stats;
}

RectI Character::GetRect() const
{
	return RectI(stats.pos.x, stats.pos.x + monkeyPosCenter.y * 2, stats.pos.y, stats.pos.y + monkeyPosCenter.y * 2);
}
