#include "Enemy.h"
#include <Logger.h>
#include <HealthComponent.h>
#include <AttackComponent.h>
#include <ParticleEmitterComponent.h>
#include <EffectManagerComponent.h>
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

		auto health = gameObject->AddComponent<XYZEngine::HealthComponent>();
		health->SetMaxHealth(Config::Enemy::MaxHealth);
		health->SetHealth(Config::Enemy::StartHealth);
		health->SetArmor(Config::Enemy::Armor);

		auto emitter = gameObject->AddComponent<XYZEngine::ParticleEmitterComponent>();
		chase = gameObject->AddComponent<XYZEngine::PlayerChaseComponent>();
		auto effects = gameObject->AddComponent<XYZEngine::EffectManagerComponent>();
		effects->SetHealthComponent(health);
		if (effects != nullptr)
		{
			XYZEngine::ParticleParams hitParams;
			hitParams.count = 16;
			hitParams.minSpeed = 120.f;
			hitParams.maxSpeed = 220.f;
			hitParams.minLife = 0.25f;
			hitParams.maxLife = 0.45f;
			hitParams.minSize = 3.f;
			hitParams.maxSize = 6.f;
			hitParams.color = sf::Color(220, 60, 60);
			effects->SetHitParams(hitParams);

			XYZEngine::ParticleParams positiveParams;
			positiveParams.count = 14;
			positiveParams.minSpeed = 80.f;
			positiveParams.maxSpeed = 160.f;
			positiveParams.minLife = 0.35f;
			positiveParams.maxLife = 0.6f;
			positiveParams.minSize = 3.f;
			positiveParams.maxSize = 6.f;
			positiveParams.color = sf::Color(90, 200, 120);
			effects->SetPositiveParams(positiveParams);

			XYZEngine::ParticleParams dustParams;
			dustParams.count = Config::Effects::Dust::Count;
			dustParams.minSpeed = Config::Effects::Dust::MinSpeed;
			dustParams.maxSpeed = Config::Effects::Dust::MaxSpeed;
			dustParams.minLife = Config::Effects::Dust::MinLife;
			dustParams.maxLife = Config::Effects::Dust::MaxLife;
			dustParams.minSize = Config::Effects::Dust::MinSize;
			dustParams.maxSize = Config::Effects::Dust::MaxSize;
			dustParams.color = sf::Color(Config::Effects::Dust::ColorR, Config::Effects::Dust::ColorG, Config::Effects::Dust::ColorB);
			effects->SetDustParams(dustParams, Config::Effects::Dust::SpeedThreshold);
		}

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

