#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum textureType
{
	Enemy1,
	Bullet1,
	WALL1,
	COUNT_TEXTURE
};

class TexturePack
{
private:
	//вектор текстур
	std::vector<sf::Texture> textures;
public:
	TexturePack();
	TexturePack(int a);
	//получить указатель на текстуру
	sf::Texture* getTexture(textureType type);
};