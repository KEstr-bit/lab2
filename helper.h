#pragma once

constexpr auto K = 0.2;
constexpr auto MAX_BULLETS = 10;

enum EndingOption { WinGame, LooseGame };
enum СardinalDirections { North, East, South, West };

//установка курсора на позицию  x y 
void setcur(int x, int y);

char* strcopy(char* _Destination, const char* _Source);

int roundd(double number);

int abss(int number);
double abss(double number);