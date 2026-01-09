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
		constexpr float MoveSpeed = 110.f;

		constexpr float AttackDamage = 15.f;
		constexpr float AttackRange = 80.f;
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
		constexpr float AttackRange = 80.f;
		constexpr float AttackCooldown = 1.0f; // секунды

		// Текстура/спрайт
		constexpr int SpriteWidth = 64;
		constexpr int SpriteHeight = 16;

		// Преследование
		constexpr float DetectionRadius = 300.f;
		constexpr float ChaseSpeed = 100.f;     // единиц в секунду
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

	// Параметры частиц (средний уровень Graphics)
	namespace Particles
	{
		// Удар/урон
		namespace Hit
		{
			constexpr int Count = 16;
			constexpr float MinSpeed = 120.f;
			constexpr float MaxSpeed = 220.f;
			constexpr float MinLife = 0.25f;
			constexpr float MaxLife = 0.45f;
			constexpr float MinSize = 3.f;
			constexpr float MaxSize = 6.f;
			constexpr unsigned char ColorR = 220;
			constexpr unsigned char ColorG = 60;
			constexpr unsigned char ColorB = 60;
		}

		// Положительный эффект (heal/buff)
		namespace Heal
		{
			constexpr int Count = 14;
			constexpr float MinSpeed = 80.f;
			constexpr float MaxSpeed = 160.f;
			constexpr float MinLife = 0.35f;
			constexpr float MaxLife = 0.6f;
			constexpr float MinSize = 3.f;
			constexpr float MaxSize = 6.f;
			constexpr unsigned char ColorR = 90;
			constexpr unsigned char ColorG = 200;
			constexpr unsigned char ColorB = 120;
		}
	}

	// Параметры эффектов (сложный уровень Graphics)
	namespace Effects
	{
		// Пыль при движении
		namespace Dust
		{
			constexpr int Count = 10;
			constexpr float MinSpeed = 40.f;
			constexpr float MaxSpeed = 90.f;
			constexpr float MinLife = 0.25f;
			constexpr float MaxLife = 0.4f;
			constexpr float MinSize = 3.f;
			constexpr float MaxSize = 5.f;
			constexpr unsigned char ColorR = 120;  // теплее/контрастнее стен
			constexpr unsigned char ColorG = 140;
			constexpr unsigned char ColorB = 150;
			constexpr float SpeedThreshold = 15.f; // порог скорости для спавна пыли
		}

		// Аура/пульсация (демо бафф): периодический хил + пульсирующий круг
		namespace Aura
		{
			constexpr float Period = 4.f; // секунды
			constexpr float HealAmount = 5.f;
			constexpr float PulseDuration = 1.5f; // длительность одного пульса (сек)
			constexpr float MinRadius = 20.f;
			constexpr float MaxRadius = 50.f;
			constexpr unsigned char ColorR = 90;
			constexpr unsigned char ColorG = 200;
			constexpr unsigned char ColorB = 120;
			constexpr unsigned char MinAlpha = 40;
			constexpr unsigned char MaxAlpha = 120;
		}
	}
}

