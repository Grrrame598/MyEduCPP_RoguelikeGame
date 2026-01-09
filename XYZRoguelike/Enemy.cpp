#include "Enemy.h"
#include <Logger.h>
#include <HealthComponent.h>
#include <AttackComponent.h>
#include "../Config/GameConfig.h"
#include <cassert>

namespace XYZRoguelike
{
	Enemy::Enemy()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		if (auto tex = XYZEngine::ResourceSystem::Instance()->GetTextureShared("platform"))
		{
			renderer->SetTexture(*tex);
			renderer->SetPixelSize(Config::Enemy::SpriteWidth, Config::Enemy::SpriteHeight);
		}
		else
		{
			LOG_ERROR("Failed to set enemy texture: platform");
			assert(false && "Texture 'platform' is required for Enemy");
			return;
		}

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		chase = gameObject->AddComponent<XYZEngine::PlayerChaseComponent>();

		auto health = gameObject->AddComponent<XYZEngine::HealthComponent>();
		health->SetMaxHealth(Config::Enemy::MaxHealth);
		health->SetHealth(Config::Enemy::StartHealth);
		health->SetArmor(Config::Enemy::Armor);

		attack = gameObject->AddComponent<XYZEngine::AttackComponent>();
		attack->SetDamage(Config::Enemy::AttackDamage);
		attack->SetRange(Config::Enemy::AttackRange);
		attack->SetCooldown(Config::Enemy::AttackCooldown);
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

