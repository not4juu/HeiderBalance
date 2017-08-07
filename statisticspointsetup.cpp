#include "statisticspointsetup.h"
#include "ui_statisticspointsetup.h"

statisticsPointSetup::statisticsPointSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statisticsPointSetup)
{
    ui->setupUi(this);
}

statisticsPointSetup::~statisticsPointSetup()
{
    delete ui;
}
