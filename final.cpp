#include <iostream>
#include "Final.h"

#include "Drawer.h"


Final::Final()
{
    font.loadFromFile("ComicSansMS.ttf");
    gameEndType = WinGame;
}

Final::~Final()
{
}

void Final::displayMessage(sf::RenderWindow& window, const std::string& message, sf::Color color) {
    //созданеие текстового блока
    sf::Text text(message, font, 70);
    text.setFillColor(color);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(Drawer::SCREEN_WIDTH / 2.0f, Drawer::SCREEN_HEIGHT / 2.0f);

    //вывод
    window.draw(text);
}

void Final::outputFinal(sf::RenderWindow& window)
{
    switch (gameEndType)
    {
    case LooseGame:
        displayMessage(window, "YOU LOOSE!!!", sf::Color::Red);
        break;
    case WinGame:
        displayMessage(window, "You Win!", sf::Color::White);
        break;
    default:
        break;
    }
    
}


