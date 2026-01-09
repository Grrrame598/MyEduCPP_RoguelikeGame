#pragma once

// Группируем основные константы баланса/сцены, чтобы избежать "магических чисел".
// Комментарии на русском: что за группа и как используется в коде.

namespace XYZRoguelike::Config
{
	// Параметры игрока: здоровье, броня, атака, размер спрайта.
	namespace Player
	{
		constexpr float MaxHealth = 100.f;
		constexpr float StartHealth = 100.f;
		constexpr float Armor = 5.f;

		constexpr float AttackDamage = 15.f;
		constexpr float AttackRange = 48.f;
		constexpr float AttackCooldown = 0.8f; // секунды

		constexpr int SpriteWidth = 32;
		constexpr int SpriteHeight = 32;
	}

	// Параметры камеры игрока: базовое разрешение.
	namespace Camera
	{
		constexpr unsigned int BaseWidth = 1280;
		constexpr unsigned int BaseHeight = 720;
	}

	// Параметры шейка камеры (легкий уровень Graphics)
	namespace CameraShake
	{
		constexpr float Amplitude = 12.f;      // пиксели смещения
		constexpr float Duration = 0.25f;      // секунды
		constexpr float Frequency = 32.f;      // герц (циклов в секунду)
	}

	// Параметры врага: преследование и начальная позиция.
	namespace Enemy
	{
		// ТТХ врага
		constexpr float MaxHealth = 80.f;
		constexpr float StartHealth = 80.f;
		constexpr float Armor = 10.f;

		constexpr float AttackDamage = 10.f;
		constexpr float AttackRange = 48.f;
		constexpr float AttackCooldown = 1.0f; // секунды

		// Текстура/спрайт
		constexpr int SpriteWidth = 64;
		constexpr int SpriteHeight = 16;

		// Преследование
		constexpr float DetectionRadius = 800.f;
		constexpr float ChaseSpeed = 120.f;     // единиц в секунду
		constexpr float StopDistance = 32.f;    // дистанция остановки

		constexpr float SpawnOffsetX = -300.f;
		constexpr float SpawnOffsetY = -180.f;
	}

	// Параметры стен периметра: размеры области и сегментов.
	namespace Walls
	{
		constexpr float HalfWidth = 512.f;
		constexpr float HalfHeight = 360.f;
		constexpr float Thickness = 24.f;
		constexpr float SegmentLength = 48.f;
	}

	// Параметры пола
	namespace Floor
	{
		constexpr char TextureName[] = "floor";
		constexpr float TileSize = Walls::SegmentLength; // квадратный тайл по шагу стен
	}
}

