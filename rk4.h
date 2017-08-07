#ifndef RK4_H
#define RK4_H

#include <math.h>
#include "point3d.h"

/***
 *  Class responsible for counting heider balance points
 *  Here you can define eps (default eps = 1e-6)
 *
 *  |x| < 1 , |y| < 1, |z| < 1
 *  x' = (1 - x^2)yz
 *  y' = (1 - y^2)zx
 *  z' = (1 - z^2)xy
 *
 * There we are using numerical analyssis Runge-Kutta method
 ***/

class RK4
{
public:
    RK4(double X0, double Y0, double Z0, double H);
    RK4(Point3D, double H);

    void countRK4(std::vector<Point3D> *points);

private:
    double x0;
    double y0;
    double z0;
    double h;

    QColor rgb;

    double dx(double x, double y, double z);
    double dy(double x, double y, double z);
    double dz(double x, double y, double z);
};

#endif // RK4_H
