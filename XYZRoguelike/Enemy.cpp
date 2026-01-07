#include "Enemy.h"

namespace XYZRoguelike
{
	Enemy::Enemy()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		// Используем другую текстуру, чтобы отличать врага от игрока
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("platform"));
		renderer->SetPixelSize(64, 16);

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		chase = gameObject->AddComponent<XYZEngine::PlayerChaseComponent>();
	}

	XYZEngine::GameObject* Enemy::GetGameObject()
	{
		return gameObject;
	}

	void Enemy::SetChaseTarget(XYZEngine::GameObject* target)
	{
		if (chase != nullptr)
		{
			chase->SetTarget(target);
		}
	}

	void Enemy::SetChaseParams(float detectionRadius, float speed, float stopDistance)
	{
		if (chase != nullptr)
		{
			chase->SetDetectionRadius(detectionRadius);
			chase->SetSpeed(speed);
			chase->SetStopDistance(stopDistance);
		}
	}
}

