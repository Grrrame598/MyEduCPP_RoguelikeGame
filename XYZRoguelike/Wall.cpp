#include "Wall.h"
#include <GameWorld.h>

namespace XYZRoguelike
{
	Wall::Wall(float widthPixels, float heightPixels)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Wall");

		renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("platform"));
		renderer->SetPixelSize(widthPixels, heightPixels);

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

