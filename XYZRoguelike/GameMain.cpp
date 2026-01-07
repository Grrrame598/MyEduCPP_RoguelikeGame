// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "Matrix2D.h"

using namespace XYZRoguelike;

int main()
{
	XYZEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "XYZRoguelike"));

	auto resourceSystem = XYZEngine::ResourceSystem::Instance();

	resourceSystem->LoadTexture("ball", "Resources/Textures/ball.png");
	resourceSystem->LoadTexture("platform", "Resources/Textures/platform.png");

	// Загружаем фоновую музыку и сразу запускаем в цикле
	resourceSystem->LoadMusic("bgm_main", "Resources/Music/Clinthammer__Background_Music.wav");
	if (resourceSystem->GetMusic("bgm_main") != nullptr)
	{
		resourceSystem->GetMusic("bgm_main")->setLoop(true);
		resourceSystem->GetMusic("bgm_main")->play();
	}

	auto developerLevel = std::make_shared<DeveloperLevel>();
	developerLevel->Start();

	XYZEngine::Engine::Instance()->Run();

	return 0;
}
