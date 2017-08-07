#include "statisticspointsetupdialog.h"
#include "ui_statisticspointsetupdialog.h"

StatisticsPointSetupDialog::StatisticsPointSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsPointSetupDialog)
{
    ui->setupUi(this);

    ui->stereFrame->setVisible(false);

    ui->upFrontRightStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("upFrontRightStere")));
    ui->upFrontLeftStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("upFrontLeftStere")));

    ui->upBackRightStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("upBackRightStere")));
    ui->upBackLeftStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("upBackLeftStere")));


    ui->downFrontRightStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("downFrontRightStere")));
    ui->downFrontLeftStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("downFrontLeftStere")));

    ui->downBackRightStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("downBackRightStere")));
    ui->downBackLeftStere->setStyleSheet(convertToStyleSheet("QCheckBox:hover",Stere::findStereColor("downBackLeftStere")));
}

StatisticsPointSetupDialog::~StatisticsPointSetupDialog()
{
    delete ui;
}

//----------------------------------------------------------------


//************************** SLOTS ******************************


//-----------------SETUP RANGE AND ADD POINTS FUNCTION -----------
void StatisticsPointSetupDialog::on_rangeSetupBox_currentIndexChanged(int index)
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
//----------------------------------------------------------------




//-------------------- ADD POINTS FUNCTION -----------------------
void StatisticsPointSetupDialog::on_addPointButton_clicked()
{
    double *pointRange = new double [8];
    if(ui->rangeSetupBox->currentIndex() == 0)
    {
        pointRange[0] = ui->defineXMin->value();
        pointRange[1] = ui->defineXMax->value();

        pointRange[2] = ui->defineYMin->value();
        pointRange[3] = ui->defineYMax->value();


        pointRange[4] = ui->defineZMin->value();
        pointRange[5] = ui->defineZMax->value();

        //this vlaue is not use but we need 8 elemtns for stere
        pointRange[6] = 0.;
        pointRange[7] = 0.;

    }
    if(ui->rangeSetupBox->currentIndex() == 1)
    {
        pointRange[0] = ui->upFrontRightStere->isChecked();
        pointRange[1] = ui->upFrontLeftStere->isChecked();

        pointRange[2] = ui->upBackRightStere->isChecked();
        pointRange[3] = ui->upBackLeftStere->isChecked();


        pointRange[4] = ui->downFrontRightStere->isChecked();
        pointRange[5] = ui->downFrontLeftStere->isChecked();

        pointRange[6] = ui->downBackRightStere->isChecked();
        pointRange[7] = ui->downBackLeftStere->isChecked();
    }

    bool stereNotSelected = true;

    for(int i=0; i < 8; ++i){
        if(pointRange[i] != 0.)stereNotSelected = false;
    }

   if(stereNotSelected && ui->rangeSetupBox->currentIndex()==1)
   {
       QMessageBox::warning(this,"Select warning","Please select stere");
   }
   else
   {
       emit emitAmountPoint(ui->pointAmount->value(), ui->rangeSetupBox->currentIndex(),pointRange,0);
   }
}
//----------------------------------------------------------------




//----------------- ADD POINTS AND RUN FUNCTION ------------------
void StatisticsPointSetupDialog::on_addAndRunButton_clicked()
{
    double *pointRange = new double [8];
    if(ui->rangeSetupBox->currentIndex() == 0)
    {
        pointRange[0] = ui->defineXMin->value();
        pointRange[1] = ui->defineXMax->value();

        pointRange[2] = ui->defineYMin->value();
        pointRange[3] = ui->defineYMax->value();


        pointRange[4] = ui->defineZMin->value();
        pointRange[5] = ui->defineZMax->value();

        //this vlaue is not use but we need 8 elemtns for stere
        pointRange[6] = 0.;
        pointRange[7] = 0.;

    }
    if(ui->rangeSetupBox->currentIndex() == 1)
    {
        pointRange[0] = ui->upFrontRightStere->isChecked();
        pointRange[1] = ui->upFrontLeftStere->isChecked();

        pointRange[2] = ui->upBackRightStere->isChecked();
        pointRange[3] = ui->upBackLeftStere->isChecked();


        pointRange[4] = ui->downFrontRightStere->isChecked();
        pointRange[5] = ui->downFrontLeftStere->isChecked();

        pointRange[6] = ui->downBackRightStere->isChecked();
        pointRange[7] = ui->downBackLeftStere->isChecked();
    }

    bool stereNotSelected = true;

    for(int i=0; i < 8; ++i){
        if(pointRange[i] != 0.)stereNotSelected = false;
    }

   if(stereNotSelected && ui->rangeSetupBox->currentIndex()==1)
   {
       QMessageBox::warning(this,"Select warning","Please select stere");
   }
   else
   {
       emit emitAmountPoint(ui->pointAmount->value(), ui->rangeSetupBox->currentIndex(),pointRange,1);
   }
}
//----------------------------------------------------------------





//--------FUNCTIONS WHICH ARE CHECKING CORRECT CHOSEN RANGE--------

void StatisticsPointSetupDialog::on_defineXMin_valueChanged(double arg1)
{
    if(ui->defineXMax->value() < arg1)
    {
        QMessageBox::warning(this,"Wrong range point","Xmin > Xmax !");
        ui->defineXMin->setValue(-1.0);
    }
}
void StatisticsPointSetupDialog::on_defineXMax_valueChanged(double arg1)
{
    if(ui->defineXMin->value() > arg1)
    {
        QMessageBox::warning(this,"Wrong range point","Xmax < Xmin !");
        ui->defineXMax->setValue(1.0);
    }
}
void StatisticsPointSetupDialog::on_defineYMin_valueChanged(double arg1)
{
    if(ui->defineYMax->value() < arg1)
    {
        QMessageBox::warning(this,"Wrong range point","Ymin > Ymax !");
        ui->defineYMin->setValue(-1.0);
    }
}
void StatisticsPointSetupDialog::on_defineYMax_valueChanged(double arg1)
{
    if(ui->defineYMin->value() > arg1)
    {
        QMessageBox::warning(this,"Wrong range point","Ymax < Ymin !");
        ui->defineYMax->setValue(1.0);
    }
}
void StatisticsPointSetupDialog::on_defineZMin_valueChanged(double arg1)
{
    if(ui->defineZMax->value() < arg1)
    {
        QMessageBox::warning(this,"Wrong range point","Zmin > Zmax !");
        ui->defineZMin->setValue(-1.0);
    }
}
void StatisticsPointSetupDialog::on_defineZMax_valueChanged(double arg1)
{
    if(ui->defineZMin->value() > arg1)
    {
        QMessageBox::warning(this,"Wrong range point","Zmax < Zmin !");
        ui->defineZMax->setValue(1.0);
    }
}
//----------------------------------------------------------------


//******************** PRIVATE FUNCTIONS *************************


//--------------- HELPER TO CONVER STYLE FUNCTION-----------------
QString StatisticsPointSetupDialog::convertToStyleSheet(QString device, QColor rgbColor, QString option)
{
    QString outString = device + " { " + option +":";
    outString += QString(" rgb(%1,%2,%3)}").arg(
                QString::number(rgbColor.red()),
                QString::number(rgbColor.green()),
                QString::number(rgbColor.blue())
                );
    return outString;
}
