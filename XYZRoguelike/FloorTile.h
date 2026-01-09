#pragma once

#include <GameWorld.h>
#include <GameObject.h>
#include <SpriteRendererComponent.h>
#include <ResourceSystem.h>
#include <cassert>
#include <Logger.h>
#include "../Config/GameConfig.h"

namespace XYZRoguelike
{
	class FloorTile
	{
	public:
		explicit FloorTile(float sizePixels);

		XYZEngine::GameObject* GetGameObject();
		void SetPosition(float x, float y);
		void SetSize(float sizePixels);

	private:
		XYZEngine::GameObject* gameObject = nullptr;
		XYZEngine::SpriteRendererComponent* renderer = nullptr;
	};
}


