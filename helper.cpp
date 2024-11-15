#include "helper.h"
#include <iostream>
#include <windows.h>

void setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

char* strcopy(char* _Destination, const char* _Source) 
{
    char* temp = _Destination;
    if(_Destination != NULL && _Source != NULL)
        while (*_Destination++ = *_Source++); 
    return temp;
};

int myRound(double number)
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

int abss(int number)
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

double abss(double number)
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

bool isWall(char* world_Map, int map_Size_X, int coord_X, int coord_Y)
{
    if (*(world_Map + coord_X * map_Size_X + coord_Y) == '#')
        return true;
    else
        return false;
};

double calcDistance(double first_X, double first_Y, double second_X, double second_Y) {
    return sqrt((first_X - second_X) * (first_X - second_X) + (first_Y - second_Y) * (first_Y - second_Y));
};

double degToRad(double deg)
{
    return deg * 3.14 / 180;
}

double radToDeg(double rad)
{
    return rad * 180 / 3.14;
}

double projectionToX(double len, double rad_Angle)
{
    return len * cos(rad_Angle);
}

double projectionToY(double len, double rad_Angle)
{
    return len * sin(rad_Angle);
}

double interpolateCoord(double startCoord, double finalCoord, double step, double distance)
{
    return (step * finalCoord + (distance - step) * startCoord) / distance;
}