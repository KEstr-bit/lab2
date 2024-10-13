#include "helper.h"
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

int roundd(double number)
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