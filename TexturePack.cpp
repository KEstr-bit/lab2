#include "TexturePack.h"

TexturePack::TexturePack(){

    sf::Texture texture;
    for (int i = 0; i < COUNT_TEXTURES; i++) {
        std::string path = "image";
        path += std::to_string(i);
        path += ".png";

        if (!texture.loadFromFile(path))
            throw std::exception("Не удалось загрузить текстуры");

        textures.emplace_back(texture);
    }
}

TexturePack::TexturePack(int)
{
    sf::Texture texture;
    for (int i = 0; i < COUNT_TEXTURES; i++)
        textures.emplace_back(texture);
}


sf::Texture* TexturePack::getTexture(const TextureType type)
{
	return &textures.at(type);
}
