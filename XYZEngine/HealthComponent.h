#pragma once

#include "Component.h"
#include "Logger.h"

namespace XYZEngine
{
	class HealthComponent : public Component
	{
	public:
		explicit HealthComponent(GameObject* gameObject);

		void SetMaxHealth(float value);
		void SetHealth(float value);
		void SetArmor(float value);

		float GetHealth() const { return health; }
		float GetMaxHealth() const { return maxHealth; }
		float GetArmor() const { return armor; }
		bool IsDead() const { return isDead; }

		float ApplyDamage(float damage);

	private:
		float maxHealth = 100.f;
		float health = 100.f;
		float armor = 0.f;
		bool isDead = false;
	};
}

