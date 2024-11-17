#include <iostream>
#include "final.h"


final::final()
{
    try {
        font.loadFromFile("ComicSansMS.ttf");
    }
    catch (std::exception) {
    }
    gameEndType = WinGame;
}

final::~final()
{
}

void final::displayMessage(sf::RenderWindow& window, const std::string& message, sf::Color color) {
    //созданеие текстового блока
    sf::Text text(message, font, 70);
    text.setFillColor(color);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    //вывод
    window.draw(text);
}

void final::outputFinal(sf::RenderWindow& window)
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


