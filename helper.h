#pragma once

enum EndingOption { WinGame, LooseGame };
enum СardinalDirections { North, East, South, West };
enum WeaponOption {ShotGun, Automat};

static class helper
{
public:
	static void setcur(int x, int y);
	static char* strcopy(char* _Destination, const char* _Source);
	//округление
	static int myRound(double number);
	//модуль
	static int myAbs(int number);
	static double myAbs(double number);
	//расстояние между двумя точками
	static double calcDistance(double first_X, double first_Y, double second_X, double second_Y);
	//перевод градусов в радианы
	static double degToRad(double deg);
	//перевод радиан в градусы
	static double radToDeg(double rad);
	//проекция вектора на ось
	static double projectionToX(double len, double rad_Angle);
	static double projectionToY(double len, double rad_Angle);
	//интерполяция координат
	static double interpolateCoord(double startCoord, double finalCoord, double step, double distance);
	static double getRotAngle(double playerAngle, double cosPlEnLine, double sinPlEnLine);
};
