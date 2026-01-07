#pragma once
#include <memory>
#include <GameObject.h>
#include <SpriteRendererComponent.h>
#include <SpriteColliderComponent.h>
#include <RigidbodyComponent.h>
#include <TransformComponent.h>
#include <ResourceSystem.h>

namespace XYZRoguelike
{
	class Wall
	{
	public:
		Wall(float widthPixels = 64.f, float heightPixels = 16.f);

		XYZEngine::GameObject* GetGameObject();

		void SetPosition(float x, float y);
		void SetSize(float widthPixels, float heightPixels);

	private:
		XYZEngine::GameObject* gameObject = nullptr;
		XYZEngine::SpriteRendererComponent* renderer = nullptr;
	};
}

