#ifndef PLANE_H
#define PLANE_H

#include <QColor>
#include "point3d.h"
#include "colorproperties.h"


/***
 *  Here we try find a Points where surface intersect the Cube
 *  I am finding a parametric representation for all lines of cube (12 - lines)
 *  r(t) = <x0, y0, z0> + t < x-x0, y-y0, z-z0>
 *  planes: Ax + By + Cz + d = 0
 *  then I am finding a intersection with this lines
 *  and unique points, next i am choosing only points which are in Cube and return it
 *
 * to finding t value i use pattern :
 *
 * t = -1 * (A * x0 + B *y0 + C *z0 +d) /  A * (x-x0) + B *(y-y0) + C(z-z0)
 * of course we have to check if denominator is not a 0
 *
 ***/

class Plane
{
public:
    Plane(double , double , double , double, QColor color = ColorProperties::DEFAULT_PLANE_COLOR);
    std::vector<Point3D> getIntersectionWithCube();
    QColor getPlaneColor();

private:
    double A;
    double B;
    double C;
    double d;

    QColor planeColor;

    Point3D findIntersection(Point3D first , Point3D last);
    bool uniquePoint(std::vector<Point3D> points, Point3D currPoint);
    std::vector<Point3D> checkPointsOrder(std::vector<Point3D> points);
};

#endif // PLANE_H
