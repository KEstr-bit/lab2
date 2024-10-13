#pragma once

constexpr auto K = 0.2;
constexpr auto MAX_BULLETS = 10;

enum EndingOption { WinGame, LooseGame };
enum СardinalDirections { North, East, South, West };
enum WeaponOption {ShotGun, Automat};

//установка курсора на позицию  x y 
void setcur(int x, int y);

char* strcopy(char* _Destination, const char* _Source);

int roundd(double number);

int abss(int number);

double abss(double number);

bool isWall(char* world_Map, int map_Size_X, int coord_X, int coord_Y);

double calcDistance(double first_X, double first_Y, double second_X, double second_Y);

