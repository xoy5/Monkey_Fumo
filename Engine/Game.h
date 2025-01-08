/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Character.h"
#include "FrameTimer.h"
#include "Enemy.h"
#include "Window.h"
#include "Vec2.h"
#include <string>
#include <fstream>
class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float  dt);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;
	/********************************/
	/*  User Variables  */
	static constexpr int Hz = 60;
	Window window;

	Character monkey;
	std::vector<Enemy> enemies;

	bool stopGame = true;
	bool keyPressed = false;

	float timeToSpawn = 7.0f;
	float timeToSpawnLeft = 0.0f;
	Vec2 posSpawn[4] = { {0.0f, 0.0f}, {725.0f, 0.0f}, {0.0f, 525.0f}, {725.0f, 525.0f} };
	int i = 3; 
	std::vector<std::string> sprites;

	Surface miska = Surface("Images/miska.bmp");


	/********************************/
};