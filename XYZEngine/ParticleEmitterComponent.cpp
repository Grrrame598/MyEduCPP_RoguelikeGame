#include "pch.h"
#include "ParticleEmitterComponent.h"
#include "TransformComponent.h"

namespace XYZEngine
{
	ParticleEmitterComponent::ParticleEmitterComponent(GameObject* gameObject)
		: Component(gameObject), rng(std::random_device{}())
	{
		shape.setPointCount(8);
		shape.setOrigin({ 0.5f, 0.5f });
	}

	void ParticleEmitterComponent::EmitBurst(const ParticleParams& params, const Vector2Df& origin)
	{
		std::uniform_real_distribution<float> angleDist(0.f, 2.f * 3.1415926535f);
		std::uniform_real_distribution<float> speedDist(params.minSpeed, params.maxSpeed);
		std::uniform_real_distribution<float> lifeDist(params.minLife, params.maxLife);
		std::uniform_real_distribution<float> sizeDist(params.minSize, params.maxSize);

		for (int i = 0; i < params.count; ++i)
		{
			float angle = angleDist(rng);
			float speed = speedDist(rng);

			Particle p;
			p.position = { origin.x, origin.y };
			p.velocity = { std::cos(angle) * speed, std::sin(angle) * speed };
			p.life = lifeDist(rng);
			p.size = sizeDist(rng);
			p.color = params.color;
			particles.push_back(p);
		}
	}

	void ParticleEmitterComponent::Update(float deltaTime)
	{
		for (auto& p : particles)
		{
			p.life -= deltaTime;
			if (p.life <= 0.f)
			{
				continue;
			}
			p.position += p.velocity * deltaTime;
		}

		particles.erase(std::remove_if(particles.begin(), particles.end(), [](const Particle& p) { return p.life <= 0.f; }), particles.end());
	}

	void ParticleEmitterComponent::Render()
	{
		for (const auto& p : particles)
		{
			if (p.life <= 0.f)
			{
				continue;
			}
			shape.setRadius(p.size * 0.5f);
			shape.setFillColor(p.color);
			shape.setPosition(p.position);
			RenderSystem::Instance()->Render(shape);
		}
	}
}


