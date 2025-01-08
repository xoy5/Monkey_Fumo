#pragma once
#include <vector>

#include  "Graphics.h"
#include "Surface.h"
#include "Vec2.h"
#include "Enemy.h"
#include "Animation.h"
#include "Stats.h"

struct Banana {
	enum class Type
	{
		Green,
		Yellow,
		Black
	};

	Banana(const Vec2& pos, const Vec2& dir, int dmg, float speed, Type type)
		:
		pos(pos),
		dir(dir),
		dmg(dmg),
		speed(speed),
		beg(pos),
		type(type)
	{}
	Vec2 pos;
	Vec2 dir;
	Vec2 beg;

	int dmg;
	float speed;
	bool hit = false;

	Type type;
};

class Weapon {
public:
	Weapon() = default;
	void Shoot(const Vec2& pos, const Vec2& scopePos, Stats& stats);
	void Update(float dt, Stats & stats, std::vector<Enemy>& enemy);
	void Draw(Graphics& gfx) const;

private:
	// banana container
	std::vector<Banana>bananas;

	// draw
	const Vei2 bananaSpriteCenter = Vei2(12, 10);

	// by type 

	const Banana::Type bananaTypes[3] = {Banana::Type::Green, Banana::Type::Yellow, Banana::Type::Black};
	const Surface bananaSprite[3]  = { Surface("Images/banana25x20green.bmp"),
									   Surface("Images/banana25x20yellow.bmp"),
									   Surface("Images/banana25x20black.bmp") };

	const Surface bananaSpriteAnimation[3] = { Surface("Images/banana100x20green.bmp"),
									   Surface("Images/banana100x20yellow.bmp"),
									   Surface("Images/banana100x20black.bmp") };

	Animation bananaAnimation[3] = { Animation{ 0, 0, 25, 20, 4, bananaSpriteAnimation[0], 0.1f},
									 Animation{ 0, 0, 25, 20, 4, bananaSpriteAnimation[1], 0.1f },
									 Animation{ 0, 0, 25, 20, 4, bananaSpriteAnimation[2], 0.1f } };
}; 