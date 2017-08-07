#ifndef STERE_H
#define STERE_H

#include <QColor>
#include "point3d.h"
#include "colorproperties.h"


class Stere
{
public:
    static QColor findStereColor(QString stere);
    static QColor findStereColor(int stere);
    static QColor findStereColor(Point3D stere);

    static int findStere(Point3D stere);
    static Point3D findSterePoint(int stere);

    static Point3D centerPoint(QString stere);
    static Point3D centerPoint(int stere);

    static Point3D getRandomStere(QString stere);
    static Point3D getRandomStere(int stere);

    static QString getStereString(int stere);
    static QString getStereString(Point3D stere);
private:
    Stere();
};

#endif // STERE_H
