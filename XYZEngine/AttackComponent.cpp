#include "pch.h"
#include "AttackComponent.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include "ParticleEmitterComponent.h"
#include "EffectManagerComponent.h"

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
			LOG_INFO("Attack: " + gameObject->GetName() + " -> " + target->GetName() + " for " + std::to_string(dealt));
			timer = cooldown;

			// Триггерим шейк камеры у атакующего и цели (если камеры есть)
			if (auto selfCamera = gameObject->GetComponent<CameraComponent>())
			{
				selfCamera->TriggerShake();
			}
			if (auto targetCamera = target->GetComponent<CameraComponent>())
			{
				targetCamera->TriggerShake();
			}

			// Эффект частиц удара (красные) у цели, если есть менеджер эффектов
			if (auto targetEffects = target->GetComponent<EffectManagerComponent>())
			{
				targetEffects->PlayHitEffect(targetPos);
			}

			// Положительный эффект (демо) у атакующего — зелёные частицы
			if (auto selfEffects = gameObject->GetComponent<EffectManagerComponent>())
			{
				selfEffects->PlayPositiveEffect(selfTransform->GetWorldPosition());
			}
		}
	}
}
