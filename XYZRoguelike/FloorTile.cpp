#include "FloorTile.h"

namespace XYZRoguelike
{
	FloorTile::FloorTile(float sizePixels)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("FloorTile");

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		auto tex = XYZEngine::ResourceSystem::Instance()->GetTextureShared(Config::Floor::TextureName);
		if (tex && renderer)
		{
			renderer->SetTexture(*tex);
			const int tileSizeInt = static_cast<int>(sizePixels);
			renderer->SetPixelSize(tileSizeInt, tileSizeInt);
			// Светлый голубовато-серый оттенок для контраста с аурой
			renderer->SetColor(sf::Color(190, 210, 220));
		}
		else
		{
			LOG_WARN("Floor texture missing: expected '" + std::string(Config::Floor::TextureName) + "'");
		}
	}

	XYZEngine::GameObject* FloorTile::GetGameObject()
	{
		return gameObject;
	}

	void FloorTile::SetPosition(float x, float y)
	{
		if (auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>())
		{
			transform->SetWorldPosition(x, y);
		}
	}

	void FloorTile::SetSize(float sizePixels)
	{
		if (renderer != nullptr)
		{
			const int tileSizeInt = static_cast<int>(sizePixels);
			renderer->SetPixelSize(tileSizeInt, tileSizeInt);
		}
	}
}


