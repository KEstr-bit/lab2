#pragma once

enum EndingOption { WinGame, LooseGame };
enum СardinalDirections { North, East, South, West };
enum WeaponOption {ShotGun, Automat};


//установка курсора на позицию  x y 
void setcur(int x, int y);

char* strcopy(char* _Destination, const char* _Source);

int myRound(double number);

int abss(int number);

double abss(double number);

bool isWall(char* world_Map, int map_Size_X, int coord_X, int coord_Y);

double calcDistance(double first_X, double first_Y, double second_X, double second_Y);

double degToRad(double deg);

double radToDeg(double rad);

double projectionToX(double len, double rad_Angle);

double projectionToY(double len, double rad_Angle);

double interpolateCoord(double startCoord, double finalCoord, double step, double distance);
