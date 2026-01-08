#include "DeveloperLevel.h"
#include "TransformComponent.h"

using namespace XYZEngine;

namespace XYZRoguelike
{
	void DeveloperLevel::Start()
	{
		player = std::make_shared<Player>();
		enemy = std::make_shared<Enemy>();

		// Настраиваем преследование: цель - игрок, радиус обнаружения и скорость
		enemy->SetChaseTarget(player->GetGameObject());
		// Радиус обнаружения ~чуть больше половины диагонали 1280x720 (~800), скорость 120 (в секунду), стоп-дистанция 20
		// Возвращаем нормальное преследование игрока
		enemy->SetChaseParams(800.f, 120.f, 32.f);

		// Разнесем позиции: игрок по умолчанию в (0,0), враг внутри периметра слева-сверху
		auto enemyTransform = enemy->GetGameObject()->GetComponent<TransformComponent>();
		if (enemyTransform != nullptr)
		{
			enemyTransform->SetWorldPosition(-300.f, -180.f);
		}

		// Ставим стены по периметру окна вокруг игрока (кинематичные, блокируют движение)
		walls.clear();
		// Ширину периметра немного сузили (512 вместо 640), высоту оставили под окно 720 (±360)
		// Сегменты перекрываются (шаг меньше длины), чтобы исключить щели
		CreatePerimeterWalls(512.f, 360.f, 24.f, 48.f);
	}
	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}
	void DeveloperLevel::Stop() 
	{
		GameWorld::Instance()->Clear();
		walls.clear();
	}

	void DeveloperLevel::CreatePerimeterWalls(float halfWidth, float halfHeight, float wallThickness, float segmentLength)
	{
		auto spawnWall = [&](float x, float y, float width, float height)
		{
			auto wall = std::make_shared<Wall>(width, height);
			wall->SetPosition(x, y);
			walls.push_back(wall);
		};

		// Верхняя и нижняя грани
		for (float x = -halfWidth; x <= halfWidth; x += segmentLength)
		{
			spawnWall(x, -halfHeight, segmentLength, wallThickness);
			spawnWall(x, halfHeight, segmentLength, wallThickness);
		}

		// Левая и правая грани
		for (float y = -halfHeight; y <= halfHeight; y += segmentLength)
		{
			spawnWall(-halfWidth, y, wallThickness, segmentLength);
			spawnWall(halfWidth, y, wallThickness, segmentLength);
		}
	}
}