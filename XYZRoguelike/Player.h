#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "AttackComponent.h"

namespace XYZRoguelike
{
	class Player
	{
	public:
		Player();
		XYZEngine::GameObject* GetGameObject();
		void SetAttackTarget(XYZEngine::GameObject* target);
	private:
		XYZEngine::GameObject* gameObject;
		XYZEngine::AttackComponent* attack = nullptr;
	};
}