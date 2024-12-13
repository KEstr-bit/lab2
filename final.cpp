#include <iostream>
#include "Final.h"

#include "Drawer.h"


Final::Final()
{
    font.loadFromFile("ComicSansMS.ttf");
    endingOption = WIN_GAME;
}


void Final::displayMessage(sf::RenderWindow& window, const std::string& message, const sf::Color color) const
{
    //созданеие текстового блока
    sf::Text text(message, font, 70);
    text.setFillColor(color);
    const sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(Drawer::SCREEN_WIDTH / 2.0f, Drawer::SCREEN_HEIGHT / 2.0f);

    //вывод
    window.draw(text);
}

void Final::outputFinal(sf::RenderWindow& window) const
{
    switch (endingOption)
    {
    case LOOSE_GAME:
        displayMessage(window, "YOU LOOSE!!!", sf::Color::Red);
        break;
    case WIN_GAME:
        displayMessage(window, "You Win!", sf::Color::White);
        break;
    }
    
}


