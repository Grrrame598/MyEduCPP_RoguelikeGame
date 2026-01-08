#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace XYZEngine
{
	class ResourceSystem
	{
	public:
		static ResourceSystem* Instance();

		void LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth = true);
		std::shared_ptr<sf::Texture> GetTextureShared(const std::string& name) const;
		std::shared_ptr<sf::Texture> GetTextureCopy(const std::string& name) const;
		void DeleteSharedTexture(const std::string& name);

		void LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize, int totalElements, bool isSmooth = true);
		std::shared_ptr<sf::Texture> GetTextureMapElementShared(const std::string& name, int elementIndex) const;
		std::shared_ptr<sf::Texture> GetTextureMapElementCopy(const std::string& name, int elementIndex) const;
		int GetTextureMapElementsCount(const std::string& name) const;
		void DeleteSharedTextureMap(const std::string& name);

		// Управление звуками (для коротких звуков - sf::SoundBuffer)
		void LoadSoundBuffer(const std::string& name, std::string sourcePath);
		std::shared_ptr<sf::SoundBuffer> GetSoundBufferShared(const std::string& name) const;
		std::shared_ptr<sf::SoundBuffer> GetSoundBufferCopy(const std::string& name) const;
		void DeleteSharedSoundBuffer(const std::string& name);

		// Управление музыкой (для фоновой музыки - sf::Music)
		void LoadMusic(const std::string& name, std::string sourcePath);
		std::shared_ptr<sf::Music> GetMusic(const std::string& name) const;
		void DeleteMusic(const std::string& name);

		void Clear();

	private:
		std::map<std::string, std::shared_ptr<sf::Texture>> textures;
		std::map<std::string, std::vector<std::shared_ptr<sf::Texture>>> textureMaps;
		std::map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers;
		std::map<std::string, std::shared_ptr<sf::Music>> musics;

		ResourceSystem() {}
		~ResourceSystem() {}

		ResourceSystem(ResourceSystem const&) = delete;
		ResourceSystem& operator= (ResourceSystem const&) = delete;

		void DeleteAllTextures();
		void DeleteAllTextureMaps();
		void DeleteAllSoundBuffers();
		void DeleteAllMusics();
	};
}