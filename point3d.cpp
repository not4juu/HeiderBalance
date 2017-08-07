#include "point3d.h"


Point3D::Point3D()
{
    this->x = 0.;
    this->y = 0.;
    this->z = 0.;

    this->rgb = ColorProperties::DEFAULT_POINT_COLOR;
}

Point3D::Point3D(double xPoint, double yPoint, double zPoint, QColor rgbPoint)
{
    this->x = xPoint;
    this->y = yPoint;
    this->z = zPoint;

    this->rgb = rgbPoint;
}

void Point3D::setPonint(double x0, double y0, double z0)
{
    this->x = x0;
    this->y = y0;
    this->z = z0;
}

Point3D Point3D::randPoint(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
{
    Point3D randPoint;
    randPoint.x = xmin + (std::rand()/(RAND_MAX +1.0))* (xmax - xmin);
    randPoint.y = ymin + (std::rand()/(RAND_MAX +1.0))* (ymax - ymin);
    randPoint.z = zmin + (std::rand()/(RAND_MAX +1.0))* (zmax - zmin) ;
   // qDebug("Point x%lf, y%lf, z%lf", randPoint.x,randPoint.y,randPoint.z);
    return randPoint;
}
