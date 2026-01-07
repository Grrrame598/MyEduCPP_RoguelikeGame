#pragma once

#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include <vector>

using namespace XYZEngine;

namespace XYZRoguelike
{
	class DeveloperLevel : public Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;
	private:
		std::shared_ptr<Player> player;
		std::shared_ptr<Enemy> enemy;
		std::vector<std::shared_ptr<Wall>> walls;

		void CreatePerimeterWalls(float halfWidth, float halfHeight, float wallThickness, float segmentLength);
	};
}