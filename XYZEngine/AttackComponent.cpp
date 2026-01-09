#include "pch.h"
#include "AttackComponent.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include "ParticleEmitterComponent.h"

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

			// Эффект частиц удара (красные) у цели, если есть эмиттер
			if (auto targetEmitter = target->GetComponent<ParticleEmitterComponent>())
			{
				ParticleParams hitParams;
				hitParams.count = 16;
				hitParams.minSpeed = 120.f;
				hitParams.maxSpeed = 220.f;
				hitParams.minLife = 0.25f;
				hitParams.maxLife = 0.45f;
				hitParams.minSize = 3.f;
				hitParams.maxSize = 6.f;
				hitParams.color = sf::Color(220, 60, 60);

				targetEmitter->EmitBurst(hitParams, targetPos);
			}

			// Положительный эффект (демо) у атакующего — зелёные частицы, чтобы показать вариативность параметров
			if (auto selfEmitter = gameObject->GetComponent<ParticleEmitterComponent>())
			{
				ParticleParams healParams;
				healParams.count = 14;
				healParams.minSpeed = 80.f;
				healParams.maxSpeed = 160.f;
				healParams.minLife = 0.35f;
				healParams.maxLife = 0.6f;
				healParams.minSize = 3.f;
				healParams.maxSize = 6.f;
				healParams.color = sf::Color(90, 200, 120);

				// Эмитируем возле атакующего, чтобы видеть вторую палитру
				Vector2Df selfPos = selfTransform->GetWorldPosition();
				selfEmitter->EmitBurst(healParams, selfPos);
			}
		}
	}
}

