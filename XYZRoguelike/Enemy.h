#pragma once

#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "PlayerChaseComponent.h"
#include "GameObject.h"
#include "AttackComponent.h"

namespace XYZRoguelike
{
	class Enemy
	{
	public:
		Enemy();
		XYZEngine::GameObject* GetGameObject();
		void SetChaseTarget(XYZEngine::GameObject* target);
		void SetChaseParams(float detectionRadius, float speed, float stopDistance = 20.f);
		void SetAttackTarget(XYZEngine::GameObject* target);
	private:
		XYZEngine::GameObject* gameObject;
		XYZEngine::PlayerChaseComponent* chase = nullptr;
		XYZEngine::AttackComponent* attack = nullptr;
	};
}

