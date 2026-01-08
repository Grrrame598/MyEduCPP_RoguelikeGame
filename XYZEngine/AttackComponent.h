#pragma once

#include "Component.h"
#include "Vector.h"
#include "Logger.h"
#include "HealthComponent.h"
#include "TransformComponent.h"
#include <string>

namespace XYZEngine
{
	class AttackComponent : public Component
	{
	public:
		explicit AttackComponent(GameObject* gameObject);

		void Update(float deltaTime) override;

		void SetTarget(GameObject* newTarget) { target = newTarget; }
		void SetDamage(float value) { damage = std::max(0.f, value); }
		void SetCooldown(float value) { cooldown = std::max(0.f, value); }
		void SetRange(float value) { range = std::max(0.f, value); }

	private:
		GameObject* target = nullptr;
		float damage = 10.f;
		float cooldown = 1.f; // seconds
		float range = 48.f;
		float timer = 0.f;
	};
}

