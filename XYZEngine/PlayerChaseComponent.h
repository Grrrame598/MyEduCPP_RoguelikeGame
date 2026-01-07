#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "Vector.h"

namespace XYZEngine
{
	// Компонент простого преследования игрока: если цель внутри радиуса, двигаемся к ней
	class PlayerChaseComponent : public Component
	{
	public:
		PlayerChaseComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetTarget(GameObject* playerGameObject);
		void SetDetectionRadius(float newRadius);
		void SetSpeed(float newSpeed);
		void SetStopDistance(float newStopDistance);

	private:
		TransformComponent* transform = nullptr;
		RigidbodyComponent* body = nullptr;
		GameObject* target = nullptr;

		float detectionRadius = 250.f;
		float speed = 120.f;
		float stopDistance = 20.f;
	};
}

