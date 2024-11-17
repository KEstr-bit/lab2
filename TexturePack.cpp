#include "TexturePack.h"

TexturePack::TexturePack(){

    int countText = COUNT_TEXTURE;
    sf::Texture texture;

    for (int i = 0; i < countText; i++) {
        std::string path = "image";
        path += std::to_string(i);
        path += ".png";

        if (!texture.loadFromFile(path))
            throw std::exception("Не удалось загрузить текстуры");

        textures.emplace_back(texture);
    }
}

TexturePack::TexturePack(int a)
{
    int countText = COUNT_TEXTURE;
    sf::Texture texture;
    for (int i = 0; i < countText; i++)
        textures.emplace_back(texture);
}

sf::Texture* TexturePack::getTexture(textureType type)
{
	return &textures.at(type);
}
