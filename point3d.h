#ifndef POINT3D_H
#define POINT3D_H

#include "QColor"
#include "colorproperties.h"

class Point3D
{
public:
    Point3D();
    Point3D(double xPoint, double yPoint , double zPoint, QColor rgbPoint = ColorProperties::DEFAULT_POINT_COLOR);

    void setPonint(double x0, double y0, double z0);

    static Point3D randPoint(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax);

    double x;
    double y;
    double z;

    QColor rgb;
};

#endif // POINT3D_H
