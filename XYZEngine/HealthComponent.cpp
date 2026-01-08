#include "pch.h"
#include "HealthComponent.h"

#include <algorithm>

namespace XYZEngine
{
	HealthComponent::HealthComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	void HealthComponent::SetMaxHealth(float value)
	{
		maxHealth = std::max(0.f, value);
		health = std::min(health, maxHealth);
	}

	void HealthComponent::SetHealth(float value)
	{
		health = std::clamp(value, 0.f, maxHealth);
		isDead = (health <= 0.f);
	}

	void HealthComponent::SetArmor(float value)
	{
		armor = std::max(0.f, value);
	}

	float HealthComponent::ApplyDamage(float damage)
	{
		float effectiveDamage = std::max(0.f, damage - armor);
		if (effectiveDamage <= 0.f)
		{
			return 0.f;
		}

		float prevHealth = health;
		health = std::max(0.f, health - effectiveDamage);
		isDead = (health <= 0.f);

		LOG_INFO("Получен урон: " + std::to_string(effectiveDamage) + ", здоровье: " + std::to_string(prevHealth) + " -> " + std::to_string(health));
		return effectiveDamage;
	}
}

