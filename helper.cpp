#include "Helper.h"
#include <iostream>


double Helper::round(const double number)
{
    if (number > 0) 
    {
        return static_cast<int>(number + 0.5);
    }
    return static_cast<int>(number - 0.5);
};


double Helper::abs(const double number)
{
    if (number > 0)
    {
        return number;
    }
    return number * (-1);
};


double Helper::calcDistance(const double firstX, const double firstY, const double secondX, const double secondY) {
    return sqrt((firstX - secondX) * (firstX - secondX) + (firstY - secondY) * (firstY - secondY));
};

double Helper::degToRad(const double degrees)
{
    return degrees * 3.14 / 180;
}

double Helper::radToDeg(const double radians)
{
    return radians * 180 / 3.14;
}

double Helper::projectToX(const double length, const double radians)
{
    return length * cos(radians);
}

double Helper::projectToY(const double length, const double radians)
{
    return length * sin(radians);
}

double Helper::interpolateCoords(const double startCoordinate, const double finalCoordinate, const double step, const double distance)
{
    return (step * finalCoordinate + (distance - step) * startCoordinate) / distance;
}

double Helper::getRotationAngle(const double radians, const double lineCos, const double lineSin) {
    double rotationCos = cos(radians) * lineCos + sin(radians) * lineSin;
    const double rotationSin = sin(radians) * lineCos - cos(radians) * lineSin;

    if (rotationCos > 1)
        rotationCos = 1;

    if (rotationCos < -1)
        rotationCos = -1;

    double rotationAngle = radToDeg(acos(rotationCos));

    if (rotationSin < 0)
        rotationAngle *= -1;

    return rotationAngle;
}