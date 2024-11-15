#include "TexturePack.h"


void TexturePack::addTexture(sf::Texture texture)
{
	textures.emplace_back(texture);
}

sf::Texture* TexturePack::getTexture(textureType type)
{
	return &textures.at(type);
}