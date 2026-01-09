#include "DeveloperLevel.h"
#include "TransformComponent.h"
#include "../Config/GameConfig.h"

using namespace XYZEngine;

namespace XYZRoguelike
{
	void DeveloperLevel::Start()
	{
		// Сначала пол, чтобы отрисовывался под стенами и объектами
		floorTiles.clear();
		CreateFloor(Config::Walls::HalfWidth, Config::Walls::HalfHeight, Config::Floor::TileSize);

		// Стены по периметру (кинематичные, блокируют движение)
		walls.clear();
		// Ширину периметра немного сузили (512 вместо 640), высоту оставили под окно 720 (±360)
		// Сегменты перекрываются (шаг меньше длины), чтобы исключить щели
		CreatePerimeterWalls(Config::Walls::HalfWidth, Config::Walls::HalfHeight, Config::Walls::Thickness, Config::Walls::SegmentLength);

		player = std::make_shared<Player>();
		enemy = std::make_shared<Enemy>();

		// Настраиваем преследование: цель - игрок, радиус обнаружения и скорость
		enemy->SetChaseTarget(player->GetGameObject());
		// Радиус обнаружения/скорость/стоп-дистанция берем из конфига
		enemy->SetChaseParams(Config::Enemy::DetectionRadius, Config::Enemy::ChaseSpeed, Config::Enemy::StopDistance);

		// Настраиваем атаки: игрок ↔ враг
		enemy->SetAttackTarget(player->GetGameObject());
		player->SetAttackTarget(enemy->GetGameObject());

		// Разнесем позиции: игрок по умолчанию в (0,0), враг внутри периметра слева-сверху
		auto enemyTransform = enemy->GetGameObject()->GetComponent<TransformComponent>();
		if (enemyTransform != nullptr)
		{
			enemyTransform->SetWorldPosition(Config::Enemy::SpawnOffsetX, Config::Enemy::SpawnOffsetY);
		}

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
		floorTiles.clear();
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

	void DeveloperLevel::CreateFloor(float halfWidth, float halfHeight, float tileSize)
	{
		auto spawnTile = [&](float x, float y)
		{
			auto tile = std::make_shared<FloorTile>(tileSize);
			tile->SetPosition(x, y);
			floorTiles.push_back(tile);
		};

		// Кладём пол с запасом: выходим за периметр на толщину стен, чтобы не было просветов при шейке
		const float margin = -Config::Walls::Thickness;
		float startX = -halfWidth + margin + tileSize * 0.5f;
		float startY = -halfHeight + margin + tileSize * 0.5f;
		float endX = halfWidth - margin - tileSize * 0.5f;
		float endY = halfHeight - margin - tileSize * 0.5f;

		for (float y = startY; y <= endY; y += tileSize)
		{
			for (float x = startX; x <= endX; x += tileSize)
			{
				spawnTile(x, y);
			}
		}
	}
}