#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

namespace XYZEngine
{
	CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
	{
		view = new sf::View(sf::FloatRect(0, 0, 800, -600));
		transform = gameObject->GetComponent<TransformComponent>();
	}
	CameraComponent::~CameraComponent()
	{
		delete view;
	}

	void CameraComponent::Update(float deltaTime)
	{
		auto position = transform->GetWorldPosition();
		auto rotation = transform->GetWorldRotation();

		sf::Vector2f center = Convert<sf::Vector2f, Vector2Df>(position);

		// Применяем шейк, если активен
		if (shakeTimer > 0.f)
		{
			shakeTimer = std::max(0.f, shakeTimer - deltaTime);
			const float twoPi = 6.28318530718f;
			shakePhase += deltaTime * shakeFrequency * twoPi;

			// Смещение камеры: по X — полная амплитуда, по Y — ослаблено (0.6), фаза Y быстрее (1.3),
			// чтобы дрожь выглядела не как идеальный круг, а слегка "раскачанно".
			float offsetX = shakeAmplitude * std::sin(shakePhase);
			float offsetY = shakeAmplitude * 0.6f * std::cos(shakePhase * 1.3f);

			center.x += offsetX;
			center.y += offsetY;

			if (shakeTimer <= 0.f)
			{
				// Сбрасываем фазу, чтобы не накапливать большие значения
				shakePhase = 0.f;
			}
		}

		view->setCenter(center);
		view->setRotation(rotation);

		window->setView(*view);
	}
	void CameraComponent::Render()
	{
		if (window == nullptr)
		{
			std::cout << "NULL window render." << std::endl;
		}
	}

	void CameraComponent::SetBaseResolution(int width, int height)
	{
		view->reset(sf::FloatRect(0, 0, width, -height));
	}
	void CameraComponent::SetWindow(sf::RenderWindow* newWindow)
	{
		window = newWindow;
	}
	void CameraComponent::ZoomBy(float newZoom)
	{
		if (newZoom <= 0)
		{
			std::cout << "Not allowed zoom lesser or equal than zero." << std::endl;
			return;
		}
		view->zoom(newZoom);
	}

	void CameraComponent::SetShakeParams(float amplitude, float duration, float frequency)
	{
		shakeAmplitude = std::max(0.f, amplitude);
		shakeDuration = std::max(0.f, duration);
		shakeFrequency = std::max(0.f, frequency);
	}

	void CameraComponent::TriggerShake()
	{
		if (shakeDuration <= 0.f || shakeAmplitude <= 0.f || shakeFrequency <= 0.f)
		{
			return;
		}

		// При повторном вызове продлеваем эффект на полную длительность
		shakeTimer = shakeDuration;
	}
}