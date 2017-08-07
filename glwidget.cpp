#include "glwidget.h"
#include <QThread>
#include <QTime>


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    this->generator = new Generator();
    this->generator->setSleepTime(500);
    connect(this->generator, SIGNAL(repaintGenerator()), this, SLOT(repaintTrajectories()));

    defaultFlagsProperties();
}

GLWidget::~GLWidget()
{
    while(!this->allK4Points.empty())
    {
        std::vector<Point3D> *points = this->allK4Points.back();
        this->allK4Points.pop_back();
        delete points;
    }
    this->generator->setPaintTrajectories(false);
    this->generator->wait();

    delete this->generator;
}
//------------------------------------------------------------------------


//********************* PROTECTED FUCNTIONS ******************************


//-------------------- INITIALIZE PAIN RESIZE FUNCTIONS-------------------
void GLWidget::initializeGL()
{
    glClearColor(1,1,1,1);
    glEnable(GL_COLOR_MATERIAL);
}

void GLWidget::paintGL()
{
    //int time = QTime::currentTime().msec();
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
                distance * cos(theta) * cos(phi),
                distance * sin(theta),
                distance * cos(theta) * sin(phi),
                0,0,0,
                distance * cos(theta + 0.1) * cos(phi),
                distance * sin(theta + 0.1),
                distance * cos(theta + 0.1) * sin(phi)
             );
    switch(this->upAxis)
    {
    case 1:
        glRotatef (90, 0.0,0.0,1.0); // x axis up
        glRotatef (90, 1.0,0.0,0.0); // set default eye veiw of coordinate system
        break;
    case 2:
        //default opneGL has y axis up, pleas check opengl coordinate system
        break;
    case 3:
        glRotatef (-90, 1.0,0.0,0.0); // z axis up
        glRotatef (90, 0.0,0.0,-1.0); // set default eye veiw of coordinate system
        break;
    }

    glColor3f(0,0,0);
    glutWireCube(2);

    //QThread::msleep(16);

    drawingTrajectories();

    if(this->drawStere)
    {
        drawingStere();
    }

    if(this->drawPlanes)
    {
        drawingPlanes();
    }

    if(this->drawCoordinateSystem){
        drawingCoordinateSystem();
    }
    //qDebug("time %d", QTime::currentTime().msec() - time);
}
void GLWidget::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(float)width/height, 0.01,100.0 );
    updateGL();
}
//------------------------------------------------------------------------





//---------------------- MOUSE EVENTS -----------------------
void GLWidget::mousePressEvent(QMouseEvent* event)
{
    this->button_x = event->x();
    this->button_y = event->y();

    if(event->button() == Qt::RightButton)
        this->mouseLeftButtonPress = true;
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
    if(this->mouseLeftButtonPress){

        //this->rotatey += 200 / (float)this->width() * (event->x() - this->button_x);
        this->phi += (event->x() - this->button_x) * 0.01f;
        this->button_x = event->x();
        //this->rotatex += 200 / (float)this->height() *(event->y() - this->button_y);
        this->theta += (event->y() - this->button_y) * 0.01f;
        this->button_y =event->y();
        updateGL();
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton)
       this->mouseLeftButtonPress = false;

    updateGL();

}
void GLWidget::wheelEvent(QWheelEvent *event)
{
    //event->delta() > 0 ? this->eyez+= 0.1 : this->eyez-= 0.1;
    event->delta() > 0 ? this->distance+= 0.1 : this->distance-= 0.1;
    updateGL();
}
//------------------------------------------------------------------------


//****************************** SLOTS ***********************************


//---------------------- START/STOP/RESTART BUTTONS -----------------------

void GLWidget::startButtonClicked()
{
    this->drawTrajectories = true;
    this->generator->setPaintTrajectories(true);
    this->generator->start();
    updateGL();
}

void GLWidget::stopButtonClicked()
{
    this->drawTrajectories = false;
    this->generator->setPaintTrajectories(false);
    updateGL();
}
void GLWidget::restartButtonClicked()
{
    this->generator->setPaintTrajectories(false);
    this->generator->wait();

    while(!this->allRK4CurrentPosition.empty())
    {
       this->allRK4CurrentPosition.pop_back();
    }

    while(!this->allRK4LastPosition.empty())
    {
       this->allRK4LastPosition.pop_back();
    }

    while(!this->allK4Points.empty())
    {
        std::vector<Point3D> *points = this->allK4Points.back();
        this->allK4Points.pop_back();
        delete points;
    }

    defaultFlagsProperties();

    updateGL();
}
//------------------------------------------------------------------------





//---------------------------- UPLOAD POINTS ------------------------------
void GLWidget::getRK4Points(std::vector<Point3D> allPoints, double h)
{
    if(this->createRK4)
    {
        while(!allPoints.empty())
        {
            Point3D point  = allPoints.back();
            allPoints.pop_back();

            std::vector<Point3D> *rk4Points = new std::vector<Point3D>;
            RK4 obj(point,h);
            obj.countRK4(rk4Points);

            std::vector<Point3D>::iterator startPosition = rk4Points->begin();
            std::vector<Point3D>::iterator lastPosition = rk4Points->end();

            //przesuniecie aby sie narysowala pierwsza prosta
            startPosition++;

            this->allRK4CurrentPosition.push_back(startPosition);
            this->allRK4LastPosition.push_back(lastPosition);

            this->allK4Points.push_back(rk4Points);
        }
        this->createRK4 = false;
    }
}
//------------------------------------------------------------------------





//-------------------- REPAINT TRAJECTORIES FUNCTION----------------------
void GLWidget::repaintTrajectories()
{
    bool allPointsDrawn = true;

    int drawProgress = 0;

    for(unsigned iter = 0 ; iter < this->allK4Points.size(); iter++)
    {
        std::vector<Point3D>::iterator currentPosition = this->allRK4CurrentPosition.at(iter);
        std::vector<Point3D>::iterator lastPosition = this->allRK4LastPosition.at(iter);

        if(currentPosition != lastPosition)
        {
            this->allRK4CurrentPosition.at(iter)++;
            allPointsDrawn = false;
        }
        if(lastPosition - currentPosition > drawProgress ) drawProgress = lastPosition - currentPosition;
       //qDebug("Current x %lf, y %lf, z %lf", (*currentPosition).x, (*currentPosition).y,  (*currentPosition).z);
    }

    emit emitPosition(drawProgress);

    if(allPointsDrawn)
    {
        this->drawTrajectories = false;
        this->generator->setPaintTrajectories(false);
        this->generator->wait();
        emit allTrajectoriesDrawn();
    }

    updateGL();
}
//------------------------------------------------------------------------





//-------------------- LINE WIDTH / TIMER FUNCTIONS ----------------------
void GLWidget::lineWidthChange(int value)
{
    this->linesWidth = value;
    updateGL();
}
void GLWidget::getTimerValue(int time)
{
    int t = time/20. * 1000;
    this->generator->setSleepTime(t);
}

//------------------------------------------------------------------------





//-------------------- COORDINATE SYSTEM FUNCTIONS -----------------------
void GLWidget::coordinateSystem()
{
    this->drawCoordinateSystem = !this->drawCoordinateSystem;
    updateGL();
}
void GLWidget::xzPlanePress(int state)
{
    this->xzPlaneCoordinateSystem = !this->xzPlaneCoordinateSystem;
    updateGL();
}

void GLWidget::yzPlanePress(int state)
{
    this->yzPlaneCoordinateSystem = !this->yzPlaneCoordinateSystem;
    updateGL();
}

void GLWidget::xyPlanePress(int state)
{
    this->xyPlaneCoordinateSystem = !this->xyPlaneCoordinateSystem;
    updateGL();
}
//------------------------------------------------------------------------





//--------------------------- STERE FUNCTIONS ----------------------------

void GLWidget::showAllStere()
{
    this->drawStere = !this->drawStere;
    updateGL();
}
void GLWidget::changeStereTransperancy(double val)
{
    this->stereTransperancy = val;
    updateGL();
}

void GLWidget::xAxisUp()
{
    this->upAxis = 1;
    //this->phi = 2.3;
    updateGL();
}
void GLWidget::yAxisUp()
{
    this->upAxis = 2;
    updateGL();
}
void GLWidget::zAxisUp()
{
    this->upAxis = 3;
    updateGL();
}
//------------------------------------------------------------------------





//-------------------------- PLANES FUNCTIONS ----------------------------
void GLWidget::getAllPlanes(std::vector<Plane> planes, double alphaChannel)
{
    this->allPlanes = planes;
    this->alphaChannelPlanes = alphaChannel;
    this->drawPlanes = true;
    updateGL();
}

void GLWidget::clearAllPlanes()
{
    this->drawPlanes = false;
    updateGL();
}
//------------------------------------------------------------------------


//*********************** PRIVATE FUCNTIONS ******************************


//-------------------------- DEFAULTS FLAGS ------------------------------
void GLWidget::defaultFlagsProperties()
{
    this->eyex = 0;
    this->eyey = 2;
    this->eyez = 4;

    this->distance = 6.0;
    this->theta = 0.4;
    this->phi = 0.3;

    this->upAxis = 2;

    this->rotatex = 0;
    this->rotatey = 0;

    this->drawTrajectories = false;
    this->linesWidth = 1.;

    this->createRK4 = true;

    this->drawPlanes =false;

    this->drawCoordinateSystem = false;
    this->xzPlaneCoordinateSystem = false;
    this->yzPlaneCoordinateSystem = false;
    this->xyPlaneCoordinateSystem = false;

    this->drawStere = false;
    this->stereTransperancy = 0.3;

    this->mouseLeftButtonPress = false;
}
//------------------------------------------------------------------------





//------------------- DRAWING TRAJECTORIES FUNCTION ----------------------
void GLWidget::drawingTrajectories()
{
   glLineWidth(this->linesWidth);

   if(!this->createRK4)
   {
        for(unsigned iter= 0 ; iter < this->allK4Points.size(); iter++)
        {
            std::vector<Point3D> *rk4Points = this->allK4Points.at(iter);
            std::vector<Point3D>::iterator iterPosition = rk4Points->begin();
            std::vector<Point3D>::iterator currentPosition = this->allRK4CurrentPosition.at(iter);

            Point3D prevPoint = *iterPosition; iterPosition++;

            glColor3f(prevPoint.rgb.red()/255., prevPoint.rgb.green()/255., prevPoint.rgb.blue()/255.);

            while(iterPosition != currentPosition)
            {
                 Point3D nextPoints = *iterPosition; iterPosition++;

                 glBegin(GL_LINES);
                     glVertex3f(prevPoint.x,prevPoint.y,prevPoint.z);
                     glVertex3f(nextPoints.x,nextPoints.y,nextPoints.z);
                 glEnd();

                 prevPoint =  nextPoints;
            }
        }
   }
   glLineWidth(1);
}
//------------------------------------------------------------------------





//----------------- DRAWING COORDINATE SYSTEM FUNCTION -------------------
void GLWidget::drawingCoordinateSystem()
{
    glColor3f(0,0,1);
    renderText(1.02 ,-0.01  ,0.01,"X");
    renderText(-0.01  ,1.02   ,0.01,"Y");
    renderText(0.01  ,-0.01   ,1.02,"Z");

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0xAAAA);
        glBegin(GL_LINES);
            //-------X--------
            glVertex3f(-1.  ,0. ,0.);
            glVertex3f(1.   ,0. ,0.);

            glVertex3f(1.   ,0.     ,0.);
            glVertex3f(0.95 ,0.03   ,0.);
            glVertex3f(1.   ,0.     ,0.);
            glVertex3f(0.95,-0.03   ,0.);

            //-------Y--------
            glVertex3f(0.,-1.,0.);
            glVertex3f(0.,1.,0.);

            glVertex3f(0.,1.,0.);
            glVertex3f(0.03,0.95,0.);
            glVertex3f(0.,1.,0.);
            glVertex3f(-0.03,0.95,0.);

            //------Z--------
            glVertex3f(0.,0.,-1.);
            glVertex3f(0.,0.,1.);

            glVertex3f(0.,0.,1.);
            glVertex3f(0.,0.03,0.95);
            glVertex3f(0.,0.,1.);
            glVertex3f(0.,-0.03,0.95);
        glEnd();
    glDisable(GL_LINE_STIPPLE);

    if(this->xzPlaneCoordinateSystem )
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glColor4f(0,0,0,0.1);
        glBegin(GL_QUADS);
            glVertex3f(1.,0.,1.);
            glVertex3f(1.,0.,-1.);
            glVertex3f(-1.,0.,-1.);
            glVertex3f(-1.,0.,1.);
        glEnd();
        glDisable(GL_BLEND);
    }
    if(this->yzPlaneCoordinateSystem )
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glColor4f(0,0,0,0.1);
        glBegin(GL_QUADS);
            glVertex3f(0,1.,1.);
            glVertex3f(0.,-1.,1.);
            glVertex3f(0.,-1.,-1.);
            glVertex3f(0.,1.,-1.);
        glEnd();
        glDisable(GL_BLEND);
    }
    if(this->xyPlaneCoordinateSystem )
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glColor4f(0,0,0,0.1);
        glBegin(GL_QUADS);
            glVertex3f(1.,1.,0.);
            glVertex3f(-1.,1.,0.);
            glVertex3f(-1.,-1.,0.);
            glVertex3f(1.,-1.,0.);
        glEnd();
        glDisable(GL_BLEND);
    }
}
//------------------------------------------------------------------------





//---------------------- DRAWING STERE FUNCTION --------------------------
void GLWidget::drawingStere()
{
    drawCube(Stere::centerPoint(0),0.5,this->stereTransperancy,Stere::findStereColor(0));
    drawCube(Stere::centerPoint(1),0.5,this->stereTransperancy,Stere::findStereColor(1));
    drawCube(Stere::centerPoint(2),0.5,this->stereTransperancy,Stere::findStereColor(2));
    drawCube(Stere::centerPoint(3),0.5,this->stereTransperancy,Stere::findStereColor(3));
    drawCube(Stere::centerPoint(4),0.5,this->stereTransperancy,Stere::findStereColor(4));
    drawCube(Stere::centerPoint(5),0.5,this->stereTransperancy,Stere::findStereColor(5));
    drawCube(Stere::centerPoint(6),0.5,this->stereTransperancy,Stere::findStereColor(6));
    drawCube(Stere::centerPoint(7),0.5,this->stereTransperancy,Stere::findStereColor(7));
}
//------------------------------------------------------------------------





//---------------------- DRAWING PLANES FUNCTION --------------------------
void GLWidget::drawingPlanes()
{
    for(unsigned iter=0; iter < this->allPlanes.size(); ++iter)
    {
        Plane plane = this->allPlanes.at(iter);
        QColor colorPlane = plane.getPlaneColor();
        std::vector<Point3D> interPoints = plane.getIntersectionWithCube();

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glColor4f(colorPlane.red() /255.,colorPlane.green() /255.,colorPlane.blue() /255.,this->alphaChannelPlanes);
        glBegin(GL_POLYGON);

        for(unsigned i=0; i < interPoints.size(); ++i)
        {
          //qDebug("it %d point x%lf y %lf z% lf",i,this->interPoints.at(i).x ,this-> interPoints.at(i).y ,this->interPoints.at(i).z);
          glVertex3f(interPoints.at(i).x,interPoints.at(i).y,interPoints.at(i).z);
        }

        glEnd();
        glDisable(GL_BLEND);
    }
}
//------------------------------------------------------------------------





//-------------------------- CUBES FUNCTIONS -----------------------------
void GLWidget::drawCube(Point3D centerPoint, double size, double transparency, QColor color)
{
    this->drawCube(centerPoint.x, centerPoint.y, centerPoint.z,size,transparency,color);
}

void GLWidget::drawCube(double x0, double y0, double z0, double size, double transparency, QColor color)
{
    if(transparency > 1. || transparency < 0.) transparency = 1.;

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glColor4f(color.red()/255.,color.green()/255.,color.blue()/255.,transparency);

    glBegin(GL_TRIANGLES);

        //FRONT
        glVertex3f(x0 + size,y0 - size,z0 + size);
        glVertex3f(x0 - size,y0 - size,z0 + size);
        glVertex3f(x0 + size,y0 + size,z0 + size);

        glVertex3f(x0 - size,y0 - size,z0 + size);
        glVertex3f(x0 - size,y0 + size,z0 + size);
        glVertex3f(x0 + size,y0 + size,z0 + size);

        //RIGHT
        glVertex3f(x0 + size,y0 - size,z0 + size);
        glVertex3f(x0 + size,y0 - size,z0 - size);
        glVertex3f(x0 + size,y0 + size,z0 + size);

        glVertex3f(x0 + size,y0 + size,z0 + size);
        glVertex3f(x0 + size,y0 + size,z0 - size);
        glVertex3f(x0 + size,y0 - size,z0 - size);

        //LEFT
        glVertex3f(x0 - size,y0 - size,z0 + size);
        glVertex3f(x0 - size,y0 - size,z0 - size);
        glVertex3f(x0 - size,y0 + size,z0 + size);

        glVertex3f(x0 - size,y0 + size,z0 + size);
        glVertex3f(x0 - size,y0 + size,z0 - size);
        glVertex3f(x0 - size,y0 - size,z0 - size);

        //BACK
        glVertex3f(x0 - size,y0 + size,z0 - size);
        glVertex3f(x0 - size,y0 - size,z0 - size);
        glVertex3f(x0 + size,y0 + size,z0 - size);

        glVertex3f(x0 + size,y0 - size,z0 - size);
        glVertex3f(x0 - size,y0 - size,z0 - size);
        glVertex3f(x0 + size,y0 + size,z0 - size);

        //UP
        glVertex3f(x0 - size,y0 + size,z0 + size);
        glVertex3f(x0 + size,y0 + size,z0 + size);
        glVertex3f(x0 + size,y0 + size,z0 - size);

        glVertex3f(x0 - size,y0 + size,z0 + size);
        glVertex3f(x0 - size,y0 + size,z0 - size);
        glVertex3f(x0 + size,y0 + size,z0 - size);

        //DOWN
        glVertex3f(x0 + size,y0 - size,z0 + size);
        glVertex3f(x0 - size,y0 - size,z0 + size);
        glVertex3f(x0 + size,y0 - size,z0 - size);

        glVertex3f(x0 - size,y0 - size,z0 + size);
        glVertex3f(x0 + size,y0 - size,z0 - size);
        glVertex3f(x0 - size,y0 - size,z0 - size);

    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}
