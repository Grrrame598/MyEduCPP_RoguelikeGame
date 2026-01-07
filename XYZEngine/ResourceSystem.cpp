#include "pch.h"
#include "ResourceSystem.h"

namespace XYZEngine
{
	ResourceSystem* ResourceSystem::Instance()
	{
		static ResourceSystem resourceSystem;
		return &resourceSystem;
	}

	void ResourceSystem::LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth)
	{
		if (textures.find(name) != textures.end())
		{
			return;
		}

		sf::Texture* newTexture = new sf::Texture();
		if (newTexture->loadFromFile(sourcePath))
		{
			newTexture->setSmooth(isSmooth);
			textures.emplace(name, newTexture);
		}
	}
	const sf::Texture* ResourceSystem::GetTextureShared(const std::string& name) const
	{
		return textures.find(name)->second;
	}
	sf::Texture* ResourceSystem::GetTextureCopy(const std::string& name) const
	{
		return new sf::Texture(*textures.find(name)->second);
	}
	void ResourceSystem::DeleteSharedTexture(const std::string& name)
	{
		auto texturePair = textures.find(name);

		sf::Texture* deletingTexure = texturePair->second;
		textures.erase(texturePair);
		delete deletingTexure;
	}

	void ResourceSystem::LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize, int totalElements, bool isSmooth)
	{
		if (textureMaps.find(name) != textureMaps.end())
		{
			return;
		}

		sf::Texture textureMap;
		if (textureMap.loadFromFile(sourcePath))
		{
			auto textureMapElements = new std::vector<sf::Texture*>();

			auto textureSize = textureMap.getSize();
			int loadedElements = 0;

			for (int y = 0; y <= textureSize.y - elementPixelSize.y; y += elementPixelSize.y)
			{
				if (loadedElements == totalElements)
				{
					break;
				}

				for (int x = 0; x <= textureSize.x - elementPixelSize.x; x += elementPixelSize.x)
				{
					if (loadedElements == totalElements)
					{
						break;
					}

					sf::Texture* newTextureMapElement = new sf::Texture();
					if (newTextureMapElement->loadFromFile(sourcePath, sf::IntRect(x, y, elementPixelSize.x, elementPixelSize.y)))
					{
						newTextureMapElement->setSmooth(isSmooth);
						textureMapElements->push_back(newTextureMapElement);
					}
					loadedElements++;
				}
			}

			textureMaps.emplace(name, *textureMapElements);
		}
	}
	const sf::Texture* ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return textures[elementIndex];
	}
	sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return new sf::Texture(*textures[elementIndex]);
	}
	int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return textures.size();
	}
	void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
	{
		auto textureMap = textureMaps.find(name);
		auto deletingTextures = textureMap->second;

		for (int i = 0; i < deletingTextures.size(); i++)
		{
			delete deletingTextures[i];
		}

		textureMaps.erase(textureMap);
	}

	// Реализация методов для работы со звуками (SoundBuffer)
	void ResourceSystem::LoadSoundBuffer(const std::string& name, std::string sourcePath)
	{
		if (soundBuffers.find(name) != soundBuffers.end())
		{
			return;
		}

		sf::SoundBuffer* newSoundBuffer = new sf::SoundBuffer();
		if (newSoundBuffer->loadFromFile(sourcePath))
		{
			soundBuffers.emplace(name, newSoundBuffer);
		}
	}

	const sf::SoundBuffer* ResourceSystem::GetSoundBufferShared(const std::string& name) const
	{
		return soundBuffers.find(name)->second;
	}

	sf::SoundBuffer* ResourceSystem::GetSoundBufferCopy(const std::string& name) const
	{
		return new sf::SoundBuffer(*soundBuffers.find(name)->second);
	}

	void ResourceSystem::DeleteSharedSoundBuffer(const std::string& name)
	{
		auto soundBufferPair = soundBuffers.find(name);

		sf::SoundBuffer* deletingSoundBuffer = soundBufferPair->second;
		soundBuffers.erase(soundBufferPair);
		delete deletingSoundBuffer;
	}

	// Реализация методов для работы с музыкой (Music)
	void ResourceSystem::LoadMusic(const std::string& name, std::string sourcePath)
	{
		if (musics.find(name) != musics.end())
		{
			return;
		}

		sf::Music* newMusic = new sf::Music();
		if (newMusic->openFromFile(sourcePath))
		{
			musics.emplace(name, newMusic);
		}
	}

	sf::Music* ResourceSystem::GetMusic(const std::string& name) const
	{
		return musics.find(name)->second;
	}

	void ResourceSystem::DeleteMusic(const std::string& name)
	{
		auto musicPair = musics.find(name);

		sf::Music* deletingMusic = musicPair->second;
		musics.erase(musicPair);
		delete deletingMusic;
	}

	void ResourceSystem::Clear()
	{
		DeleteAllTextures();
		DeleteAllTextureMaps();
		DeleteAllSoundBuffers();
		DeleteAllMusics();
	}

	void ResourceSystem::DeleteAllTextures()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& texturePair : textures)
		{
			keysToDelete.push_back(texturePair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTexture(key);
		}
	}
	void ResourceSystem::DeleteAllTextureMaps()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& textureMapPair : textureMaps)
		{
			keysToDelete.push_back(textureMapPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTextureMap(key);
		}
	}

	void ResourceSystem::DeleteAllSoundBuffers()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& soundBufferPair : soundBuffers)
		{
			keysToDelete.push_back(soundBufferPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedSoundBuffer(key);
		}
	}

	void ResourceSystem::DeleteAllMusics()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& musicPair : musics)
		{
			keysToDelete.push_back(musicPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteMusic(key);
		}
	}
}