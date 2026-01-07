#include "pch.h"
#include "PlayerChaseComponent.h"
#include "GameObject.h"
#include <cmath>

namespace XYZEngine
{
	PlayerChaseComponent::PlayerChaseComponent(GameObject* gameObject) : Component(gameObject)
	{
		transform = gameObject->GetComponent<TransformComponent>();
		body = gameObject->GetComponent<RigidbodyComponent>();
	}

	void PlayerChaseComponent::Update(float deltaTime)
	{
		if (body == nullptr || transform == nullptr)
		{
			return;
		}

		if (target == nullptr)
		{
			body->SetLinearVelocity({ 0.f, 0.f });
			return;
		}

		auto playerTransform = target->GetComponent<TransformComponent>();
		if (playerTransform == nullptr)
		{
			body->SetLinearVelocity({ 0.f, 0.f });
			return;
		}

		Vector2Df enemyPos = transform->GetWorldPosition();
		Vector2Df playerPos = playerTransform->GetWorldPosition();

		Vector2Df dir = { playerPos.x - enemyPos.x, playerPos.y - enemyPos.y };
		float distance = dir.GetLength();

		if (distance <= stopDistance || distance > detectionRadius)
		{
			body->SetLinearVelocity({ 0.f, 0.f });
			return;
		}

		Vector2Df dirNorm = { dir.x / distance, dir.y / distance };
		Vector2Df velocity = { dirNorm.x * speed, dirNorm.y * speed };

		body->SetLinearVelocity(velocity);
	}

	void PlayerChaseComponent::Render()
	{
	}

	void PlayerChaseComponent::SetTarget(GameObject* playerGameObject)
	{
		target = playerGameObject;
	}

	void PlayerChaseComponent::SetDetectionRadius(float newRadius)
	{
		detectionRadius = newRadius;
	}

	void PlayerChaseComponent::SetSpeed(float newSpeed)
	{
		speed = newSpeed;
	}

	void PlayerChaseComponent::SetStopDistance(float newStopDistance)
	{
		stopDistance = newStopDistance;
	}
}

