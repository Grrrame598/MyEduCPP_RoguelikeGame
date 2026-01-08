#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <HealthComponent.h>
#include <Logger.h>
#include <cassert>

namespace XYZRoguelike
{
	Player::Player()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player");
		auto playerRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		if (auto tex = XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"))
		{
			playerRenderer->SetTexture(*tex);
			playerRenderer->SetPixelSize(32, 32);
		}
		else
		{
			LOG_ERROR("Не удалось установить текстуру игрока: ball");
			assert(false && "Texture 'ball' is required for Player");
			return;
		}

		auto playerCamera = gameObject->AddComponent<XYZEngine::CameraComponent>();
		playerCamera->SetWindow(&XYZEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto health = gameObject->AddComponent<XYZEngine::HealthComponent>();
		health->SetMaxHealth(100.f);
		health->SetHealth(100.f);
		health->SetArmor(20.f);
	}

	XYZEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}