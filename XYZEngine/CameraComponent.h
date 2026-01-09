#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "TransformComponent.h"
#include <cmath>

namespace XYZEngine
{
	class CameraComponent : public Component
	{
	public:
		CameraComponent(GameObject* gameObject);
		~CameraComponent();

		void Update(float deltaTime) override;
		void Render() override;

		void SetWindow(sf::RenderWindow* newWindow);
		void ZoomBy(float newZoom);

		void SetBaseResolution(int width, int height);

		// Настройка и запуск шейка камеры (без параметров — используем сохранённые значения).
		void SetShakeParams(float amplitude, float duration, float frequency);
		void TriggerShake();

	private:
		TransformComponent* transform;
		sf::RenderWindow* window;
		sf::View* view;

		// Состояние шейка
		float shakeAmplitude = 0.f;
		float shakeDuration = 0.f;
		float shakeFrequency = 0.f;
		float shakeTimer = 0.f;
		float shakePhase = 0.f;
	};
}