#include "trajectoriesdialog.h"
#include "ui_trajectoriesdialog.h"
#include <QMessageBox>

TrajectoriesDialog::TrajectoriesDialog(std::vector<Point3D> allPoints, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrajectoriesDialog)
{
    ui->setupUi(this);

    ui->stereFrame->setVisible(false);

    this->allLayouts = new  std::vector<QHBoxLayout *>;
    this->allSpinBoxes = new std::vector<std::vector<QDoubleSpinBox *> >;
    this->allLabels = new std::vector<std::vector<QLabel *> >;
    this->checkBoxes = new std::vector<QCheckBox *>;
    this->allColorButtons = new std::vector<QPushButton *> ;

    this->chosenSolidColor = ColorProperties::DEFAULT_POINT_COLOR;

    while(allPoints.size() > 0)
    {
        Point3D point =  allPoints.back();
        allPoints.pop_back();
        addPoint(OLD_POINT,point.x,point.y,point.z,point.rgb);
    }

    ui->upFrontRightStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("upFrontRightStere")));
    ui->upFrontLeftStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("upFrontLeftStere")));

    ui->upBackRightStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("upBackRightStere")));
    ui->upBackLeftStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("upBackLeftStere")));


    ui->downFrontRightStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("downFrontRightStere")));
    ui->downFrontLeftStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("downFrontLeftStere")));

    ui->downBackRightStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("downBackRightStere")));
    ui->downBackLeftStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("downBackLeftStere")));


    ui->solidColorButton->setStyleSheet(convertToStyleSheet("QPushButton", ColorProperties::DEFAULT_POINT_COLOR));
}

TrajectoriesDialog::~TrajectoriesDialog()
{
    delete this->allLayouts;
    delete this->allSpinBoxes ;
    delete this->allLabels;
    delete this->checkBoxes;
    delete this->allColorButtons;
    delete ui;
}
//------------------------------------------------------------------------




//----------------------ADD/DELETE/SAVE Points----------------------------
void TrajectoriesDialog::on_addTrajectoryButton_clicked()
{
    addPoint(NEW_POINT);
}

void TrajectoriesDialog::on_deleteTrajectoryButton_clicked()
{
    if(!this->allLayouts->empty() ){
       QHBoxLayout *lastPoints = this->allLayouts->back();
       this->allLayouts->pop_back();
       delete lastPoints;

       QCheckBox *checkBox = this->checkBoxes->back();
       this->checkBoxes->pop_back();
       delete checkBox;

       QPushButton *colorButton = this->allColorButtons->back();
       this->allColorButtons->pop_back();
       delete colorButton;

       std::vector<QDoubleSpinBox *> spinBox = this->allSpinBoxes->back();
       this->allSpinBoxes->pop_back();
       {
            QDoubleSpinBox *z = spinBox.back();
            spinBox.pop_back();
            delete z;

            QDoubleSpinBox *y = spinBox.back();
            spinBox.pop_back();
            delete y;

            QDoubleSpinBox *x = spinBox.back();
            spinBox.pop_back();
            delete x;

       }
       std::vector<QLabel *> labels = this->allLabels->back();
       this->allLabels->pop_back();
       {

           QLabel *zLabel = labels.back();
           labels.pop_back();
           delete zLabel;

           QLabel *yLabel = labels.back();
           labels.pop_back();
           delete yLabel;

           QLabel *xLabel = labels.back();
           labels.pop_back();
           delete xLabel;
       }
    }
}


void TrajectoriesDialog::addPoint(bool newPoint, double xPoint, double yPoint, double zPoint, QColor rgbPoint)
{
    QDoubleSpinBox *x =  new QDoubleSpinBox(this);
    QDoubleSpinBox *y =  new QDoubleSpinBox(this);
    QDoubleSpinBox *z =  new QDoubleSpinBox(this);

    setPointsProperties(x);
    setPointsProperties(y);
    setPointsProperties(z);

    if(newPoint == OLD_POINT)
    {
        x->setValue(xPoint);
        y->setValue(yPoint);
        z->setValue(zPoint);
    }

    std::vector<QDoubleSpinBox *> spinBox;

    spinBox.push_back(x);
    spinBox.push_back(y);
    spinBox.push_back(z);

    this->allSpinBoxes->push_back(spinBox);

    QLabel *xLabel = new QLabel(this);
    QLabel *yLabel = new QLabel(this);
    QLabel *zLabel = new QLabel(this);

    xLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    yLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    zLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    xLabel->setMaximumWidth(40);
    yLabel->setMaximumWidth(20);
    zLabel->setMaximumWidth(20);


    QPushButton *colorButton = new QPushButton(this);

    colorButton->setStyleSheet(convertToStyleSheet(
                                   "QPushButton",
                                    QColor(
                                        rgbPoint.red(),
                                        rgbPoint.green(),
                                        rgbPoint.blue()
                                        ))
                               );

    colorButton->setMaximumHeight(15);
    colorButton->setMaximumWidth(15);

    connect(colorButton, SIGNAL(clicked()),this, SLOT(changeChosenColor()));
    this->allColorButtons->push_back(colorButton);


    std::vector<QLabel *> labels;
    labels.push_back(xLabel);
    labels.push_back(yLabel);
    labels.push_back(zLabel);

    this->allLabels->push_back(labels);

    xLabel->setText(QString::number(this->allLabels->size())+" x:");
    yLabel->setText("y:");
    zLabel->setText("z:");

    QCheckBox *checkBox = new QCheckBox(this);
    checkBox->setMaximumWidth(20);
    this->checkBoxes->push_back(checkBox);


    QHBoxLayout *layoutHorizontal = new QHBoxLayout();
    layoutHorizontal->addWidget(checkBox);
    layoutHorizontal->addWidget(colorButton);
    layoutHorizontal->addWidget(xLabel);
    layoutHorizontal->addWidget(x);
    layoutHorizontal->addWidget(yLabel);
    layoutHorizontal->addWidget(y);
    layoutHorizontal->addWidget(zLabel);
    layoutHorizontal->addWidget(z);

    this->allLayouts->push_back(layoutHorizontal);
    ui->pointsLayout->addLayout(layoutHorizontal);
}



void TrajectoriesDialog::setPointsProperties(QDoubleSpinBox *box)
{
    box->setButtonSymbols(QAbstractSpinBox::NoButtons);
    box->setRange(-0.999999,0.999999);
    box->setSingleStep(0.005);
    box->setDecimals(7);
    box->setSpecialValueText(" ");
    box->setValue(box->minimum());
    box->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void TrajectoriesDialog::on_saveTrajetories_clicked()
{
    std::vector<Point3D> allPoints;

    bool allPointsSelected = true;

    for(unsigned iter = 0; iter < this->allSpinBoxes->size(); ++iter)
    {
        std::vector<QDoubleSpinBox *> spinBox  = this->allSpinBoxes->at(iter);

        QDoubleSpinBox * x = spinBox.at(0);
        QDoubleSpinBox * y = spinBox.at(1);
        QDoubleSpinBox * z = spinBox.at(2);

        QPushButton *colorButton = this->allColorButtons->at(iter);

        if(x->value() == x->minimum() || y->value() == y->minimum() || z->value() == z->minimum())
        {
            allPointsSelected = false;
        }

        QColor col = colorButton->palette().color(QPalette::Background);

        Point3D point(x->value(), y->value(),z->value(),col);

        allPoints.push_back(point);
    }

    if(allPointsSelected)
    {
        //QMessageBox::information(this,"Save Points","Points have been saved");
        emit appendPoints(allPoints);
        this->close();
    }
    else
    {
        QMessageBox::warning(this,"Important warning","Please select all points");
    }
}
//----------------------------------------------------------------------------





//----------------------RANDOM POINTS FUNCTIONS--------------------------------

void TrajectoriesDialog::on_buttonRanomPoints_clicked()
{
    if(ui->randomAll->isChecked())this->randomAllPoints();
    if(ui->randomChosen->isChecked())this->randomChosenPoints();
    if(ui->colorAutomaticallyButton->isChecked())on_buttonColorPoints_clicked();
}

void TrajectoriesDialog::on_pointsRangeBox_currentIndexChanged(int index)
{
   switch(index)
   {
    case 0:
       ui->defineRangeFrame->setVisible(true);
       ui->stereFrame->setVisible(false);
       break;
   case 1:
        ui->defineRangeFrame->setVisible(false);
        ui->stereFrame->setVisible(true);
       break;
   }
}


void TrajectoriesDialog::randomAllPoints()
{
    for(unsigned iter = 0; iter < this->allSpinBoxes->size(); ++iter)
    {
        std::vector<QDoubleSpinBox *> spinBox  = this->allSpinBoxes->at(iter);

        Point3D randPoint;

        switch (ui->pointsRangeBox->currentIndex())
        {
        case 0:
            randPoint = Point3D::randPoint(ui->defineXMin->value(),ui->defineXMax->value(),
                                                   ui->defineYMin->value(),ui->defineYMax->value(),
                                                   ui->defineZMin->value(),ui->defineZMax->value());
            spinBox.at(0)->setValue(randPoint.x);
            spinBox.at(1)->setValue(randPoint.y);
            spinBox.at(2)->setValue(randPoint.z);
            break;
        case 1:
             randPoint = randomStere();
             spinBox.at(0)->setValue(randPoint.x);
             spinBox.at(1)->setValue(randPoint.y);
             spinBox.at(2)->setValue(randPoint.z);
            break;
        }
    }
}

void TrajectoriesDialog::randomChosenPoints()
{
    for(unsigned iter = 0; iter < this->allSpinBoxes->size(); ++iter)
    {
        std::vector<QDoubleSpinBox *> spinBox  = this->allSpinBoxes->at(iter);

        QCheckBox * checkBox = this->checkBoxes->at(iter);

        if(checkBox->isChecked()){

            Point3D randPoint;
            switch (ui->pointsRangeBox->currentIndex())
            {
            case 0:
                randPoint = Point3D::randPoint(ui->defineXMin->value(),ui->defineXMax->value(),
                                               ui->defineYMin->value(),ui->defineYMax->value(),
                                               ui->defineZMin->value(),ui->defineZMax->value());
                spinBox.at(0)->setValue(randPoint.x);
                spinBox.at(1)->setValue(randPoint.y);
                spinBox.at(2)->setValue(randPoint.z);

                break;
            case 1:
                 randPoint = randomStere();
                 spinBox.at(0)->setValue(randPoint.x);
                 spinBox.at(1)->setValue(randPoint.y);
                 spinBox.at(2)->setValue(randPoint.z);
                break;
            }
        }
    }
}

Point3D TrajectoriesDialog::randomStere()
{
    Point3D randPoint;
    bool clickedStere[8];
    clickedStere[0] = ui->upFrontRightStere->isChecked();
    clickedStere[1] = ui->upFrontLeftStere->isChecked();

    clickedStere[2] = ui->upBackRightStere->isChecked();
    clickedStere[3] = ui->upBackLeftStere->isChecked();


    clickedStere[4] = ui->downFrontRightStere->isChecked();
    clickedStere[5] = ui->downFrontLeftStere->isChecked();

    clickedStere[6] = ui->downBackRightStere->isChecked();
    clickedStere[7] = ui->downBackLeftStere->isChecked();

    int randStere = -1;
    bool foundProperStere =  true;

    for(int i=0; i < 8 ; ++i)
    {
        if(clickedStere[i])foundProperStere=false;
    }

    while(!foundProperStere)
    {
        randStere = std::rand() % 8 ;
        foundProperStere = clickedStere[randStere];
    }
    randPoint = Stere::getRandomStere(randStere);
    return randPoint;
}
//----------------------------------------------------------------------------





//------------------------COLOR FUNCTIONS-------------------------------------------

void TrajectoriesDialog::on_buttonColorPoints_clicked()
{
    if(ui->solidColor->isChecked()) this->solidColor();
    if(ui->stereColor->isChecked()) this->stereColor();
    if(ui->randomColor->isChecked()) this->randomColor();
}

void TrajectoriesDialog::solidColor()
{
    for(unsigned iter = 0; iter < this->allColorButtons->size(); ++iter)
    {
        QPushButton *colorButton = this->allColorButtons->at(iter);

        colorButton->setStyleSheet(convertToStyleSheet("QPushButton", this->chosenSolidColor) );
    }
}

void TrajectoriesDialog::stereColor()
{
    bool allPointsSelected = true;

   // CHECK IF ALL POINTS ARE NOT SELECTED WE CAN NOT CHOSE PROPER COLOR
    for(unsigned iter = 0; iter < this->allSpinBoxes->size(); ++iter)
    {
        std::vector<QDoubleSpinBox *> spinBox  = this->allSpinBoxes->at(iter);

        QDoubleSpinBox * x = spinBox.at(0);
        QDoubleSpinBox * y = spinBox.at(1);
        QDoubleSpinBox * z = spinBox.at(2);

        if(x->value() == x->minimum() || y->value() == y->minimum() || z->value() == z->minimum())
        {
            allPointsSelected = false;
        }
    }

    // IF ALL POINTS ARE SELECTED WE COLOR THEM BY CELL
    if(allPointsSelected)
    {

        for(unsigned iter = 0; iter < this->allSpinBoxes->size(); ++iter)
        {
           std::vector<QDoubleSpinBox *> spinBox  = this->allSpinBoxes->at(iter);

           QDoubleSpinBox * x = spinBox.at(0);
           QDoubleSpinBox * y = spinBox.at(1);
           QDoubleSpinBox * z = spinBox.at(2);

           QPushButton *colorButton = this->allColorButtons->at(iter);

           Point3D sterePoint(x->value(),y->value(),z->value());

           QColor stereColor = Stere::findStereColor(sterePoint);

           colorButton->setStyleSheet(convertToStyleSheet("QPushButton",stereColor));
        }
    }
    else
    {
        QMessageBox::warning(this,"Important warning","Please select all points");
    }
}

void TrajectoriesDialog::randomColor()
{
    for(unsigned iter = 0; iter < this->allColorButtons->size(); ++iter)
    {
        QPushButton *colorButton = this->allColorButtons->at(iter);

        colorButton->setStyleSheet( convertToStyleSheet(
                                       "QPushButton",
                                        QColor(
                                            (std::rand() / (RAND_MAX+1.) * 255),
                                            (std::rand() / (RAND_MAX+1.) * 255),
                                            (std::rand() / (RAND_MAX+1.) * 255)
                                            ))
                                    );
    }
}
void TrajectoriesDialog::on_solidColorButton_clicked()
{
    QColorDialog colorDialog(this);
    connect(&colorDialog,SIGNAL(colorSelected(QColor)), this,SLOT(colorSelectedByUser(QColor)));
    colorDialog.setModal(true);
    colorDialog.exec();
}

void TrajectoriesDialog::colorSelectedByUser(QColor chosenColor)
{
    this->chosenSolidColor = chosenColor;
    ui->solidColorButton->setStyleSheet(convertToStyleSheet(
                                            "QPushButton",
                                             QColor(
                                                 chosenColor.red(),
                                                 chosenColor.green(),
                                                 chosenColor.blue()
                                                 ))
                                        );
}

void TrajectoriesDialog::changeChosenColor()
{
    QPushButton* senderObj = (QPushButton *)sender();

    QColorDialog colorDialog(this);

    QColor startColor = colorDialog.selectedColor();

    colorDialog.setModal(true);
    colorDialog.exec();

    if(startColor != colorDialog.selectedColor()){
    senderObj->setStyleSheet(convertToStyleSheet(
                                      "QPushButton",
                                       QColor(
                                           colorDialog.selectedColor().red(),
                                           colorDialog.selectedColor().green(),
                                           colorDialog.selectedColor().blue()
                                           ))
                                  );
    }
}

QString TrajectoriesDialog::convertToStyleSheet(QString device, QColor rgbColor, QString option)
{
    QString outString = device + " { " + option +":";
    outString += QString(" rgb(%1,%2,%3)}").arg(
                QString::number(rgbColor.red()),
                QString::number(rgbColor.green()),
                QString::number(rgbColor.blue())
                );
    return outString;
}
//----------------------------------------------------------------------------





//--------------------FUNCTIONS WHICH CHECK CORRECT CHOSEN RANGE----------------
void TrajectoriesDialog::on_defineXMin_valueChanged(double arg1)
{
    if(ui->defineXMax->value() < arg1)
    {
        QMessageBox::warning(this,"Wrong range point","Xmin > Xmax !");
        ui->defineXMin->setValue(-1.0);
    }
}

void TrajectoriesDialog::on_defineXMax_valueChanged(double arg1)
{
    if(ui->defineXMin->value() > arg1)
    {
        QMessageBox::warning(this,"Wrong range point","Xmax < Xmin !");
        ui->defineXMax->setValue(1.0);
    }
}

void TrajectoriesDialog::on_defineYMin_valueChanged(double arg1)
{
    if(ui->defineYMax->value() < arg1)
    {
        QMessageBox::warning(this,"Wrong range point","Ymin > Ymax !");
        ui->defineYMin->setValue(-1.0);
    }
}

void TrajectoriesDialog::on_defineYMax_valueChanged(double arg1)
{
    if(ui->defineYMin->value() > arg1)
    {
        QMessageBox::warning(this,"Wrong range point","Ymax < Ymin !");
        ui->defineYMax->setValue(1.0);
    }
}

void TrajectoriesDialog::on_defineZMin_valueChanged(double arg1)
{
    if(ui->defineZMax->value() < arg1)
    {
        QMessageBox::warning(this,"Wrong range point","Zmin > Zmax !");
        ui->defineZMin->setValue(-1.0);
    }
}

void TrajectoriesDialog::on_defineZMax_valueChanged(double arg1)
{
    if(ui->defineZMin->value() > arg1)
    {
        QMessageBox::warning(this,"Wrong range point","Zmax <= Zmin !");
        ui->defineZMax->setValue(1.0);
    }
}
