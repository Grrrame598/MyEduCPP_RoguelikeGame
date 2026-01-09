#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <HealthComponent.h>
#include <AttackComponent.h>
#include "../Config/GameConfig.h"
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
			playerRenderer->SetPixelSize(Config::Player::SpriteWidth, Config::Player::SpriteHeight);
		}
		else
		{
			LOG_ERROR("Failed to set player texture: ball");
			assert(false && "Texture 'ball' is required for Player");
			return;
		}

		auto playerCamera = gameObject->AddComponent<XYZEngine::CameraComponent>();
		playerCamera->SetWindow(&XYZEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(Config::Camera::BaseWidth, Config::Camera::BaseHeight);
		playerCamera->SetShakeParams(Config::CameraShake::Amplitude, Config::CameraShake::Duration, Config::CameraShake::Frequency);

		auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto health = gameObject->AddComponent<XYZEngine::HealthComponent>();
		health->SetMaxHealth(Config::Player::MaxHealth);
		health->SetHealth(Config::Player::StartHealth);
		health->SetArmor(Config::Player::Armor);

		attack = gameObject->AddComponent<XYZEngine::AttackComponent>();
		attack->SetDamage(Config::Player::AttackDamage);
		attack->SetRange(Config::Player::AttackRange);
		attack->SetCooldown(Config::Player::AttackCooldown);
	}

	void Player::SetAttackTarget(XYZEngine::GameObject* target)
	{
		if (attack != nullptr)
		{
			attack->SetTarget(target);
		}
	}

	XYZEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}