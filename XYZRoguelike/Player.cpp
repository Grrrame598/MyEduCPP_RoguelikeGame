#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <HealthComponent.h>
#include <AttackComponent.h>
#include <ParticleEmitterComponent.h>
#include <EffectManagerComponent.h>
#include "../Config/GameConfig.h"
#include <Logger.h>
#include <cassert>

namespace XYZRoguelike
{
	Player::Player()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player");
		auto playerRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		if (auto tex = XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"))
		{
			playerRenderer->SetTexture(*tex);
			playerRenderer->SetPixelSize(Config::Player::SpriteWidth, Config::Player::SpriteHeight);
			// Тёплый тинт, чтобы игрок выделялся на фоне пола
			const sf::Color baseTint(220, 150, 150);
			playerRenderer->SetColor(baseTint);
		}
		else
		{
			LOG_ERROR("Failed to set player texture: ball");
			assert(false && "Texture 'ball' is required for Player");
			return;
		}

		auto playerCamera = gameObject->AddComponent<XYZEngine::CameraComponent>();
		playerCamera->SetWindow(&XYZEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(Config::Camera::BaseWidth, Config::Camera::BaseHeight);
		playerCamera->SetShakeParams(Config::CameraShake::Amplitude, Config::CameraShake::Duration, Config::CameraShake::Frequency);

		auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		playerInput->SetMove(body, Config::Player::MoveSpeed);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto health = gameObject->AddComponent<XYZEngine::HealthComponent>();
		health->SetMaxHealth(Config::Player::MaxHealth);
		health->SetHealth(Config::Player::StartHealth);
		health->SetArmor(Config::Player::Armor);

		auto emitter = gameObject->AddComponent<XYZEngine::ParticleEmitterComponent>();
		auto effects = gameObject->AddComponent<XYZEngine::EffectManagerComponent>();
		effects->SetHealthComponent(health);
		effects->SetLowHealthTint(sf::Color(220, 150, 150), sf::Color(255, 80, 80), 0.2f); // краснеем ниже 20% HP
		playerInput->SetEffects(effects);
		// Настройки частиц: hit/positive/dust
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
		// Аура: пульсирующий круг с периодом/хилом из конфига
		{
			XYZEngine::EffectManagerComponent::AuraSettings auraSettings;
			auraSettings.periodSeconds = Config::Effects::Aura::Period;
			auraSettings.healAmount = Config::Effects::Aura::HealAmount;
			auraSettings.pulseDuration = Config::Effects::Aura::PulseDuration;
			auraSettings.minRadius = Config::Effects::Aura::MinRadius;
			auraSettings.maxRadius = Config::Effects::Aura::MaxRadius;
			auraSettings.color = sf::Color(Config::Effects::Aura::ColorR, Config::Effects::Aura::ColorG, Config::Effects::Aura::ColorB);
			auraSettings.minAlpha = Config::Effects::Aura::MinAlpha;
			auraSettings.maxAlpha = Config::Effects::Aura::MaxAlpha;
			effects->SetAura(auraSettings);
		}

		attack = gameObject->AddComponent<XYZEngine::AttackComponent>();
		attack->SetDamage(Config::Player::AttackDamage);
		attack->SetRange(Config::Player::AttackRange);
		attack->SetCooldown(Config::Player::AttackCooldown);
	}

	void Player::SetAttackTarget(XYZEngine::GameObject* target)
	{
		if (attack != nullptr)
		{
			attack->SetTarget(target);
		}
	}

	XYZEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}