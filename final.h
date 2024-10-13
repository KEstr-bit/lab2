#pragma once
#include "helper.h"

class final
{
private:
    EndingOption gameEndType;       //������� ��������� ����
    char winMessage[10];            //��������� ��� ������
    char looseMessage[10];          //��������� ��� ���������

public:
    final(EndingOption option, char win_mes[10], char loose_mes[10]);
    final();
    ~final();
    //�������� �������� ���������
    int changeType(EndingOption option);
    //������� ��������� �� ���������� ����
    int vivodFinal();

};