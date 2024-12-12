#pragma once
#include <SFML/Graphics.hpp>
#include "Helper.h"

class Final
{
private:
    sf::Font font;
    EndingOption gameEndType;       //Парамтр окончания игры

public:
    Final();
    ~Final();
    //Вывести сообщение об завершении игры
    void outputFinal(sf::RenderWindow& window);
    //Изменить параметр окончания
    friend void change_final(EndingOption, Final*);
private:
    void displayMessage(sf::RenderWindow& window, const std::string& message, sf::Color color);
};