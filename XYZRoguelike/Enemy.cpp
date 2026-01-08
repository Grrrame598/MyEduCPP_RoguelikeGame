#include "Enemy.h"
#include <Logger.h>
#include <HealthComponent.h>
#include <AttackComponent.h>
#include <cassert>

namespace XYZRoguelike
{
	Enemy::Enemy()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		// Используем другую текстуру, чтобы отличать врага от игрока
		if (auto tex = XYZEngine::ResourceSystem::Instance()->GetTextureShared("platform"))
		{
			renderer->SetTexture(*tex);
			renderer->SetPixelSize(64, 16);
		}
		else
		{
			LOG_ERROR("Не удалось установить текстуру врага: platform");
			assert(false && "Texture 'platform' is required for Enemy");
			return;
		}

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		chase = gameObject->AddComponent<XYZEngine::PlayerChaseComponent>();

		auto health = gameObject->AddComponent<XYZEngine::HealthComponent>();
		health->SetMaxHealth(80.f);
		health->SetHealth(80.f);
		health->SetArmor(10.f);

		attack = gameObject->AddComponent<XYZEngine::AttackComponent>();
		attack->SetDamage(10.f);
		attack->SetRange(48.f);
		attack->SetCooldown(1.0f);
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

	void Enemy::SetAttackTarget(XYZEngine::GameObject* target)
	{
		if (attack != nullptr)
		{
			attack->SetTarget(target);
		}
	}
}

