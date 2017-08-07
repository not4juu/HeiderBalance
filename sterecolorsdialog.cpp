#include "sterecolorsdialog.h"
#include "ui_sterecolorsdialog.h"
#include "stere.h"

StereColorsDialog::StereColorsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StereColorsDialog)
{
    ui->setupUi(this);

    setDefaultColors();

    connect(ui->upFrontRightStere, SIGNAL(clicked()),this, SLOT(changeChosenColor()));
    connect(ui->upFrontLeftStere, SIGNAL(clicked()),this, SLOT(changeChosenColor()));
    connect(ui->upBackRightStere, SIGNAL(clicked()),this, SLOT(changeChosenColor()));
    connect(ui->upBackLeftStere, SIGNAL(clicked()),this, SLOT(changeChosenColor()));

    connect(ui->downFrontRightStere, SIGNAL(clicked()),this, SLOT(changeChosenColor()));
    connect(ui->downFrontLeftStere, SIGNAL(clicked()),this, SLOT(changeChosenColor()));
    connect(ui->downBackRightStere, SIGNAL(clicked()),this, SLOT(changeChosenColor()));
    connect(ui->downBackLeftStere, SIGNAL(clicked()),this, SLOT(changeChosenColor()));
}
StereColorsDialog::~StereColorsDialog()
{
    delete ui;
}

void StereColorsDialog::on_overwriteButton_clicked()
{
    ColorProperties::STERE_COLOR_0 = ui->upFrontRightStere->palette().color(QPalette::Background);
    ColorProperties::STERE_COLOR_1 = ui->upFrontLeftStere->palette().color(QPalette::Background);
    ColorProperties::STERE_COLOR_2 = ui->upBackRightStere->palette().color(QPalette::Background);
    ColorProperties::STERE_COLOR_3 = ui->upBackLeftStere->palette().color(QPalette::Background);

    ColorProperties::STERE_COLOR_4 = ui->downFrontRightStere->palette().color(QPalette::Background);
    ColorProperties::STERE_COLOR_5 = ui->downFrontLeftStere->palette().color(QPalette::Background);
    ColorProperties::STERE_COLOR_6 = ui->downBackRightStere->palette().color(QPalette::Background);
    ColorProperties::STERE_COLOR_7 = ui->downBackLeftStere->palette().color(QPalette::Background);

    this->close();
}

void StereColorsDialog::on_defaultButton_clicked()
{
    setDefaultColors(BACK_TO_DEFAULT_COLOR);
    this->close();
}

void StereColorsDialog::setDefaultColors(int type)
{

    if(type == BACK_TO_DEFAULT_COLOR)
    {
        // PINK
        ColorProperties::STERE_COLOR_0 =  QColor(255,0,255);
        // YELLOW
        ColorProperties::STERE_COLOR_1 =  QColor(240,240,0);
        // LIGHT BLUE
        ColorProperties::STERE_COLOR_2 =  QColor(0,255,255);
        // GREEN
        ColorProperties::STERE_COLOR_3 =  QColor(0,255,0);
        // BRWON
        ColorProperties::STERE_COLOR_4 =  QColor(160,80,0);
        // RED
        ColorProperties::STERE_COLOR_5 =  QColor(255,0,0);
        // ORANGE
        ColorProperties::STERE_COLOR_6 =  QColor(255,160,0);
        // PURPLE
        ColorProperties::STERE_COLOR_7 =  QColor(140,0,255);
    }

    ui->upFrontRightStere->setStyleSheet(convertToStyleSheet("QPushButton",Stere::findStereColor("upFrontRightStere")));
    ui->upFrontLeftStere->setStyleSheet(convertToStyleSheet("QPushButton",Stere::findStereColor("upFrontLeftStere")));

    ui->upBackRightStere->setStyleSheet(convertToStyleSheet("QPushButton",Stere::findStereColor("upBackRightStere")));
    ui->upBackLeftStere->setStyleSheet(convertToStyleSheet("QPushButton",Stere::findStereColor("upBackLeftStere")));


    ui->downFrontRightStere->setStyleSheet(convertToStyleSheet("QPushButton",Stere::findStereColor("downFrontRightStere")));
    ui->downFrontLeftStere->setStyleSheet(convertToStyleSheet("QPushButton",Stere::findStereColor("downFrontLeftStere")));

    ui->downBackRightStere->setStyleSheet(convertToStyleSheet("QPushButton",Stere::findStereColor("downBackRightStere")));
    ui->downBackLeftStere->setStyleSheet(convertToStyleSheet("QPushButton",Stere::findStereColor("downBackLeftStere")));
}

QString StereColorsDialog::convertToStyleSheet(QString device, QColor rgbColor, QString option)
{
    QString outString = device + " { " + option +":";
    outString += QString(" rgb(%1,%2,%3)}").arg(
                QString::number(rgbColor.red()),
                QString::number(rgbColor.green()),
                QString::number(rgbColor.blue())
                );
    return outString;
}

void StereColorsDialog::changeChosenColor()
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
