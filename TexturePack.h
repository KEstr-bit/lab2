#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum TextureType
{
	ENEMY,
	BULLET,
	WALLS,
	NECROMANCER,
	SHOTGUN,
	RIFLE,
	COUNT_TEXTURES
};

class TexturePack
{
private:
	std::vector<sf::Texture> textures;
public:
	static constexpr int FRAMES_COUNT = 8;
	explicit TexturePack(int);
	TexturePack();
	//получить указатель на текстуру
	sf::Texture* getTexture(TextureType type);
};