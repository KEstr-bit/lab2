#include "Helper.h"
#include <iostream>
#include <windows.h>

void Helper::setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

char* Helper::strcopy(char* _Destination, const char* _Source)
{
    char* temp = _Destination;
    if(_Destination != NULL && _Source != NULL)
        while (*_Destination++ = *_Source++); 
    return temp;
};

int Helper::myRound(double number)
{
    if (number > 0) 
    {
        return static_cast<int>(number + 0.5);
    }
    else 
    {
        return static_cast<int>(number - 0.5);
    }

};

int Helper::myAbs(int number)
{
    if (number > 0) 
    {
        return number;
    }
    else
    {
        return number * (-1);
    }
};

double Helper::myAbs(double number)
{
    if (number > 0)
    {
        return number;
    }
    else
    {
        return number * (-1);
    }
};


double Helper::calcDistance(double first_X, double first_Y, double second_X, double second_Y) {
    return sqrt((first_X - second_X) * (first_X - second_X) + (first_Y - second_Y) * (first_Y - second_Y));
};

double Helper::degToRad(double deg)
{
    return deg * 3.14 / 180;
}

double Helper::radToDeg(double rad)
{
    return rad * 180 / 3.14;
}

double Helper::projectionToX(double len, double rad_Angle)
{
    return len * cos(rad_Angle);
}

double Helper::projectionToY(double len, double rad_Angle)
{
    return len * sin(rad_Angle);
}

double Helper::interpolateCoord(double startCoord, double finalCoord, double step, double distance)
{
    return (step * finalCoord + (distance - step) * startCoord) / distance;
}

double Helper::getRotAngle(double playerAngle, double cosPlEnLine, double sinPlEnLine) {
    double cosRotAngle = cos(Helper::degToRad(playerAngle)) * cosPlEnLine + sin(Helper::degToRad(playerAngle)) * sinPlEnLine;
    double sinRotAngle = sin(Helper::degToRad(playerAngle)) * cosPlEnLine - cos(Helper::degToRad(playerAngle)) * sinPlEnLine;

    if (cosRotAngle > 1)
        cosRotAngle = 1;

    if (cosRotAngle < -1)
        cosRotAngle = -1;

    //угол на который игроку нужно повернуться, чтобы смотреть ровно на объект
    double rotAngle = Helper::radToDeg(acos(cosRotAngle));

    if (sinRotAngle < 0)
        rotAngle *= -1;

    //если объект находится за обзором игрока
    rotAngle = round(rotAngle * 1000) / 1000.0;
    return rotAngle;
}