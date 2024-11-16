#pragma once
#include <SFML/Graphics.hpp>
#include "helper.h"

class final
{
private:
    EndingOption gameEndType;       //������� ��������� ����

public:
    final();
    ~final();
    //������� ��������� �� ���������� ����
    void outputFinal(sf::RenderWindow& window);
    //�������� �������� ���������
    void changeFinal(EndingOption);
private:
    void displayMessage(sf::RenderWindow& window, const std::string& message, sf::Color color);
};