#pragma once
#include <vector>

enum EndingOption { WIN_GAME, LOOSE_GAME };
enum CardinalDirections { NORTH, EAST, SOUTH, WEST };
enum GunOption { GUN_SHOTGUN, GUN_RIFLE };

class Helper
{
public:
	//округление
	static double round(double number);
	//модуль
	static double abs(double number);
	//расстояние между двумя точками
	static double calcDistance(double firstX, double firstY, double secondX, double secondY);
	//перевод градусов в радианы
	static double degToRad(double degrees);
	//перевод радиан в градусы
	static double radToDeg(double radians);
	//проекция вектора на ось
	static double projectToX(double length, double radians);
	static double projectToY(double length, double radians);
	//интерполяция координат
	static double interpolateCords(double startCoordinate, double finalCoordinate, double step, double distance);
	static double getRotationAngle(double radians, double lineCos, double lineSin);

	template<typename T, typename Q>
	static void dependSorting(std::vector<T>& mainMas, std::vector<Q>& sideMas, int left, int right);
};

template <typename T, typename Q>
void Helper::dependSorting(std::vector<T>& mainMas, std::vector<Q>& sideMas, int left, int right)
{
    //Указатели в начало и в конец массива
    int i = left, j = right;

    //Центральный элемент массива
    T mid = mainMas[(left + right) / 2];

    //Делим массив
    do {

        while (mainMas[i] > mid) {
            i++;
        }

        while (mainMas[j] < mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {

            std::swap(sideMas[i], sideMas[j]);
            std::swap(mainMas[i], mainMas[j]);

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if (left < j)
        dependSorting(mainMas, sideMas, left, j);
    if (i < right)
        dependSorting(mainMas, sideMas, i, right);
}
