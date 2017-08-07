#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand (time (NULL));
    ui->setupUi(this);

    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(false);

    this->trajectoriesDrawn = false;
    this->positionProgess = 0;
    this->coordinateSystemIcon = false;
    this->stereSystemIcon = false;


    connect(ui->startButton,SIGNAL(clicked()), ui->OpenGLWidget,SLOT(startButtonClicked()));
    connect(ui->stopButton ,SIGNAL(clicked()), ui->OpenGLWidget,SLOT(stopButtonClicked()));
    connect(ui->coordinateSystem, SIGNAL(clicked()), ui->OpenGLWidget,SLOT(coordinateSystem()));
    connect(ui->timeSlider, SIGNAL(valueChanged(int)), ui->OpenGLWidget, SLOT(getTimerValue(int)));
    connect(ui->timeSlider, SIGNAL(valueChanged(int)), this,SLOT(setLCDTimer(int)));

    connect(ui->lineWidth, SIGNAL(valueChanged(int)), ui->OpenGLWidget, SLOT(lineWidthChange(int)));


    connect(ui->actionX_axis_up, SIGNAL(triggered()), ui->OpenGLWidget, SLOT(xAxisUp()));
    connect(ui->actionY_axis_up, SIGNAL(triggered()), ui->OpenGLWidget, SLOT(yAxisUp()));
    connect(ui->actionZ_axis_up, SIGNAL(triggered()), ui->OpenGLWidget, SLOT(zAxisUp()));
    connect(ui->OpenGLWidget, SIGNAL(allTrajectoriesDrawn()), this, SLOT(getAllTrajectoriesDrawn()));


    connect(this, SIGNAL(emitRK4Points(std::vector<Point3D>, double)),
            ui->OpenGLWidget, SLOT(getRK4Points(std::vector<Point3D>, double))
            );

    connect(ui->xzPlaneCS, SIGNAL(stateChanged(int)), ui->OpenGLWidget, SLOT(xzPlanePress(int)));
    connect(ui->yzPlaneCS, SIGNAL(stateChanged(int)), ui->OpenGLWidget, SLOT(yzPlanePress(int)));
    connect(ui->xyPlaneCS, SIGNAL(stateChanged(int)), ui->OpenGLWidget, SLOT(xyPlanePress(int)));

    connect(this, SIGNAL(restartOpenGLWidget()), ui->OpenGLWidget, SLOT(restartButtonClicked()));

    connect(ui->showAllStere,SIGNAL(clicked()), ui->OpenGLWidget, SLOT(showAllStere()));

    connect(ui->OpenGLWidget, SIGNAL(emitPosition(int)), this, SLOT(progreessPositionBar(int)));

    connect(ui->transperancy, SIGNAL(valueChanged(double)), ui->OpenGLWidget, SLOT(changeStereTransperancy(double)));
    connect(ui->transperancy, SIGNAL(valueChanged(double)), ui->OpenGLWidget, SLOT(changeStereTransperancy(double)));

    connect(this, SIGNAL(emitPlnesToOpengGL(std::vector<Plane>, double)), ui->OpenGLWidget, SLOT(getAllPlanes(std::vector<Plane>, double)));
    connect(ui->clearPlanes, SIGNAL(clicked()), ui->OpenGLWidget, SLOT(clearAllPlanes()));

    // **************   STATISTICS  **************


    this->pointSetupDialog = NULL;
    initTables();

    this->planesDialog = NULL;

}
MainWindow::~MainWindow()
{
    delete ui;
}
//------------------------------------------------------------------------


//****************************** SLOTS ***********************************


//--------------------------- MENU BAR FUNCTIONS -------------------------
void MainWindow::on_actionExit_triggered()
{
    this->close();
}
void MainWindow::on_actionRestart_triggered()
{
    on_restartButton_clicked();
}
void MainWindow::on_actionAbout_triggered()
{
    AboutDialog aboutDialog;
    aboutDialog.setModal(true);
    aboutDialog.exec();
}
//------------------------------------------------------------------------


//************************ VISUALIZATION SLOTS ***************************


//---------------------- START/STOP/RESTART BUTTONS ----------------------
void MainWindow::on_startButton_clicked()
{
   if(this->trajectoriesDrawn)
   {
        QMessageBox::warning(this, "Warrning", "All trajectories are already drawn");
   }
   else
   {
       ui->stopButton->setEnabled(true);
       ui->startButton->setEnabled(false);

       ui->hValue->setEnabled(false);

       ui->trajectoriesButton->setEnabled(false);

       emit emitRK4Points(this->allPoints, ui->hValue->value());
   }
}
void MainWindow::on_stopButton_clicked()
{
    ui->stopButton->setEnabled(false);
    ui->startButton->setEnabled(true);
}
void MainWindow::on_restartButton_clicked()
{
    this->allPoints.clear();
    this->trajectoriesDrawn = false;

    ui->stopButton->setEnabled(false);
    ui->startButton->setEnabled(false);

    ui->timeSlider->setValue(10);

    ui->lineWidth->setValue(1);

    ui->trajectoriesButton->setEnabled(true);
    ui->hValue->setEnabled(true);
    ui->hValue->setValue(0.05);
    ui->xyPlaneCS->setChecked(false);
    ui->xzPlaneCS->setChecked(false);
    ui->yzPlaneCS->setChecked(false);

    this->positionProgess = 0;
    ui->progressBar->setValue(0);

    ui->transperancy->setValue(0.3);

    if(this->coordinateSystemIcon)
    {
        ui->coordinateSystem->setIcon(QIcon(":/icon/off.png"));
        ui->coordinateSystem->setText(" OFF ");
        this->coordinateSystemIcon =  false;
    }
    if(this->stereSystemIcon)
    {
        ui->showAllStere->setIcon(QIcon(":/icon/off.png"));
        ui->showAllStere->setText(" OFF ");
        this->stereSystemIcon =  false;
    }

    emit restartOpenGLWidget();
}
//------------------------------------------------------------------------





//------------------------ TRAJECTORIES PROPERTIES -----------------------

void MainWindow::on_trajectoriesButton_clicked()
{
    TrajectoriesDialog trajectoriesDialog(this->allPoints,this);
    connect(&trajectoriesDialog, SIGNAL(appendPoints(std::vector<Point3D>)), this, SLOT(getAppendedPoints(std::vector<Point3D>)));
    trajectoriesDialog.setMinimumHeight(600);
    trajectoriesDialog.setMinimumWidth(650);
    trajectoriesDialog.setModal(true);
    trajectoriesDialog.exec();
}
void MainWindow::getAppendedPoints(std::vector<Point3D> allPoints)
{
    this->allPoints.clear();
    while(allPoints.size() > 0)
    {
        this->allPoints.push_back(allPoints.back());
        allPoints.pop_back();
    } 
    this->allPoints.size() > 0 ?  ui->startButton->setEnabled(true) :  ui->startButton->setEnabled(false);
}

void MainWindow::getAllTrajectoriesDrawn()
{
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    if(!this->trajectoriesDrawn){
        QMessageBox::information(this,"","All trajectories have been drawn");
    }
    this->trajectoriesDrawn = true;
}
//------------------------------------------------------------------------





//------------------------- PROGRESS PROPERTIES --------------------------
void MainWindow::progreessPositionBar(int position)
{
    if(this->positionProgess < position)
    {
        this->positionProgess = position;
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(this->positionProgess);
    }
    ui->progressBar->setValue(this->positionProgess -position);
}
void MainWindow::setLCDTimer(int value)
{
    ui->lcdTimer->display(value/20.);
}
//------------------------------------------------------------------------





//-------------------------- PLANES PROPERTIES ---------------------------
void MainWindow::on_planes_clicked()
{
    if(this->planesDialog == NULL)
    {
        this->planesDialog = new PlanesDialog(this);
        this->planesDialog->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        connect(planesDialog, SIGNAL(finished(int)), this, SLOT(planesDialog_destroy()));
        connect(planesDialog, SIGNAL(emitPlanes(std::vector<Plane>,double)),this, SLOT(getAllPlanes(std::vector<Plane>,double)));
        this->planesDialog->show();
    }
}
void MainWindow::getAllPlanes(std::vector<Plane> planes, double alphaChannel)
{
    emit emitPlnesToOpengGL(planes,alphaChannel);
}
void MainWindow::planesDialog_destroy()
{
    this->planesDialog = NULL;
}
//------------------------------------------------------------------------





//----------------- DISPLAY ON/OFF COORDINATE SYSTEM ---------------------
void MainWindow::on_coordinateSystem_clicked()
{
    if(coordinateSystemIcon)
    {
        ui->coordinateSystem->setIcon(QIcon(":/icon/off.png"));
        ui->coordinateSystem->setText(" OFF ");
    }
    else
    {
        ui->coordinateSystem->setIcon(QIcon(":/icon/on.png"));
        ui->coordinateSystem->setText(" ON  ");
    }

    this->coordinateSystemIcon = !this->coordinateSystemIcon;
}
//------------------------------------------------------------------------





//---------------------- SNAPSHOTS IMAGE PROPERTIES ----------------------
void MainWindow::on_snapshotImage_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Image files (*.jpg *.png)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    connect(&dialog, SIGNAL(fileSelected(QString)), this, SLOT(saveSnapshotImage(QString)));
    dialog.exec();
}
void MainWindow::saveSnapshotImage(QString filename)
{
    bool jpgFile  = filename.endsWith(".jpg");
    bool pngFile  = filename.endsWith(".png");
    if(!(jpgFile || pngFile))
    {
       filename = filename + ".jpg";
    }
    QImage img = ui->OpenGLWidget->grabFrameBuffer();
    img.save(filename);
}
//------------------------------------------------------------------------





//---------------------- DISPLAY ON/OFF STEREs ----------------------
void MainWindow::on_showAllStere_clicked()
{
    if(stereSystemIcon)
    {
        ui->showAllStere->setIcon(QIcon(":/icon/off.png"));
        ui->showAllStere->setText(" OFF ");

    }
    else
    {
        ui->showAllStere->setIcon(QIcon(":/icon/on.png"));
        ui->showAllStere->setText(" ON  ");
    }

    this->stereSystemIcon = !this->stereSystemIcon;
}

//------------------------------------------------------------------------


//*********************** STATISTICS SLOTS ********************************


//--------------------------- POINTS PROPERTIES --------------------------
void MainWindow::on_pointSetupButton_clicked()
{
    if(this->pointSetupDialog == NULL)
    {
        this->pointSetupDialog = new StatisticsPointSetupDialog(this);
        this->pointSetupDialog->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        connect(pointSetupDialog, SIGNAL(finished(int)), this, SLOT(pointSetupButton_destroy()));
        connect(pointSetupDialog, SIGNAL(emitAmountPoint(int, int, double *, bool)), this, SLOT(getPointAmountFromStatistics(int, int, double *, bool) ));
        this->pointSetupDialog->show();
    }
}
void MainWindow::getPointAmountFromStatistics(int amoutOfPoints, int randomOption, double *pointRange, bool run)
{
    ui->addingPointsProgressBar->setMinimum(0);
    ui->addingPointsProgressBar->setMaximum(amoutOfPoints);

    for(int i=0; i < amoutOfPoints; ++i)
    {
        Point3D randPoint;

        if(randomOption == RANGE_OPTION)
        {
            randPoint = Point3D::randPoint(pointRange[0],pointRange[1],
                                       pointRange[2],pointRange[3],
                                       pointRange[4],pointRange[5]);
        }
        else
        {
            bool foundProperStere =  true;
            int randStere = -1;

            while(foundProperStere)
            {
                randStere = std::rand() % 8 ;
                foundProperStere = pointRange[randStere] != 0. ? false : true;
            }

            randPoint = Stere::getRandomStere(randStere);
        }

        QTableWidgetItem *item =  new QTableWidgetItem(Stere::getStereString(randPoint));

        QColor stereColor = Stere::findStereColor(randPoint);
        stereColor.setAlpha(150);
        item->setBackgroundColor(stereColor);

        ui->pointsTable->insertRow(ui->pointsTable->rowCount());
        ui->pointsTable->setItem(ui->pointsTable->rowCount() - 1, 0, item);
        ui->pointsTable->setItem(ui->pointsTable->rowCount() - 1, 1, new QTableWidgetItem(QString::number(randPoint.x)));
        ui->pointsTable->setItem(ui->pointsTable->rowCount() - 1, 2, new QTableWidgetItem(QString::number(randPoint.y)));
        ui->pointsTable->setItem(ui->pointsTable->rowCount() - 1, 3, new QTableWidgetItem(QString::number(randPoint.z)));

        this->statisticsPoints.push_back(randPoint);

        ui->addingPointsProgressBar->setValue(i+1);
    }
    ui->pointsTable->scrollToBottom();
    delete [] pointRange;

    if(run)
    {
        this->pointSetupDialog->close();
        this->pointSetupDialog = NULL;
        on_countDataButton_clicked();
    }
}
void MainWindow::pointSetupButton_destroy()
{
    this->pointSetupDialog = NULL;
}
//------------------------------------------------------------------------





//--------------------- COUNT STATISTICS FUNCTION ------------------------
void MainWindow::on_countDataButton_clicked()
{
    if(this->statisticsPoints.size() > 0)
    {
        ui->pointCountingBar->setMinimum(0);
        ui->pointCountingBar->setMaximum(this->statisticsPoints.size());

        initTables(1);

    }
    for(unsigned i=0; i < this->statisticsPoints.size(); ++i)
    {
        Point3D currentPoint = this->statisticsPoints.at(i);

        std::vector<Point3D> *rk4Points = new std::vector<Point3D>;
        RK4 obj(currentPoint,ui->hValueStatistics->value());
        obj.countRK4(rk4Points);

        StatOutput output(currentPoint,rk4Points->back(),ui->hValueStatistics->value(),rk4Points->size());
        this->outputStats.push_back(output);

        displyStandartTable(output, i);

        ui->pointCountingBar->setValue(i+1);
        delete rk4Points;
    }

    if(this->statisticsPoints.size() > 0)displayStereTable();

}
//------------------------------------------------------------------------





//--------------------- CLEAR STATISTICS FUNCTION ------------------------
void MainWindow::on_clearPointsButton_clicked()
{

    initTables();

    this->statisticsPoints.clear();
    this->outputStats.clear();

    ui->pointCountingBar->setValue(0);
    ui->addingPointsProgressBar->setValue(0);
}
//------------------------------------------------------------------------





//---------------------- SAVE FILE TO XML FUNCTIONS ------------------------
void MainWindow::on_saveDataButton_clicked()
{
    QFileDialog dialog(this);
   // dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("XML files (*.xml)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    connect(&dialog, SIGNAL(fileSelected(QString)), this, SLOT(saveData(QString)));
    dialog.exec();

}
void MainWindow::saveData(QString filename)
{
    bool xmlFile  = filename.endsWith(".xml");
    if(!xmlFile)
    {
       filename = filename + ".xml";
    }
    std::string newFileName = filename.toUtf8().constData();
    const int sizeStere = 9;

    using boost::property_tree::ptree;
    ptree xmlRoot;

    if(ui->standartOptionOutput->isChecked())
    {
        xmlRoot.put("heiderbalance.N",this->outputStats.size());

        for(unsigned i=0; i < this->outputStats.size(); ++i)
        {
            ptree xmlPoint;
            StatOutput output = this->outputStats.at(i);

            xmlPoint.put("<xmlattr>.n",i);
            xmlPoint.put("h",output.h);
            xmlPoint.put("size",output.size);

            xmlPoint.put("firstPoint.x",output.firstPoint.x);
            xmlPoint.put("firstPoint.y",output.firstPoint.y);
            xmlPoint.put("firstPoint.z",output.firstPoint.z);

            xmlPoint.put("lastPoint.x",output.lastPoint.x);
            xmlPoint.put("lastPoint.y",output.lastPoint.y);
            xmlPoint.put("lastPoint.z",output.lastPoint.z);

            xmlRoot.add_child("heiderbalance.point",xmlPoint);

        }
    }
    else if(ui->stereOptionOutput->isChecked())
    {

        for(unsigned i=0 ; i < sizeStere; ++i)
        {
            ptree xmlStere;
            xmlStere.put("<xmlattr>.name",Stere::getStereString(i).toUtf8().constData());
            xmlStere.put("<xmlattr>.value",i);
            xmlStere.put("percentage",this->outputStatsStere[i].percentage);
            xmlStere.put("allPoints",this->outputStatsStere[i].allPoints);
            xmlStere.put("reachPoints.n",this->outputStatsStere[i].reachPoints);

            for(unsigned j=0 ; j < sizeStere; ++j)
            {
                ptree xmlStereFrom;
                xmlStereFrom.put("<xmlattr>.name",Stere::getStereString(j).toUtf8().constData());
                xmlStereFrom.put("<xmlattr>.value",j);
                xmlStereFrom.put("",this->outputStatsStere[i].fromStere[j]);
                xmlStere.add_child("reachPoints.from",xmlStereFrom);
            }


            xmlRoot.add_child("heiderbalance.stere",xmlStere);
        }
    }

    write_xml(newFileName, xmlRoot);
}
//------------------------------------------------------------------------


//************************** COMMON SLOTS ********************************


//------------------------ CHANGE TAB FUNCTIONS --------------------------

void MainWindow::on_mainTableWindow_currentChanged(int index)
{
    if( this->planesDialog != NULL)
    {
        this->planesDialog->close();
        this->planesDialog = NULL;
    }
}
//------------------------------------------------------------------------


//************************ PRIVATE FUNCTIONS *****************************


//------------------ INIT STATISTICS TABLES FUNCTION ---------------------
void MainWindow::initTables(int type)
{
    if(!type)
    {
        ui->pointsTable->clear();
        ui->pointsTable->setRowCount(0);
        QStringList pointsHeader;
        pointsHeader << "Stere" << "x " << "y "<< "z ";

        ui->pointsTable->setColumnCount(4);
        ui->pointsTable->setColumnWidth(0,70);
        ui->pointsTable->setHorizontalHeaderLabels(pointsHeader);
    }

    ui->standartTable->clear();
    ui->standartTable->setRowCount(0);

    QStringList standartStatsHeader;
    standartStatsHeader << "Nr" << "h" << "size " << "first point \n (x,y,z)"<<"first\n stere "<< "last point \n (x,y,z)"<<"last\n stere";

    ui->standartTable->setColumnCount(7);
    ui->standartTable->setColumnWidth(0,35);
    ui->standartTable->setColumnWidth(1,45);
    ui->standartTable->setColumnWidth(2,50);
    ui->standartTable->setColumnWidth(3,220);
    ui->standartTable->setColumnWidth(4,70);
    ui->standartTable->setColumnWidth(6,70);
    ui->standartTable->setHorizontalHeaderLabels(standartStatsHeader);
    ui->standartTable->verticalHeader()->setVisible(false);

    ui->stereTable->clear();
    ui->stereTable->setRowCount(0);

    QStringList stereTableHeader;
    stereTableHeader << "Nr" << "Stere" << "Points" << "All points" << "Percentage"
                    << "From \n" + Stere::getStereString(0)
                    << "From \n" + Stere::getStereString(1)
                    << "From \n" + Stere::getStereString(2)
                    << "From \n" + Stere::getStereString(3)
                    << "From \n" + Stere::getStereString(4)
                    << "From \n" + Stere::getStereString(5)
                    << "From \n" + Stere::getStereString(6)
                    << "From \n" + Stere::getStereString(7)
                    << "From \n" + Stere::getStereString(8);
    ui->stereTable->setColumnCount(14);
    ui->stereTable->setColumnWidth(0,35);
    ui->stereTable->setColumnWidth(1,70);
    ui->stereTable->setColumnWidth(2,65);
    ui->stereTable->setColumnWidth(3,85);
    ui->stereTable->setColumnWidth(5,70);
    ui->stereTable->setColumnWidth(6,70);
    ui->stereTable->setColumnWidth(7,70);
    ui->stereTable->setColumnWidth(8,70);
    ui->stereTable->setColumnWidth(9,70);
    ui->stereTable->setColumnWidth(10,70);
    ui->stereTable->setColumnWidth(11,70);
    ui->stereTable->setColumnWidth(12,70);
    ui->stereTable->setColumnWidth(13,70);
    ui->stereTable->setHorizontalHeaderLabels(stereTableHeader);

    ui->stereTable->verticalHeader()->setVisible(false);

    this->outputStats.clear();
}
//------------------------------------------------------------------------




//--------------------- STANDART TABLE FUNCTION -------------------------
void MainWindow::displyStandartTable(StatOutput output, unsigned number)
{
    QTableWidgetItem *firstPoint =  new QTableWidgetItem(
                QString(
                    QString::number(output.firstPoint.x) + " " +
                    QString::number(output.firstPoint.y) + " " +
                    QString::number(output.firstPoint.z)
                    )
                );
    QTableWidgetItem *firstStere =  new QTableWidgetItem(Stere::getStereString(output.firstStere));
    output.firstColor.setAlpha(150);
    firstStere->setBackgroundColor(output.firstColor);

    QTableWidgetItem *lastPoint =  new QTableWidgetItem(
                QString(
                    QString::number(output.lastPoint.x) + " " +
                    QString::number(output.lastPoint.y) + " " +
                    QString::number(output.lastPoint.z)
                    )
                );
    QTableWidgetItem *lastStere =  new QTableWidgetItem(Stere::getStereString(output.lastStere));
    output.lastColor.setAlpha(150);
    lastStere->setBackgroundColor(output.lastColor);

    QTableWidgetItem *pItem = new QTableWidgetItem();
    pItem->setCheckState(Qt::Checked);

    ui->standartTable->insertRow(ui->standartTable->rowCount());
    ui->standartTable->setItem(ui->standartTable->rowCount() - 1, 0, new QTableWidgetItem(QString::number(number + 1)));
    ui->standartTable->setItem(ui->standartTable->rowCount() - 1, 1, new QTableWidgetItem(QString::number(output.h)));
    ui->standartTable->setItem(ui->standartTable->rowCount() - 1, 2, new QTableWidgetItem(QString::number(output.size)));
    ui->standartTable->setItem(ui->standartTable->rowCount() - 1, 3, firstPoint);
    ui->standartTable->setItem(ui->standartTable->rowCount() - 1, 4, firstStere);
    ui->standartTable->setItem(ui->standartTable->rowCount() - 1, 5, lastPoint);
    ui->standartTable->setItem(ui->standartTable->rowCount() - 1, 6, lastStere);
}
//------------------------------------------------------------------------




//----------------------- STERE TABLE FUNCTION ---------------------------
void MainWindow::displayStereTable()
{
    const int sizeStere = 9;

    //reset array
    int stats[sizeStere][sizeStere];
    for(unsigned i=0; i < sizeStere; ++i)
    {
        for(unsigned j=0; j < sizeStere; ++j) stats[i][j] = 0;
    }

    // finding stats output
    for(unsigned i=0; i < this->outputStats.size(); ++i)
    {
        StatOutput nextOutputElement =  this->outputStats.at(i);
        stats[nextOutputElement.lastStere][nextOutputElement.firstStere]++;
    }

    //dispaly stats
    for(unsigned i=0; i < sizeStere; ++i)
    {
        QTableWidgetItem *stere =  new QTableWidgetItem(Stere::getStereString(i));
        QColor stereColor = Stere::findStereColor(i);
        stereColor.setAlpha(150);
        stere->setBackgroundColor(stereColor);


        int sumPerStere = 0;
        for(unsigned j=0 ; j < sizeStere; ++j) sumPerStere += stats[i][j];

        double percentage = sumPerStere / (double) this->outputStats.size() * 100.0;

        ui->stereTable->insertRow(ui->stereTable->rowCount());
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 0, new QTableWidgetItem(QString::number(i)));
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 1, stere);
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 2, new QTableWidgetItem(QString::number(sumPerStere)));
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 3, new QTableWidgetItem(QString::number(this->outputStats.size())));
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 4, new QTableWidgetItem(QString::number(percentage)+"%"));
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 5, new QTableWidgetItem(QString::number(stats[i][0])));
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 6, new QTableWidgetItem(QString::number(stats[i][1])));
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 7, new QTableWidgetItem(QString::number(stats[i][2])));
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 8, new QTableWidgetItem(QString::number(stats[i][3])));
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 9, new QTableWidgetItem(QString::number(stats[i][4])));
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 10, new QTableWidgetItem(QString::number(stats[i][5])));
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 11, new QTableWidgetItem(QString::number(stats[i][6])));
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 12, new QTableWidgetItem(QString::number(stats[i][7])));
        ui->stereTable->setItem(ui->stereTable->rowCount() - 1, 13, new QTableWidgetItem(QString::number(stats[i][8])));

        this->outputStatsStere[i].reachPoints = sumPerStere;
        this->outputStatsStere[i].allPoints = this->outputStats.size();
        this->outputStatsStere[i].percentage = percentage;
        for(unsigned j=0 ; j < sizeStere; ++j) this->outputStatsStere[i].fromStere[j] = stats[i][j];

    }
}


void MainWindow::on_colorsStere_clicked()
{
    StereColorsDialog stereColorDialog;
    stereColorDialog.setModal(true);
    stereColorDialog.exec();
}

