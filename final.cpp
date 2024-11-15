#include <iostream>
#include "final.h"


final::final()
{
    gameEndType = WinGame;
}

final::~final()
{
}

void final::displayMessage(sf::RenderWindow& window, const std::string& message, sf::Color color) {
    sf::Font font;
    if (!font.loadFromFile("ComicSansMS.ttf")) { // Замените "arial.ttf" на путь к вашему шрифту
        //Обработка ошибки - можно вывести сообщение об ошибке или завершить работу программы
        return;
    }

    sf::Text text(message, font, 70);
    text.setFillColor(color);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
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

void final::changeFinal(EndingOption option)
{
    gameEndType = option;
}
