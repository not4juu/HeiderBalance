#ifndef COLORPROPERTIES_H
#define COLORPROPERTIES_H

#include<QColor>

/***
 *  There you can define your all default colors.
 *  All functions use this vaules so if you need others color re-define it there
 ***/

class ColorProperties
{
public:
    static QColor DEFAULT_POINT_COLOR;

    static QColor DEFAULT_PLANE_COLOR;

    //"xyz"
    static QColor STERE_COLOR_0;
    //"-xyz"
    static QColor STERE_COLOR_1;
    //"xy-z"
    static QColor STERE_COLOR_2;
    //"-xy-z"
    static QColor STERE_COLOR_3;
    //"x-yz"
    static QColor STERE_COLOR_4;
    //"-x-yz"
    static QColor STERE_COLOR_5;
    //"x-y-z"
    static QColor STERE_COLOR_6;
    //"-x-y-z"
    static QColor STERE_COLOR_7;

    //"one of variable points is 0"
    static QColor STERE_COLOR_ZERO;


private:
    ColorProperties();
};

#endif // COLORPROPERTIES_H
