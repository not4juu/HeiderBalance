#include "statoutput.h"


StatOutput::StatOutput()
{
}

StatOutput::StatOutput(Point3D firstP, Point3D lastP, double hValue, int Size)
{
    this->h = hValue;
    this->size = Size;

    if( fabs(lastP.x) < 0.01) lastP.x = 0.0;
    if( fabs(lastP.y) < 0.01) lastP.y = 0.0;
    if( fabs(lastP.z) < 0.01) lastP.z = 0.0;

    this->firstStere  = Stere::findStere(firstP);
    this->lastStere = Stere::findStere(lastP);

    this->firstColor = Stere::findStereColor(firstP);
    this->lastColor = Stere::findStereColor(lastP);

    this->firstPoint = firstP;

    int round = 0;

    if( 1.- fabs(lastP.x) < 0.01) round++;
    if( 1.- fabs(lastP.y) < 0.01) round++;
    if( 1.- fabs(lastP.z) < 0.01) round++;

    if(round == 3)
    {
        this->lastPoint = Stere::findSterePoint(this->lastStere);
    }
    else
    {

        this->lastPoint = lastP;
    }
}
