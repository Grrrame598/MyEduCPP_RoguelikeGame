#include "FloorTile.h"

namespace XYZRoguelike
{
	FloorTile::FloorTile(float sizePixels)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("FloorTile");

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		auto tex = XYZEngine::ResourceSystem::Instance()->GetTextureShared(Config::Floor::TextureName);
		if (tex && renderer && tex->getSize().x == tex->getSize().y && static_cast<int>(tex->getSize().x) == static_cast<int>(sizePixels))
		{
			renderer->SetTexture(*tex);
			renderer->SetPixelSize(sizePixels, sizePixels);
		}
		else
		{
			// Если нет текстуры или размер не совпадает с тайлом — логируем и не падаем.
			LOG_WARN("Floor texture missing or size mismatch: expected square " + std::to_string(static_cast<int>(sizePixels)) + " px, got " + (tex ? std::to_string(tex->getSize().x) + "x" + std::to_string(tex->getSize().y) : "null"));
			if (tex)
			{
				renderer->SetTexture(*tex);
				renderer->SetPixelSize(sizePixels, sizePixels);
			}
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
			renderer->SetPixelSize(sizePixels, sizePixels);
		}
	}
}


