#include "Window.h"
#include <string>

int Window::NumsInNum(int num) const
{
	if (num == 0) return 1;
	int nums = 0;
	for (; num > 0; num /= 10, nums++);
	return nums;
}


Window::Window()
{
	for (int i = 0; i < 6; i++)
	{
		plusVec.push_back(  RectI{ hacksPos.x + hacksStatsWidth,
							   hacksPos.x + hacksStatsWidth + 34,
							   hacksPos.y + hacksHeight + 30 * i,
							   hacksPos.y + hacksHeight + 30 * (i + 1) }  );

		minusVec.push_back( RectI{ hacksPos.x + hacksStatsWidth + 34 + 10,
								hacksPos.x + hacksStatsWidth + 34 * 2 + 10,
								hacksPos.y + hacksHeight + 30 * i,
								hacksPos.y + hacksHeight + 30 * (i + 1) }  );
	}
}

void Window::Update(const Mouse& mouse, Stats& stats, bool stopGame)
{
	if (stopGame && mouse.LeftIsPressed())
	{
		if (!isClicked)
		{
			const auto pos = mouse.GetPos();
			if (hacksRect.Contains(pos))
			{
				hacks = true;
				isClicked = true;
			}
			else
			{
				if (plusVec[0].Contains(pos))
				{
					stats.quantity++;
					isClicked = true;
				}
				else if(minusVec[0].Contains(pos))
				{
					stats.quantity--;
					isClicked = true;
				}
				else if (plusVec[1].Contains(pos))
				{
					stats.minSpeed += 10.0f;
					isClicked = true;
				}
				else if (minusVec[1].Contains(pos))
				{
					stats.minSpeed -= 10.0f;
					isClicked = true;
				}
				else if (plusVec[2].Contains(pos))
				{
					stats.coins++;
					isClicked = true;
				}
				else if (minusVec[2].Contains(pos))
				{
					stats.coins--;
					isClicked = true;
				}
				else if (plusVec[3].Contains(pos))
				{
					stats.hp += 5;
					if (stats.hpMax < stats.hp)
					{
						stats.hpMax = stats.hp;
					}
					isClicked = true;
				}
				else if (minusVec[3].Contains(pos))
				{
					stats.hp -= 3;
					isClicked = true;
				}
				else if (plusVec[4].Contains(pos))
				{
					stats.movePower += 0.1f;
					isClicked = true;
				}
				else if (minusVec[4].Contains(pos))
				{
					stats.movePower -= 0.1f;
					isClicked = true;
				}
				else if (plusVec[5].Contains(pos))
				{
					stats.moveCondition += 1.0f;
					stats.moveRegeneration = std::max(0.1f, stats.moveRegeneration - 0.1f);
					isClicked = true;
				}
				else if (minusVec[5].Contains(pos))
				{
					stats.moveCondition -= 1.0f;
					stats.moveRegeneration = std::min(2.5f, stats.moveRegeneration + 0.1f);
					isClicked = true;
				}
			}
		}
	}
	else
	{
		isClicked = false;
	}
}

void Window::Draw(Graphics& gfx, const Mouse& mouse, const Stats& stats, bool stopGame) const
{
	windowRect = { windowRect.left, 175 + 16 * NumsInNum(stats.coins), windowRect.top, windowRect.bottom };
	if (!windowRect.Contains(mouse.GetPos()) || stopGame)
	{
		// heart
		for (int y = 74; y >= 0; y--)
		{
			for (int x = 0; x < 90; x++)
			{
				if (heartToFill.GetPixel(x, y) == Colors::White)
				{
					gfx.PutPixel(x + heartPos, y + heartPos, Colors::Black);
				}
			}
		}

		for (int y = 74; y >= std::abs(74.0f / stats.hpMax * stats.hp - 74); y--)
		{
			for (int x = 0; x < 90; x++)
			{
				if (heartToFill.GetPixel(x, y) == Colors::White)
				{
					gfx.PutPixel(x + heartPos, y + heartPos, heartTemplate.GetPixel(x, y));
				}
			}
		}

		// coin
		gfx.DrawSprite(coinPos.x, coinPos.y, coin, SpriteEffect::Chroma{});
		font.DrawText(std::to_string(stats.coins), textPos, Colors::White, gfx);

		// run condition
		gfx.DrawSprite(runPos.x, runPos.y, run, SpriteEffect::Copy{});
		for (int y = 1; y < 9; y++)
		{
			for (int x = 1; x < static_cast<int>(74.0f * (stats.moveElapsedTime / stats.moveCondition)); x++)
			{
				gfx.PutPixel(x + runPos.x, y + runPos.y, Colors::White);
			}
		}

	}
	else
	{
		// heart
		for (int y = 74; y >= std::abs(74.0f / stats.hpMax * stats.hp - 74); y--)
		{
			for (int x = 0; x < 90; x++)
			{
				if (heartToFill.GetPixel(x, y) == Colors::White)
				{
					const Color dest = gfx.GetPixel(x + heartPos, y + heartPos);
					const Color src = heartTemplate.GetPixel(x, y);
					const Color blend = Color((src.GetR() + dest.GetR()) / 2,
						(src.GetG() + dest.GetG()) / 2,
						(src.GetB() + dest.GetB()) / 2);
					gfx.PutPixel(x + heartPos, y + heartPos, blend);
				}
			}
		}

		// coin
		gfx.DrawSprite(coinPos.x, coinPos.y, coin, SpriteEffect::Ghost{});
		font.DrawText(std::to_string(stats.coins), textPos, Colors::White, gfx);

		// run
		gfx.DrawSprite(runPos.x, runPos.y, run, SpriteEffect::Ghost{});
		for (int y = 1; y < 9; y++)
		{
			for (int x = 1; x < static_cast<int>(74.0f * (stats.moveElapsedTime / stats.moveCondition)); x++)
			{
				Color dest = gfx.GetPixel(x, y);
				Color blend = Color(((unsigned char)255 + dest.GetR()) / 2,
					((unsigned char)255 + dest.GetG()) / 2,
					((unsigned char)255 + dest.GetB()) / 2);
				gfx.PutPixel(x + runPos.x, y + runPos.y, blend);
			}
		}
	}

	if (stopGame)
	{
		//// Menu darknes ////
		for (int y = 0; y < Graphics::ScreenHeight; y++)
		{
			for (int x = 0; x < Graphics::ScreenWidth; x++)
			{
				Color dest = gfx.GetPixel(x, y);
				gfx.PutPixel(x, y, dest.GetR() / 2, dest.GetG() / 2, dest.GetB() / 2);
			}
		}
		///////////////////////
		gfx.DrawSprite(halfScreen - controlsWidth, 150, controls, SpriteEffect::SubstitutionButSingleColor{Color(255, 255, 240), Colors::Black});
		gfx.DrawSprite(halfScreen - menuWidth / 2, 50, menu, SpriteEffect::SubstitutionButSingleColor{Color(255, 255, 240), Colors::Black});

		if (hacks)
		{
			gfx.DrawSprite(hacksPos.x, hacksPos.y, hacksYes, SpriteEffect::SubstitutionButSingleColor{Color(255, 255, 240), Colors::Black});
			gfx.DrawSprite(hacksPos.x, hacksPos.y + 80, hacksStats, SpriteEffect::SubstitutionButSingleColor{Color(255, 255, 240), Colors::Black});
			for (int i = 0; i < 6; i++)
			{
				gfx.DrawSprite(plusVec[i].left, plusVec[i].top, plus, SpriteEffect::SubstitutionButSingleColor{Color(255, 255, 240), Colors::Black});
				gfx.DrawSprite(minusVec[i].left, minusVec[i].top, minus, SpriteEffect::SubstitutionButSingleColor{Color(255, 255, 240), Colors::Black});
			}
			font.DrawText(std::to_string(stats.quantity), { minusVec[0].right + 10, minusVec[0].top + 3 }, Colors::White, gfx);
			font.DrawText(std::to_string((int)stats.minSpeed),	  { minusVec[1].right + 10, minusVec[1].top + 3 }, Colors::White, gfx);
			font.DrawText(std::to_string(stats.coins),	  { minusVec[2].right + 10, minusVec[2].top + 3 }, Colors::White, gfx);
			font.DrawText(std::to_string((int)stats.hp),	  { minusVec[3].right + 10, minusVec[3].top + 3 }, Colors::White, gfx);
			font.DrawText(std::to_string(stats.movePower), { minusVec[4].right + 10, minusVec[4].top + 3 }, Colors::White, gfx);
			font.DrawText(std::to_string((int)stats.moveCondition), { minusVec[5].right + 10, minusVec[5].top + 3 }, Colors::White, gfx);
		}
		else
		{
			gfx.DrawSprite(hacksPos.x, hacksPos.y, hacksNo, SpriteEffect::SubstitutionButSingleColor{Color(255, 255, 240), Colors::Black});
			gfx.DrawSprite(hacksPos.x, hacksPos.y + 80, hacksStats, SpriteEffect::SubstitutionButSingleColor{Color(55, 55, 50), Colors::Black});
		}
	}
	gfx.DrawSprite(mouse.GetPosX() - scopeSpriteCenter, mouse.GetPosY() - scopeSpriteCenter, scope, SpriteEffect::Chroma{}); // cursor

	if (hacks)
	{
		font.DrawText("HACKS", { 720, 0 }, Colors::Red, gfx);
	}
}

void Window::DrawBackground(Graphics& gfx) const
{
	for (int y = 0; y < Graphics::ScreenHeight; y++)
	{
		for (int x = 0; x < Graphics::ScreenWidth; x++)
		{
			gfx.PutPixel(x, y, 30, 30, 40);
		}
	}
}
