/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Vec2.h"
#include "SpriteEffect.h"
#include <cmath>

#include <assert.h>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	monkey(Vec2(390, 290), "Images/monkey50x50.bmp")
{
	std::ifstream file("Images/zdjecia.txt");
	if (file.is_open()) { 

		std::string filename;

		while (std::getline(file, filename)) 
		{ 
			sprites.push_back("Images/" + filename + "75x75.bmp");
		}

		file.close();
	}
	else 
	{
		assert(!file.is_open());
	}

	for (int i = 0; i < std::min((int)sprites.size(), 3); ++i)
	{
		enemies.push_back(Enemy(std::string(sprites[i]), posSpawn[i+1]));
	}

}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(1.0f / static_cast<float>(Hz), elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();

}

void Game::UpdateModel(float  dt)
{
	if (0.0f < monkey.GetStats().hp)
	{
		if (!stopGame)
		{
			Vec2 dir = { 0.0f, 0.0f };
			if (wnd.kbd.KeyIsPressed('A'))
			{
				dir += {-1.0f, 0.0f};
			}
			if (wnd.kbd.KeyIsPressed('D'))
			{
				dir += {1.0f, 0.0f};
			}
			if (wnd.kbd.KeyIsPressed('W'))
			{
				dir += {0.0f, -1.0f};
			}
			if (wnd.kbd.KeyIsPressed('S'))
			{
				dir += {0.0f, 1.0f};
			}

			monkey.SetDirection(dir);
			monkey.Update(dt, enemies, wnd.kbd, wnd.mouse);
			for (auto& enemy : enemies)
			{
				enemy.Update(dt, monkey.GetStats().GetPosCenter());
			}

			enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
				return enemy.GetHp() <= 0;
			}), enemies.end());

			timeToSpawnLeft += dt;
			if (timeToSpawnLeft > timeToSpawn)
			{
				timeToSpawnLeft -= timeToSpawn;
				enemies.push_back(Enemy{ sprites[i % sprites.size()], posSpawn[i % 4]});
				i++;
			}
		}

		if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
		{
			if (!keyPressed)
			{
				stopGame = stopGame ? false : true;
			}
			keyPressed = true;
		}
		else
		{
			keyPressed = false;
		}

		window.Update(wnd.mouse, monkey.GetStats(), stopGame);
	}
}

void Game::ComposeFrame()
{
	if ( 0.0f < monkey.GetStats().hp)
	{
		window.DrawBackground(gfx);
		monkey.Draw(gfx, wnd.mouse.GetPos()); // monkey character and bananas
		for (const auto& enemy : enemies)
		{
			enemy.Draw(gfx);
		}
		window.Draw(gfx, wnd.mouse, monkey.GetStats(), stopGame);
	}
	else
	{
		gfx.DrawSprite(0, 0, miska, SpriteEffect::Chroma{});
	}
}
