#include "pch.h"
#include "InputComponent.h"

namespace XYZEngine
{
	InputComponent::InputComponent(GameObject* gameObject) : Component(gameObject) {}

	void InputComponent::Update(float deltaTime)
	{
		verticalAxis = 0.f;
		horizontalAxis = 0.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			verticalAxis += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			verticalAxis -= 1.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			horizontalAxis += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			horizontalAxis -= 1.0f;
		}

		if (rb != nullptr && moveSpeed > 0.f)
		{
			Vector2Df move = { horizontalAxis, verticalAxis };
			float len = move.GetLength();
			if (len > 0.f)
			{
				Vector2Df dir = { move.x / len, move.y / len };
				Vector2Df vel = { dir.x * moveSpeed, dir.y * moveSpeed };
				rb->SetLinearVelocity(vel);

				// Пыль при движении игрока (если задан эффектор)
				if (fx != nullptr && len * moveSpeed > 15.f)
				{
					if (auto tr = gameObject->GetComponent<TransformComponent>())
					{
						fx->PlayDustEffect(tr->GetWorldPosition());
					}
				}
			}
			else
			{
				rb->SetLinearVelocity({ 0.f, 0.f });
			}
		}
	}

	void InputComponent::Render()
	{
	}

	void InputComponent::SetMove(RigidbodyComponent* body, float speed)
	{
		rb = body;
		moveSpeed = speed;
	}

	void InputComponent::SetEffects(EffectManagerComponent* effects)
	{
		fx = effects;
	}

	float InputComponent::GetHorizontalAxis() const
	{
		return horizontalAxis;
	}
	float InputComponent::GetVerticalAxis() const
	{
		return verticalAxis;
	}
}