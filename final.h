#pragma once
#include <SFML/Graphics.hpp>
#include "helper.h"

class final
{
private:
    EndingOption gameEndType;       //Парамтр окончания игры

public:
    final();
    ~final();
    //Вывести сообщение об завершении игры
    void outputFinal(sf::RenderWindow& window);
    //Изменить параметр окончания
    void changeFinal(EndingOption);
private:
    void displayMessage(sf::RenderWindow& window, const std::string& message, sf::Color color);
};