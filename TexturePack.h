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
	//вектор текстур
	std::vector<sf::Texture> textures;
public:
	//загрузить текстуру
	void addTexture(sf::Texture);
	//получить указатель на текстуру
	sf::Texture* getTexture(textureType type);
};