#pragma once

#include "Component.h"
#include "RigidbodyComponent.h"
#include "EffectManagerComponent.h"
#include "Vector.h"
#include <SFML/Window.hpp>

namespace XYZEngine
{
	class InputComponent : public Component
	{
	public:
		InputComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		float GetHorizontalAxis() const;
		float GetVerticalAxis() const;

		void SetMove(RigidbodyComponent* body, float speed);
		void SetEffects(EffectManagerComponent* effects);
	private:
		float horizontalAxis = 0.f;
		float verticalAxis = 0.f;

		RigidbodyComponent* rb = nullptr;
		float moveSpeed = 0.f;
		EffectManagerComponent* fx = nullptr;
	};
}