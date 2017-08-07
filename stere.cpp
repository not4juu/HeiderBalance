#include "stere.h"

QColor Stere::findStereColor(QString stere)
{
    QColor outColor = ColorProperties::DEFAULT_POINT_COLOR;
    // PINK
    if(stere == "xyz"       || stere == "upFrontRightStere")    outColor = ColorProperties::STERE_COLOR_0;
    // YELLOW
    if(stere == "-xyz"      || stere == "upFrontLeftStere")     outColor = ColorProperties::STERE_COLOR_1;
    // LIGHT BLUE
    if(stere == "xy-z"      || stere == "upBackRightStere")     outColor = ColorProperties::STERE_COLOR_2;
    // GREEN
    if(stere == "-xy-z"     || stere == "upBackLeftStere")      outColor = ColorProperties::STERE_COLOR_3;
    // BRWON
    if(stere == "x-yz"      || stere == "downFrontRightStere")  outColor = ColorProperties::STERE_COLOR_4;
    // RED
    if(stere == "-x-yz"     || stere == "downFrontLeftStere")   outColor = ColorProperties::STERE_COLOR_5;
    // ORANGE
    if(stere == "x-y-z"     || stere == "downBackRightStere")   outColor = ColorProperties::STERE_COLOR_6;
    // PURPLE
    if(stere == "-x-y-z"    || stere == "downBackLeftStere")    outColor = ColorProperties::STERE_COLOR_7;

    // BLACK
    if(stere == "zero" )  outColor = ColorProperties::STERE_COLOR_ZERO;

    return outColor;
}

QColor Stere::findStereColor(int stere)
{
    QColor outColor = ColorProperties::DEFAULT_POINT_COLOR;
    if(stere == 0)   outColor = Stere::findStereColor("xyz");
    if(stere == 1)   outColor = Stere::findStereColor("-xyz");
    if(stere == 2)   outColor = Stere::findStereColor("xy-z");
    if(stere == 3)   outColor = Stere::findStereColor("-xy-z");
    if(stere == 4)   outColor = Stere::findStereColor("x-yz");
    if(stere == 5)   outColor = Stere::findStereColor("-x-yz");
    if(stere == 6)   outColor = Stere::findStereColor("x-y-z");
    if(stere == 7)   outColor = Stere::findStereColor("-x-y-z");
    if(stere == 8)   outColor = Stere::findStereColor("zero");
    return outColor;
}

QColor Stere::findStereColor(Point3D stere)
{
    QColor outColor = ColorProperties::DEFAULT_POINT_COLOR;
    if(stere.x > 0. && stere.y > 0. && stere.z > 0.)   outColor = Stere::findStereColor("xyz");
    if(stere.x < 0. && stere.y > 0. && stere.z > 0.)   outColor = Stere::findStereColor("-xyz");
    if(stere.x > 0. && stere.y > 0. && stere.z < 0.)   outColor = Stere::findStereColor("xy-z");
    if(stere.x < 0. && stere.y > 0. && stere.z < 0.)   outColor = Stere::findStereColor("-xy-z");
    if(stere.x > 0. && stere.y < 0. && stere.z > 0.)   outColor = Stere::findStereColor("x-yz");
    if(stere.x < 0. && stere.y < 0. && stere.z > 0.)   outColor = Stere::findStereColor("-x-yz");
    if(stere.x > 0. && stere.y < 0. && stere.z < 0.)   outColor = Stere::findStereColor("x-y-z");
    if(stere.x < 0. && stere.y < 0. && stere.z < 0.)   outColor = Stere::findStereColor("-x-y-z");
    if(stere.x == 0. || stere.y == 0. || stere.z == 0.)   outColor = Stere::findStereColor("zero");
    return outColor;

}

int Stere::findStere(Point3D stere)
{
    int outStere = 0;
    if(stere.x > 0. && stere.y > 0. && stere.z > 0.)  outStere = 0;
    if(stere.x < 0. && stere.y > 0. && stere.z > 0.)  outStere = 1;
    if(stere.x > 0. && stere.y > 0. && stere.z < 0.)  outStere = 2;
    if(stere.x < 0. && stere.y > 0. && stere.z < 0.)  outStere = 3;
    if(stere.x > 0. && stere.y < 0. && stere.z > 0.)  outStere = 4;
    if(stere.x < 0. && stere.y < 0. && stere.z > 0.)  outStere = 5;
    if(stere.x > 0. && stere.y < 0. && stere.z < 0.)  outStere = 6;
    if(stere.x < 0. && stere.y < 0. && stere.z < 0.)  outStere = 7;
    if(stere.x == 0. || stere.y == 0. || stere.z == 0.) outStere = 8;
    return outStere;
}

Point3D Stere::findSterePoint(int stere)
{
    Point3D outStere;
    if(stere == 0){  outStere.x = 1.; outStere.y = 1. ; outStere.z = 1.; }
    if(stere == 1){  outStere.x = -1.; outStere.y = 1. ; outStere.z = 1.; }
    if(stere == 2){  outStere.x = 1.; outStere.y = 1. ; outStere.z = -1.; }
    if(stere == 3){  outStere.x = -1.; outStere.y = 1. ; outStere.z = -1.; }
    if(stere == 4){  outStere.x = 1.; outStere.y = -1. ; outStere.z = 1.; }
    if(stere == 5){  outStere.x = -1.; outStere.y = -1. ; outStere.z = 1.; }
    if(stere == 6){  outStere.x = 1.; outStere.y = -1. ; outStere.z = -1.; }
    if(stere == 7){  outStere.x = -1.; outStere.y = -1. ; outStere.z = -1.; }
    return outStere;
}

Point3D Stere::centerPoint(QString stere)
{
    Point3D centerPoint(0,0,0,ColorProperties::DEFAULT_POINT_COLOR);
    // PINK
    if(stere == "xyz"       || stere == "upFrontRightStere")    centerPoint.setPonint(0.5,0.5,0.5);
    // PURPLE
    if(stere == "-xyz"      || stere == "upFrontLeftStere")     centerPoint.setPonint(-0.5,0.5,0.5);
    // LIGHT BLUE
    if(stere == "xy-z"      || stere == "upBackRightStere")     centerPoint.setPonint(0.5,0.5,-0.5);
    // YELLOW
    if(stere == "-xy-z"     || stere == "upBackLeftStere")      centerPoint.setPonint(-0.5,0.5,-0.5);
    // BRWON
    if(stere == "x-yz"      || stere == "downFrontRightStere")  centerPoint.setPonint(0.5,-0.5,0.5);
    // RED
    if(stere == "-x-yz"     || stere == "downFrontLeftStere")   centerPoint.setPonint(-0.5,-0.5,0.5);
    // ORANGE
    if(stere == "x-y-z"     || stere == "downBackRightStere")   centerPoint.setPonint(0.5,-0.5,-0.5);
    // GREEN
    if(stere == "-x-y-z"    || stere == "downBackLeftStere")    centerPoint.setPonint(-0.5,-0.5,-0.5);

    return centerPoint;
}

Point3D Stere::centerPoint(int stere)
{
    Point3D centerPoint(0, 0 ,0 ,ColorProperties::DEFAULT_POINT_COLOR);
    if(stere == 0)   centerPoint = Stere::centerPoint("xyz");
    if(stere == 1)   centerPoint = Stere::centerPoint("-xyz");
    if(stere == 2)   centerPoint = Stere::centerPoint("xy-z");
    if(stere == 3)   centerPoint = Stere::centerPoint("-xy-z");
    if(stere == 4)   centerPoint = Stere::centerPoint("x-yz");
    if(stere == 5)   centerPoint = Stere::centerPoint("-x-yz");
    if(stere == 6)   centerPoint = Stere::centerPoint("x-y-z");
    if(stere == 7)   centerPoint = Stere::centerPoint("-x-y-z");
    return centerPoint;
}

Point3D Stere::getRandomStere(QString stere)
{
    Point3D randomPoint(-0.9999999,-0.9999999,-0.9999999, ColorProperties::DEFAULT_POINT_COLOR);
    // PINK
    if(stere == "xyz"       || stere == "upFrontRightStere")    randomPoint= Point3D::randPoint(0.,1.,0.,1.,0.,1.);
    // PURPLE
    if(stere == "-xyz"      || stere == "upFrontLeftStere")     randomPoint= Point3D::randPoint(-1.,0.,0.,1.,0.,1.);
    // LIGHT BLUE
    if(stere == "xy-z"      || stere == "upBackRightStere")     randomPoint= Point3D::randPoint(0.,1.,0.,1.,-1.,0.);
    // YELLOW
    if(stere == "-xy-z"     || stere == "upBackLeftStere")      randomPoint= Point3D::randPoint(-1.,0.,0.,1.,-1.,0.);
    // BRWON
    if(stere == "x-yz"      || stere == "downFrontRightStere")  randomPoint= Point3D::randPoint(0.,1.,-1.,0.,0.,1.);
    // RED
    if(stere == "-x-yz"     || stere == "downFrontLeftStere")   randomPoint= Point3D::randPoint(-1.,0.,-1.,0.,0.,1.);
    // ORANGE
    if(stere == "x-y-z"     || stere == "downBackRightStere")   randomPoint= Point3D::randPoint(0.,1.,-1.,0.,-1.,0.);
    // GREEN
    if(stere == "-x-y-z"    || stere == "downBackLeftStere")    randomPoint= Point3D::randPoint(-1.,0.,-1.,0.,-1.,0.);

    return randomPoint;
}

Point3D Stere::getRandomStere(int stere)
{
    Point3D randomPoint(-0.9999999,-0.9999999,-0.9999999, ColorProperties::DEFAULT_POINT_COLOR);
    if(stere == 0)   randomPoint = Stere::getRandomStere("xyz");
    if(stere == 1)   randomPoint = Stere::getRandomStere("-xyz");
    if(stere == 2)   randomPoint = Stere::getRandomStere("xy-z");
    if(stere == 3)   randomPoint = Stere::getRandomStere("-xy-z");
    if(stere == 4)   randomPoint = Stere::getRandomStere("x-yz");
    if(stere == 5)   randomPoint = Stere::getRandomStere("-x-yz");
    if(stere == 6)   randomPoint = Stere::getRandomStere("x-y-z");
    if(stere == 7)   randomPoint = Stere::getRandomStere("-x-y-z");
    return randomPoint;
}

QString Stere::getStereString(int stere)
{
    QString outString("error stere");

    if(stere == 0)   outString = " x  y  z";
    if(stere == 1)   outString = "-x  y  z";
    if(stere == 2)   outString = " x  y -z";
    if(stere == 3)   outString = "-x  y -z";
    if(stere == 4)   outString = " x -y  z";
    if(stere == 5)   outString = "-x -y  z";
    if(stere == 6)   outString = " x -y -z";
    if(stere == 7)   outString = "-x -y -z";

    if(stere == 8)   outString = "zero";

    return outString;
}

QString Stere::getStereString(Point3D stere)
{
    QString outString("error stere");

    if(stere.x > 0. && stere.y > 0. && stere.z > 0.)   outString = Stere::getStereString(0);
    if(stere.x < 0. && stere.y > 0. && stere.z > 0.)   outString = Stere::getStereString(1);
    if(stere.x > 0. && stere.y > 0. && stere.z < 0.)   outString = Stere::getStereString(2);
    if(stere.x < 0. && stere.y > 0. && stere.z < 0.)   outString = Stere::getStereString(3);
    if(stere.x > 0. && stere.y < 0. && stere.z > 0.)   outString = Stere::getStereString(4);
    if(stere.x < 0. && stere.y < 0. && stere.z > 0.)   outString = Stere::getStereString(5);
    if(stere.x > 0. && stere.y < 0. && stere.z < 0.)   outString = Stere::getStereString(6);
    if(stere.x < 0. && stere.y < 0. && stere.z < 0.)   outString = Stere::getStereString(7);

    if(stere.x == 0. || stere.y == 0. || stere.z == 0.)   outString = Stere::getStereString(8);

    return outString;
}
Stere::Stere()
{
}
