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

	LOG_INFO("Logger initialized");
}

int main()
{
	SetupLogger();
	LOG_INFO("Starting game");

	try
	{
		XYZEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "XYZRoguelike"));

		auto resourceSystem = XYZEngine::ResourceSystem::Instance();

		resourceSystem->LoadTexture("ball", "Resources/Textures/ball.png");
		resourceSystem->LoadTexture("platform", "Resources/Textures/platform.png");
		resourceSystem->LoadTexture("floor", "Resources/Textures/floor.png", false); // floor без сглаживания, чтобы не было швов
		LOG_INFO("Textures ball, platform, floor loaded");

		resourceSystem->LoadMusic("bgm_main", "Resources/Music/Clinthammer__Background_Music.wav");
		if (auto music = resourceSystem->GetMusic("bgm_main"))
		{
			music->setLoop(true);
			music->play();
			LOG_INFO("Background music bgm_main started in loop");
		}
		else
		{
			LOG_WARN("Failed to load background music bgm_main");
		}

		auto developerLevel = std::make_shared<DeveloperLevel>();
		developerLevel->Start();
		LOG_INFO("DeveloperLevel started");

		XYZEngine::Engine::Instance()->Run();
		LOG_INFO("Engine shutdown");
		return 0;
	}
	catch (const std::exception& ex)
	{
		LOG_ERROR(std::string("Critical initialization error: ") + ex.what());
		return 1;
	}
}
