#pragma once
#include "helper.h"

class final
{
private:
    EndingOption gameEndType;       //Парамтр окончания игры
    char winMessage[10];            //Сообщение при победе
    char looseMessage[10];          //Сообщение при проигрыше

public:
    final(EndingOption option, char win_mes[10], char loose_mes[10]);
    final();
    ~final();
    //Изменить параметр окончания
    int changeType(EndingOption option);
    //Вывести сообщение об завершении игры
    int vivodFinal();

};