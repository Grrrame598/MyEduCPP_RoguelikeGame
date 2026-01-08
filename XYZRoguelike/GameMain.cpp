// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "Logger.h"
#include "DeveloperLevel.h"
#include "Matrix2D.h"

using namespace XYZRoguelike;

// Настраиваем логирование (консоль + файл)
void SetupLogger()
{
	auto logger = std::make_shared<XYZEngine::Logger>();
	logger->SetMinLevel(XYZEngine::LogLevel::INFO);
	logger->AddSink(std::make_shared<XYZEngine::ConsoleSink>());
	logger->AddSink(std::make_shared<XYZEngine::FileSink>("Logs/game.log"));

	auto& registry = XYZEngine::LoggerRegistry::Instance();
	registry.RegisterLogger("global", logger);
	registry.SetDefaultLogger(logger);

	LOG_INFO("Логгер инициализирован");
}

int main()
{
	SetupLogger();
	LOG_INFO("Запуск игры");

	try
	{
		XYZEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "XYZRoguelike"));

		auto resourceSystem = XYZEngine::ResourceSystem::Instance();

		resourceSystem->LoadTexture("ball", "Resources/Textures/ball.png");
		resourceSystem->LoadTexture("platform", "Resources/Textures/platform.png");
		LOG_INFO("Текстуры ball и platform загружены");

		// Загружаем фоновую музыку и сразу запускаем в цикле
		resourceSystem->LoadMusic("bgm_main", "Resources/Music/Clinthammer__Background_Music.wav");
		if (auto music = resourceSystem->GetMusic("bgm_main"))
		{
			music->setLoop(true);
			music->play();
			LOG_INFO("Фоновая музыка bgm_main запущена в цикле");
		}
		else
		{
			LOG_WARN("Не удалось загрузить фоновую музыку bgm_main");
		}

		auto developerLevel = std::make_shared<DeveloperLevel>();
		developerLevel->Start();
		LOG_INFO("DeveloperLevel запущен");

		XYZEngine::Engine::Instance()->Run();
		LOG_INFO("Завершение работы движка");
		return 0;
	}
	catch (const std::exception& ex)
	{
		LOG_ERROR(std::string("Критическая ошибка при инициализации: ") + ex.what());
		return 1;
	}
}
