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

		auto newTexture = std::make_shared<sf::Texture>();
		if (newTexture->loadFromFile(sourcePath))
		{
			newTexture->setSmooth(isSmooth);
			textures.emplace(name, newTexture);
		}
	}
	std::shared_ptr<sf::Texture> ResourceSystem::GetTextureShared(const std::string& name) const
	{
		auto it = textures.find(name);
		if (it == textures.end())
		{
			return nullptr;
		}
		return it->second;
	}
	std::shared_ptr<sf::Texture> ResourceSystem::GetTextureCopy(const std::string& name) const
	{
		auto it = textures.find(name);
		if (it == textures.end())
		{
			return nullptr;
		}
		return std::make_shared<sf::Texture>(*it->second);
	}
	void ResourceSystem::DeleteSharedTexture(const std::string& name)
	{
		auto texturePair = textures.find(name);
		if (texturePair == textures.end())
		{
			return;
		}
		textures.erase(texturePair);
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
			std::vector<std::shared_ptr<sf::Texture>> textureMapElements;

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

					auto newTextureMapElement = std::make_shared<sf::Texture>();
					if (newTextureMapElement->loadFromFile(sourcePath, sf::IntRect(x, y, elementPixelSize.x, elementPixelSize.y)))
					{
						newTextureMapElement->setSmooth(isSmooth);
						textureMapElements.push_back(newTextureMapElement);
					}
					loadedElements++;
				}
			}

			textureMaps.emplace(name, textureMapElements);
		}
	}
	std::shared_ptr<sf::Texture> ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		if (textureMap == textureMaps.end() || elementIndex < 0 || elementIndex >= static_cast<int>(textureMap->second.size()))
		{
			return nullptr;
		}
		return textureMap->second[elementIndex];
	}
	std::shared_ptr<sf::Texture> ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		if (textureMap == textureMaps.end() || elementIndex < 0 || elementIndex >= static_cast<int>(textureMap->second.size()))
		{
			return nullptr;
		}
		return std::make_shared<sf::Texture>(*textureMap->second[elementIndex]);
	}
	int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
	{
		auto textureMap = textureMaps.find(name);
		if (textureMap == textureMaps.end())
		{
			return 0;
		}
		return textureMap->second.size();
	}
	void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
	{
		auto textureMap = textureMaps.find(name);
		if (textureMap == textureMaps.end())
		{
			return;
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

		auto newSoundBuffer = std::make_shared<sf::SoundBuffer>();
		if (newSoundBuffer->loadFromFile(sourcePath))
		{
			soundBuffers.emplace(name, newSoundBuffer);
		}
	}

	std::shared_ptr<sf::SoundBuffer> ResourceSystem::GetSoundBufferShared(const std::string& name) const
	{
		auto it = soundBuffers.find(name);
		if (it == soundBuffers.end())
		{
			return nullptr;
		}
		return it->second;
	}

	std::shared_ptr<sf::SoundBuffer> ResourceSystem::GetSoundBufferCopy(const std::string& name) const
	{
		auto it = soundBuffers.find(name);
		if (it == soundBuffers.end())
		{
			return nullptr;
		}
		return std::make_shared<sf::SoundBuffer>(*it->second);
	}

	void ResourceSystem::DeleteSharedSoundBuffer(const std::string& name)
	{
		auto soundBufferPair = soundBuffers.find(name);
		if (soundBufferPair == soundBuffers.end())
		{
			return;
		}
		soundBuffers.erase(soundBufferPair);
	}

	// Реализация методов для работы с музыкой (Music)
	void ResourceSystem::LoadMusic(const std::string& name, std::string sourcePath)
	{
		if (musics.find(name) != musics.end())
		{
			return;
		}

		auto newMusic = std::make_shared<sf::Music>();
		if (newMusic->openFromFile(sourcePath))
		{
			musics.emplace(name, newMusic);
		}
	}

	std::shared_ptr<sf::Music> ResourceSystem::GetMusic(const std::string& name) const
	{
		auto it = musics.find(name);
		if (it == musics.end())
		{
			return nullptr;
		}
		return it->second;
	}

	void ResourceSystem::DeleteMusic(const std::string& name)
	{
		auto musicPair = musics.find(name);
		if (musicPair == musics.end())
		{
			return;
		}

		musics.erase(musicPair);
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
		textures.clear();
	}
	void ResourceSystem::DeleteAllTextureMaps()
	{
		textureMaps.clear();
	}

	void ResourceSystem::DeleteAllSoundBuffers()
	{
		soundBuffers.clear();
	}

	void ResourceSystem::DeleteAllMusics()
	{
		musics.clear();
	}
}