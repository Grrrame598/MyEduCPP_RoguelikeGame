#include "pch.h"
#include "EffectManagerComponent.h"

namespace XYZEngine
{
	EffectManagerComponent::EffectManagerComponent(GameObject* gameObject)
		: Component(gameObject)
	{
		emitter = gameObject->GetComponent<ParticleEmitterComponent>();
		transform = gameObject->GetComponent<TransformComponent>();
		renderer = gameObject->GetComponent<SpriteRendererComponent>();
		auraCircle.setPointCount(24);
	}

	void EffectManagerComponent::SetAura(const AuraSettings& settings)
	{
		auraSettings = settings;
		auraTimer = auraSettings.periodSeconds;
		auraPulseTimer = 0.f;
	}

	void EffectManagerComponent::SetLowHealthTint(const sf::Color& baseTintIn, const sf::Color& lowTintIn, float threshold01)
	{
		baseTint = baseTintIn;
		lowHealthTint = lowTintIn;
		lowHealthThreshold = threshold01;
		if (lowHealthThreshold < 0.f) lowHealthThreshold = 0.f;
		if (lowHealthThreshold > 1.f) lowHealthThreshold = 1.f;
	}

	void EffectManagerComponent::Update(float deltaTime)
	{
		// Периодический эффект ауры (опционально с хилом)
		if (auraSettings.periodSeconds > 0.f && transform != nullptr)
		{
			auraTimer -= deltaTime;
			if (auraTimer <= 0.f)
			{
				auraTimer = auraSettings.periodSeconds;
				auraPulseTimer = auraSettings.pulseDuration;

				if (health != nullptr && auraSettings.healAmount > 0.f && !health->IsDead())
				{
					float newHealth = std::min(health->GetMaxHealth(), health->GetHealth() + auraSettings.healAmount);
					health->SetHealth(newHealth);
				}
			}
		}

		if (auraPulseTimer > 0.f)
		{
			auraPulseTimer = std::max(0.f, auraPulseTimer - deltaTime);
		}

		// Тинт по низкому здоровью
		if (renderer == nullptr)
		{
			renderer = gameObject->GetComponent<SpriteRendererComponent>();
		}
		if (renderer != nullptr && health != nullptr && lowHealthThreshold > 0.f && health->GetMaxHealth() > 0.f)
		{
			float ratio = health->GetHealth() / health->GetMaxHealth();
			if (ratio <= lowHealthThreshold)
			{
				renderer->SetColor(lowHealthTint);
			}
			else
			{
				renderer->SetColor(baseTint);
			}
		}
	}

	void EffectManagerComponent::PlayHitEffect(const Vector2Df& origin)
	{
		if (emitter == nullptr)
		{
			emitter = gameObject->GetComponent<ParticleEmitterComponent>();
			return;
		}
		emitter->EmitBurst(hitParams, origin);
	}

	void EffectManagerComponent::PlayPositiveEffect(const Vector2Df& origin)
	{
		if (emitter == nullptr)
		{
			return;
		}
		emitter->EmitBurst(positiveParams, origin);
	}

	void EffectManagerComponent::PlayDustEffect(const Vector2Df& origin)
	{
		if (emitter == nullptr || dustSpeedThreshold <= 0.f || transform == nullptr)
		{
			return;
		}

		
        emitter->EmitBurst(dustParams, origin);
	}

	void EffectManagerComponent::Render()
	{
		if (auraPulseTimer > 0.f && auraSettings.pulseDuration > 0.f && transform != nullptr)
		{
			float t = 1.f - (auraPulseTimer / auraSettings.pulseDuration);
			// Линейный рост радиуса и затухание альфы
			float radius = auraSettings.minRadius + t * (auraSettings.maxRadius - auraSettings.minRadius);
			float alpha = static_cast<float>(auraSettings.maxAlpha) - t * (static_cast<float>(auraSettings.maxAlpha) - static_cast<float>(auraSettings.minAlpha));

			auraCircle.setRadius(radius);
			auraCircle.setOrigin(radius, radius);
			auraCircle.setPosition(transform->GetWorldPosition().x, transform->GetWorldPosition().y);
			sf::Color c = auraSettings.color;
			c.a = static_cast<sf::Uint8>(alpha);
			auraCircle.setFillColor(c);
			RenderSystem::Instance()->Render(auraCircle);
		}
	}
}


