#pragma once

#include "Component.h"
#include "ParticleEmitterComponent.h"
#include "HealthComponent.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"
#include "Vector.h"
#include "RenderSystem.h"
#include <SFML/Graphics.hpp>

namespace XYZEngine
{
	struct EffectParams
	{
		ParticleParams particleParams;
	};

	class EffectManagerComponent : public Component
	{
	public:
		explicit EffectManagerComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void PlayHitEffect(const Vector2Df& origin);
		void PlayPositiveEffect(const Vector2Df& origin);
		void PlayDustEffect(const Vector2Df& origin);

		// Настройки
		void SetHitParams(const ParticleParams& params) { hitParams = params; }
		void SetPositiveParams(const ParticleParams& params) { positiveParams = params; }
		void SetDustParams(const ParticleParams& params, float speedThreshold) { dustParams = params; dustSpeedThreshold = speedThreshold; }
		// Настройка смены цвета при низком HP (baseTint — обычный, lowTint — при low HP). threshold01: 0..1
		void SetLowHealthTint(const sf::Color& baseTint, const sf::Color& lowTint, float threshold01);

		// Аура (периодический хил/эффект)
		struct AuraSettings
		{
			float periodSeconds = 0.f;
			float healAmount = 0.f;
			float pulseDuration = 0.f;
			float minRadius = 0.f;
			float maxRadius = 0.f;
			sf::Color color = sf::Color::White;
			sf::Uint8 minAlpha = 0;
			sf::Uint8 maxAlpha = 0;
		};
		void SetAura(const AuraSettings& settings);

		void SetHealthComponent(HealthComponent* hc) { health = hc; }

	private:
		ParticleEmitterComponent* emitter = nullptr;
		HealthComponent* health = nullptr;
		TransformComponent* transform = nullptr;
		SpriteRendererComponent* renderer = nullptr;

		ParticleParams hitParams;
		ParticleParams positiveParams;
		ParticleParams dustParams;
		float dustSpeedThreshold = 0.f;

		AuraSettings auraSettings;
		float auraTimer = 0.f;
		float auraPulseTimer = 0.f;
		sf::CircleShape auraCircle;

		// Тинт по здоровью
		sf::Color baseTint = sf::Color::White;
		sf::Color lowHealthTint = sf::Color::White;
		float lowHealthThreshold = 0.f; 
	};
}


