#pragma once
#include <SFML/Graphics.hpp>
#include "helper.h"

class final
{
private:
    sf::Font font;
    EndingOption gameEndType;       //Парамтр окончания игры

public:
    final();
    ~final();
    //Вывести сообщение об завершении игры
    void outputFinal(sf::RenderWindow& window);
    //Изменить параметр окончания
    friend void changeFinal(EndingOption, final*);
private:
    void displayMessage(sf::RenderWindow& window, const std::string& message, sf::Color color);
};