#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum textureType
{
	Enemy1,
	Bullet1
};

class TexturePack
{
private:
	std::vector<sf::Texture> textures;
public:
	void addTexture(sf::Texture);
	sf::Texture* getTexture(textureType type);
};