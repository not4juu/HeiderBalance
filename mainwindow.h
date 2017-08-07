#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "point3d.h"
#include "statisticspointsetupdialog.h"
#include "trajectoriesdialog.h"
#include "sterecolorsdialog.h"
#include "planesdialog.h"
#include "statoutput.h"
#include "statstereoutput.h"
#include "aboutdialog.h"
#include "plane.h"
#include <vector>
#include <QFileDialog>

#include <time.h>
#include <cstdlib>
#include <QMessageBox>
#include <QTime>

#include <set>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

    void emitRK4Points(std::vector<Point3D> allPoints, double h);
    void restartOpenGLWidget();
    void emitPlnesToOpengGL(std::vector<Plane>, double);

private slots:

    void on_actionRestart_triggered();
    void on_actionAbout_triggered();
    void on_actionExit_triggered();

//************************ VISUALIZATION SLOTS ***************************
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_restartButton_clicked();

    void on_trajectoriesButton_clicked();
    void getAppendedPoints(std::vector<Point3D> allPoints);
    void getAllTrajectoriesDrawn();

    void progreessPositionBar(int);
    void setLCDTimer(int);

    void on_planes_clicked();
    void getAllPlanes(std::vector<Plane>, double);
    void planesDialog_destroy();

    void on_coordinateSystem_clicked();

    void on_snapshotImage_clicked();
    void saveSnapshotImage(QString);

    void on_showAllStere_clicked();

//*********************** STATISTICS SLOTS ********************************
    void on_pointSetupButton_clicked();
    void getPointAmountFromStatistics(int, int, double *, bool);
    void pointSetupButton_destroy();

    void on_countDataButton_clicked();

    void on_clearPointsButton_clicked();

    void on_saveDataButton_clicked();
    void saveData(QString filename);

    void on_mainTableWindow_currentChanged(int index);

    void on_colorsStere_clicked();


private:

    Ui::MainWindow *ui;
    std::vector<Point3D> allPoints;

    bool trajectoriesDrawn;
    int positionProgess;
    bool coordinateSystemIcon;
    bool stereSystemIcon;

    StatisticsPointSetupDialog *pointSetupDialog;
    PlanesDialog *planesDialog;

    enum{ RANGE_OPTION, STERE_OPTION};
    std::vector<Point3D> statisticsPoints;
    std::vector<StatOutput> outputStats;
    StatStereOutput outputStatsStere [9];

    void initTables(int type=0);
    void displyStandartTable(StatOutput output, unsigned number);
    void displayStereTable();



};

#endif // MAINWINDOW_H
