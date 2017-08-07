#ifndef STATOUTPUT_H
#define STATOUTPUT_H

#include <QColor>
#include <QCheckBox>
#include "point3d.h"
#include "stere.h"
#include <math.h>


class StatOutput
{
public:
    StatOutput();


    StatOutput(Point3D firstP, Point3D lastP, double hValue, int Size);

    Point3D firstPoint;
    Point3D lastPoint;

    QColor firstColor;
    QColor lastColor;

    double h;
    int size;

    int firstStere;
    int lastStere;
};

#endif // STATOUTPUT_H
