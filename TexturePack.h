#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum textureType
{
	Enemy1,
	Bullet1,
	WALL1,
	NEGROMANT,
	SHOTGUN,
	AVT,
	COUNT_TEXTURE
};

class TexturePack
{
private:
	//вектор текстур
	std::vector<sf::Texture> textures;
public:
	static const int FRAMES_COUNT = 8;
	TexturePack();
	TexturePack(int a);
	//получить указатель на текстуру
	sf::Texture* getTexture(textureType type);
};