#include "plane.h"

Plane::Plane(double Aval, double Bval, double Cval, double dval, QColor color)
{
    this->A = Aval;
    this->B = Bval;
    this->C = Cval;
    this->d = dval;

    this->planeColor = color;
}

std::vector<Point3D> Plane::getIntersectionWithCube()
{
    //define all Cube points
    Point3D xyz(1,1,1);
    Point3D xnyz(1,-1,1);

    Point3D nxyz(-1,1,1);
    Point3D nxnyz(-1,-1,1);

    Point3D xynz(1,1,-1);
    Point3D xnynz(1,-1,-1);

    Point3D nxynz(-1,1,-1);
    Point3D nxnynz(-1,-1,-1);


    std::vector<Point3D> interPoints;

    Point3D intPoint;
    intPoint = findIntersection(nxyz,xyz);//d
    if(uniquePoint(interPoints,intPoint))interPoints.push_back(intPoint);
    intPoint = findIntersection(nxnyz,xnyz);//c
    if(uniquePoint(interPoints,intPoint))interPoints.push_back(intPoint);
    intPoint = findIntersection(xnyz,xyz);//a
    if(uniquePoint(interPoints,intPoint))interPoints.push_back(intPoint);
    intPoint = findIntersection(xnyz,xnynz);//e
    if(uniquePoint(interPoints,intPoint))interPoints.push_back(intPoint);
    intPoint = findIntersection(xyz,xynz);//g
    if(uniquePoint(interPoints,intPoint))interPoints.push_back(intPoint);
    intPoint = findIntersection(xnynz,xynz);//f
    if(uniquePoint(interPoints,intPoint))interPoints.push_back(intPoint);
    intPoint = findIntersection(nxnynz,xnynz);//k
    if(uniquePoint(interPoints,intPoint))interPoints.push_back(intPoint);
    intPoint = findIntersection(nxynz,xynz);//l
    if(uniquePoint(interPoints,intPoint))interPoints.push_back(intPoint);
    intPoint = findIntersection(nxnynz,nxynz);//i
    if(uniquePoint(interPoints,intPoint))interPoints.push_back(intPoint);
    intPoint = findIntersection(nxyz,nxynz);//j
    if(uniquePoint(interPoints,intPoint))interPoints.push_back(intPoint);
    intPoint = findIntersection(nxnyz,nxnynz);//h
    if(uniquePoint(interPoints,intPoint))interPoints.push_back(intPoint);
    intPoint = findIntersection(nxnyz,nxyz);//b
    if(uniquePoint(interPoints,intPoint))interPoints.push_back(intPoint);


    if(interPoints.size() == 4)interPoints = checkPointsOrder(interPoints);
    return interPoints;
}

QColor Plane::getPlaneColor()
{
    return this->planeColor;
}
Point3D Plane::findIntersection(Point3D first, Point3D last)
{

    Point3D parametric (last.x - first.x, last.y - first.y, last.z - first.z);
    double denominator = this->A * (last.x - first.x) + this->B * (last.y - first.y) + this->C * (last.z - first.z);
    Point3D final(2,2,2);

    double t;
    if(denominator !=0)
    {
        t = (-1 * (this->A * first.x + this->B * first.y + this->C * first.z + this->d)) / denominator;
        final.x = first.x + t * parametric.x;
        final.y = first.y + t * parametric.y;
        final.z = first.z + t * parametric.z;
    }
    return final;
}

bool Plane::uniquePoint(std::vector<Point3D> points, Point3D currPoint)
{
    bool output = true;

    //checking if points is in Cube
    if(currPoint.x > 1 || currPoint.x < -1 || currPoint.y > 1 || currPoint.y < -1 || currPoint.z > 1 || currPoint.z < -1) output = false;

    for(unsigned i=0; i < points.size(); ++i)
    {
        // checking if points is uniqe
       if(points.at(i).x == currPoint.x && points.at(i).y == currPoint.y && points.at(i).z == currPoint.z)output = false;

    }
    return output;
}

std::vector<Point3D> Plane::checkPointsOrder(std::vector<Point3D> points)
{
    std::vector<Point3D> goodOrder;
    if((points.at(0).y > 0 && points.at(3).y < 0) || (points.at(0).y < 0 && points.at(3).y > 0))
    {
        goodOrder.push_back(points.at(0));
        goodOrder.push_back(points.at(1));
        goodOrder.push_back(points.at(3));
        goodOrder.push_back(points.at(2));
        return goodOrder;
    }
    else
    {
        return points;
    }
}
