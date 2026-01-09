#include "Wall.h"
#include <GameWorld.h>
#include <Logger.h>
#include <cassert>
#include <HealthComponent.h> // на будущее, если понадобится нерушимость/прочность

namespace XYZRoguelike
{
	Wall::Wall(float widthPixels, float heightPixels)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Wall");

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		if (auto tex = XYZEngine::ResourceSystem::Instance()->GetTextureShared("platform"))
		{
			renderer->SetTexture(*tex);
			renderer->SetPixelSize(widthPixels, heightPixels);
		}
		else
		{
			LOG_ERROR("Failed to set wall texture: platform");
			assert(false && "Texture 'platform' is required for Wall");
			return;
		}

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		body->SetKinematic(true);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
	}

	XYZEngine::GameObject* Wall::GetGameObject()
	{
		return gameObject;
	}

	void Wall::SetPosition(float x, float y)
	{
		if (auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>())
		{
			transform->SetWorldPosition(x, y);
		}
	}

	void Wall::SetSize(float widthPixels, float heightPixels)
	{
		if (renderer != nullptr)
		{
			renderer->SetPixelSize(widthPixels, heightPixels);
		}
	}
}

