#include "pch.h"
#include "AttackComponent.h"
#include "GameObject.h"

#include <algorithm>

namespace XYZEngine
{
	AttackComponent::AttackComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	void AttackComponent::Update(float deltaTime)
	{
		if (target == nullptr)
		{
			return;
		}

		timer = std::max(0.f, timer - deltaTime);
		if (timer > 0.f)
		{
			return;
		}

		auto selfTransform = gameObject->GetComponent<TransformComponent>();
		auto targetTransform = target->GetComponent<TransformComponent>();
		auto targetHealth = target->GetComponent<HealthComponent>();

		if (selfTransform == nullptr || targetTransform == nullptr || targetHealth == nullptr)
		{
			return;
		}

		Vector2Df selfPos = selfTransform->GetWorldPosition();
		Vector2Df targetPos = targetTransform->GetWorldPosition();

		Vector2Df dir = { targetPos.x - selfPos.x, targetPos.y - selfPos.y };
		float distance = dir.GetLength();

		if (distance > range)
		{
			return;
		}

		float dealt = targetHealth->ApplyDamage(damage);
		if (dealt > 0.f)
		{
			LOG_INFO("Атака: " + gameObject->GetName() + " -> " + target->GetName() + " на " + std::to_string(dealt));
			timer = cooldown;
		}
	}
}

