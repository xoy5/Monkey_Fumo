#pragma once
#include "Surface.h"
#include "Graphics.h"
#include "Font.h"
#include "Stats.h"
#include "SpriteEffect.h"
#include "Vec2.h"
#include "Rect.h"
#include "Mouse.h"
#include "Stats.h"
#include "Rect.h"
#include <vector>

class Window
{
public:
	Window();
	void Update(const Mouse& mouse, Stats & stats, bool stopGame);
	void Draw(Graphics& gfx, const Mouse& mouse, const Stats & stats, bool stopGame) const;
	void DrawBackground(Graphics& gfx) const;
private:
	int NumsInNum(int num)const;
private:
	Font font = Font("Images/Fixedsys16x28.bmp");
	mutable RectI windowRect = { 0, 175, 0, 100 };

	bool hacks = false;
	bool isClicked = false;

	// heart
	const Surface heartBorder = Surface("Images/heart90x75empty.bmp");
	const Surface heartToFill = Surface("Images/heart90x75toFill.bmp");
	const Surface heartTemplate = Surface("Images/heart90x75template.bmp");
	static constexpr int heartPos = 10;

	// run
	const Surface run = Surface("Images/run75x10.bmp");
	const Vei2 runPos{ 17, 90 };

	// coin
	const Surface coin = Surface("Images/coin41x41.bmp");
	const Vei2 coinPos = { 120, 20 };
	const Vei2 textPos = { 170, 30 };

	// scope
	const Surface scope = Surface("Images/scope21x21.bmp");
	const int scopeSpriteCenter = 10;

	// menu
	Surface menu = Surface("Images/menu200x70.bmp");
	static constexpr int menuWidth = 200;
	static constexpr int menuHeight = 70;

	Surface controls = Surface("Images/controls300x350.bmp");
	static constexpr int controlsWidth = 300;
	static constexpr int controlsHeight = 350;

	Surface hacksYes = Surface("Images/heatsYes270x81.bmp");
	Surface hacksNo = Surface("Images/heatsNo270x81.bmp");
	static constexpr int hacksWidth = 270;
	static constexpr int hacksHeight = 81;

	Surface plus = Surface("Images/plus34x34.bmp");
	Surface minus = Surface("Images/minus34x34.bmp");
	Surface hacksStats = Surface("Images/hacksStats145x189.bmp");
	static constexpr int hacksStatsWidth = 145;
	static constexpr int hacksStatsHeight = 189;

	std::vector<RectI> plusVec;
	std::vector<RectI> minusVec;

	const int halfScreen = Graphics::ScreenWidth / 2;
	RectI hacksRect = { halfScreen + halfScreen / 2 - hacksWidth / 2,
						halfScreen + halfScreen / 2 - hacksWidth / 2 + hacksWidth,
						150,
						150 + hacksHeight };  

	const Vei2 hacksPos = { halfScreen + halfScreen / 2 - hacksWidth / 2, 150 };
};