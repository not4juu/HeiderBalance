#include "rk4.h"


RK4::RK4(double X0, double Y0, double Z0, double H)
{
    this->x0 = X0;  this->y0 = Y0; this->z0 = Z0; this->h = H;
    this->rgb = QColor(0,0,255);

}

RK4::RK4(Point3D point, double H)
{
    this->x0 = point.x; this->y0 = point.y; this->z0 = point.z;
    this->h = H;
    this->rgb = point.rgb;

}

void RK4::countRK4(std::vector<Point3D>* points)
{
    Point3D pointNext(this->x0, this->y0, this->z0, this->rgb);
    Point3D pointPrev(2., 2., 2., this->rgb);

    double eps = 1e-6;

    while( (fabs(pointNext.x - pointPrev.x) > eps) or (fabs(pointNext.y - pointPrev.y) > eps) or (fabs(pointNext.z - pointPrev.z) > eps) )
    {
            double k1 = this->h * dx(pointNext.x,pointNext.y,pointNext.z);
            double l1 = this->h * dy(pointNext.x,pointNext.y,pointNext.z);
            double m1 = this->h * dz(pointNext.x,pointNext.y,pointNext.z);

            double k2 = this->h * dx(pointNext.x + k1/2., pointNext.y + l1/2., pointNext.z + m1/2.);
            double l2 = this->h * dy(pointNext.x + k1/2., pointNext.y + l1/2., pointNext.z + m1/2.);
            double m2 = this->h * dz(pointNext.x + k1/2., pointNext.y + l1/2., pointNext.z + m1/2.);

            double k3 = this->h * dx(pointNext.x + k2/2., pointNext.y + l2/2., pointNext.z + m2/2.);
            double l3 = this->h * dy(pointNext.x + k2/2., pointNext.y + l2/2., pointNext.z + m2/2.);
            double m3 = this->h * dz(pointNext.x + k2/2., pointNext.y + l2/2., pointNext.z + m2/2.);

            double k4 = this->h * dx(pointNext.x + k3, pointNext.y + l3, pointNext.z + m3);
            double l4 = this->h * dy(pointNext.x + k3, pointNext.y + l3, pointNext.z + m3);
            double m4 = this->h * dz(pointNext.x + k3, pointNext.y + l3, pointNext.z + m3);

            pointPrev = pointNext;

            pointNext.x = pointNext.x + (k1 + 2*k2 + 2*k3 + k4)/6.;
            pointNext.y = pointNext.y + (l1 + 2*l2 + 2*l3 + l4)/6.;
            pointNext.z = pointNext.z + (m1 + 2*m2 + 2*m3 + m4)/6.;
           // qDebug("xp: %.8lf, yp: %.8lf, zp: %.8lf\n", pointPrev.x,pointPrev.y,pointPrev.z);
            points->push_back(pointPrev);
     }
}

double RK4::dx(double x, double y, double z){
    return (1- pow(x,2))*y*z;
}
double RK4::dy(double x, double y, double z){
    return (1- pow(y,2))*x*z;
}
double RK4::dz(double x, double y, double z){
    return (1- pow(z,2))*y*x;
}
