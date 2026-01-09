#pragma once

#include "Component.h"
#include "Vector.h"
#include "RenderSystem.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

namespace XYZEngine
{
	struct ParticleParams
	{
		int count = 10;
		sf::Color color = sf::Color::White;
		float minSpeed = 50.f;
		float maxSpeed = 150.f;
		float minLife = 0.3f;
		float maxLife = 0.6f;
		float minSize = 3.f;
		float maxSize = 6.f;
	};

	class ParticleEmitterComponent : public Component
	{
	public:
		explicit ParticleEmitterComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void EmitBurst(const ParticleParams& params, const Vector2Df& origin);

	private:
		// Простейший лимит на количество частиц, чтобы избежать безудержного роста вектора при спаме эффектов.
		static constexpr size_t MaxParticles = 200;

		struct Particle
		{
			sf::Vector2f position;
			sf::Vector2f velocity;
			float life = 0.f;
			float size = 1.f;
			sf::Color color;
		};

		std::vector<Particle> particles;
		std::mt19937 rng;
		sf::CircleShape shape;
	};
}


