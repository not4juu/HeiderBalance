#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glut.h>
#include "generator.h"
#include "rk4.h"
#include "point3d.h"
#include "stere.h"
#include "plane.h"
#include <QtMath>

/***
 *  This class is responsible for everythink what happens at middle cube area:
 *  (drawing, position view, mouse control, visualization buttons properties, updates etc.)
 ***/

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent *event);

private slots:

    void startButtonClicked();
    void stopButtonClicked();
    void restartButtonClicked();

    void getRK4Points(std::vector<Point3D> allPoints,  double h);
    void repaintTrajectories();
    void lineWidthChange(int);

    void getTimerValue(int time);

    void coordinateSystem();
    void xzPlanePress(int state);
    void yzPlanePress(int state);
    void xyPlanePress(int state);

    void showAllStere();
    void changeStereTransperancy(double);

    void xAxisUp();
    void yAxisUp();
    void zAxisUp();

    void getAllPlanes(std::vector<Plane>, double);
    void clearAllPlanes();

signals:

    void emitPosition(int);

    void allTrajectoriesDrawn();

private:

    void defaultFlagsProperties();

    void drawingTrajectories();
    void drawingPlanes();
    void drawingCoordinateSystem();
    void drawingStere();

    void drawCube(Point3D centerPoint, double size, double transparency, QColor color);
    void drawCube(double x0, double y0, double z0, double size, double transparency, QColor color);


    GLdouble eyex;
    GLdouble eyey;
    GLdouble eyez;

    GLfloat theta;
    GLfloat phi;
    GLfloat distance;

    int upAxis;

    GLfloat rotatex;
    GLfloat rotatey;

    bool mouseLeftButtonPress;
    int button_x;
    int button_y;

    Generator *generator;
    bool drawTrajectories;
    std::vector< std::vector <Point3D> * > allK4Points;
    std::vector< std::vector <Point3D>::iterator > allRK4CurrentPosition;
    std::vector< std::vector <Point3D>::iterator > allRK4LastPosition;
    GLfloat linesWidth;
    bool createRK4;

    std::vector<Plane> allPlanes;
    double alphaChannelPlanes;
    bool drawPlanes;

    bool drawCoordinateSystem;
    bool xzPlaneCoordinateSystem;
    bool yzPlaneCoordinateSystem;
    bool xyPlaneCoordinateSystem;

    bool drawStere;
    double stereTransperancy;
};

#endif // GLWIDGET_H
