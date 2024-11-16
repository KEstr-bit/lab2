#pragma once

enum EndingOption { WinGame, LooseGame };
enum СardinalDirections { North, East, South, West };
enum WeaponOption {ShotGun, Automat};


//установка курсора на позицию  x y 
void setcur(int x, int y);

char* strcopy(char* _Destination, const char* _Source);

//округление
int myRound(double number);

//модуль
int myAbs(int number);
double myAbs(double number);

//расстояние между двумя точками
double calcDistance(double first_X, double first_Y, double second_X, double second_Y);

//перевод градусов в радианы
double degToRad(double deg);

//перевод радиан в градусы
double radToDeg(double rad);

//проекция вектора на ось
double projectionToX(double len, double rad_Angle);
double projectionToY(double len, double rad_Angle);

//интерполяция координат
double interpolateCoord(double startCoord, double finalCoord, double step, double distance);
