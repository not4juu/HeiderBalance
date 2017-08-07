#include "planesdialog.h"
#include "ui_planesdialog.h"

PlanesDialog::PlanesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlanesDialog)
{
    ui->setupUi(this);
    this->alphaChannel = ui->alphaChannel->value();
}

PlanesDialog::~PlanesDialog()
{
    delete ui;
}
//---------------------------------------------------------------



//************************** SLOTS ******************************


//------------------------ADD Planes-----------------------------
void PlanesDialog::on_addPlane_clicked()
{
    QDoubleSpinBox *A =  new QDoubleSpinBox(this);
    QDoubleSpinBox *B =  new QDoubleSpinBox(this);
    QDoubleSpinBox *C =  new QDoubleSpinBox(this);
    QDoubleSpinBox *d =  new QDoubleSpinBox(this);

    QLabel *ALabel = new QLabel(this);
    QLabel *BLabel = new QLabel(this);
    QLabel *CLabel = new QLabel(this);
    QLabel *dLabel = new QLabel(this);
    QLabel *zeroLabel = new QLabel(this);

    setPlanesProperties(A, ALabel);
    setPlanesProperties(B, BLabel);
    setPlanesProperties(C, CLabel);
    setPlanesProperties(d, dLabel);

    ALabel->setText("A +");
    BLabel->setText("B +");
    CLabel->setText("C +");
    dLabel->setText("d +");
    zeroLabel->setText("=0");
    zeroLabel->setMaximumWidth(20);
    d->setValue(0.0);

    QPushButton *colorButton = new QPushButton(this);
    colorButton->setStyleSheet(convertToStyleSheet(
                                   "QPushButton",
                                    ColorProperties::DEFAULT_PLANE_COLOR)
                               );
    connect(colorButton, SIGNAL(clicked()),this, SLOT(changePlaneColor()));
    colorButton->setMaximumHeight(15);
    colorButton->setMaximumWidth(15);

    QHBoxLayout *layoutHorizontal = new QHBoxLayout();
    layoutHorizontal->addWidget(ALabel);
    layoutHorizontal->addWidget(A);
    layoutHorizontal->addWidget(BLabel);
    layoutHorizontal->addWidget(B);
    layoutHorizontal->addWidget(CLabel);
    layoutHorizontal->addWidget(C);
    layoutHorizontal->addWidget(dLabel);
    layoutHorizontal->addWidget(d);
    layoutHorizontal->addWidget(zeroLabel);
    layoutHorizontal->addWidget(colorButton);

    layoutHorizontal->setSpacing(3);
    ui->planesLayout->addLayout(layoutHorizontal);

    std::vector<QDoubleSpinBox *> planeSpinBoxes;
    planeSpinBoxes.push_back(A);
    planeSpinBoxes.push_back(B);
    planeSpinBoxes.push_back(C);
    planeSpinBoxes.push_back(d);
    this->allSpinBoxes.push_back(planeSpinBoxes);


    this->allLabels.push_back(ALabel);
    this->allLabels.push_back(BLabel);
    this->allLabels.push_back(CLabel);
    this->allLabels.push_back(dLabel);
    this->allLabels.push_back(zeroLabel);
    this->allColorButtons.push_back(colorButton);
    this->allLayouts.push_back(layoutHorizontal);
}
//---------------------------------------------------------------





//-----------------------DELETE Planes---------------------------
void PlanesDialog::on_deletePlane_clicked()
{
    if(!this->allLayouts.empty())
    {
        QHBoxLayout *lastPlaneLayout = this->allLayouts.back();
        this->allLayouts.pop_back();
        delete lastPlaneLayout;

        QPushButton *colorButton = this->allColorButtons.back();
        this->allColorButtons.pop_back();
        delete colorButton;



        std::vector<QDoubleSpinBox *> planeSpinBoxes = this->allSpinBoxes.back();
        {
            QDoubleSpinBox *DspinBox = planeSpinBoxes.back();
            planeSpinBoxes.pop_back();
            delete DspinBox;
            QDoubleSpinBox *CspinBox = planeSpinBoxes.back();
            planeSpinBoxes.pop_back();
            delete CspinBox;
            QDoubleSpinBox *BspinBox = planeSpinBoxes.back();
            planeSpinBoxes.pop_back();
            delete BspinBox;
            QDoubleSpinBox *AspinBox = planeSpinBoxes.back();
            planeSpinBoxes.pop_back();
            delete AspinBox;
        }
        this->allSpinBoxes.pop_back();


        QLabel *zerolabels = this->allLabels.back();
        this->allLabels.pop_back();
        delete zerolabels;
        QLabel *dlabels = this->allLabels.back();
        this->allLabels.pop_back();
        delete dlabels;
        QLabel *Clabels = this->allLabels.back();
        this->allLabels.pop_back();
        delete Clabels;
        QLabel *Blabels = this->allLabels.back();
        this->allLabels.pop_back();
        delete Blabels;
        QLabel *Alabels = this->allLabels.back();
        this->allLabels.pop_back();
        delete Alabels;
    }
}
//---------------------------------------------------------------





//------------------- ALPHA CHANNEL FUNCTION --------------------
void PlanesDialog::on_alphaChannel_valueChanged(double arg1)
{
    this->alphaChannel = arg1;
}
//---------------------------------------------------------------




//------------------- PLANES COLOR FUNCTION ---------------------
void PlanesDialog::changePlaneColor()
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

//---------------------------------------------------------------





//------------------------DRAW Planes----------------------------
void PlanesDialog::on_darawPlanes_clicked()
{
    std::vector<Plane> allPlanes;
    if(!this->allLayouts.empty())
    {
        for(unsigned iter=0; iter < this->allColorButtons.size(); ++iter)
        {
            QPushButton *colorButton = this->allColorButtons.at(iter);
            QColor buttonColor = colorButton->palette().color(QPalette::Background);
           // qDebug("R %d G %d B %d",buttonColor.red(),buttonColor.green(),buttonColor.blue());

            std::vector<QDoubleSpinBox *> planeSpinBoxes = this->allSpinBoxes.at(iter);

            QDoubleSpinBox *DspinBox = planeSpinBoxes.at(3);
            QDoubleSpinBox *CspinBox = planeSpinBoxes.at(2);
            QDoubleSpinBox *BspinBox = planeSpinBoxes.at(1);
            QDoubleSpinBox *AspinBox = planeSpinBoxes.at(0);

           // qDebug("A %lf B %lf C%lf D%lf",AspinBox->value(),BspinBox->value(),CspinBox->value(),DspinBox->value());

            Plane plane(AspinBox->value(),BspinBox->value(),CspinBox->value(),DspinBox->value(),buttonColor);
            allPlanes.push_back(plane);
        }

    }
    emit emitPlanes(allPlanes,this->alphaChannel);
}
//---------------------------------------------------------------


//******************* PRIVATE FUNCTIONS *************************


//-------------- PLANES PROPERTIES FUNCTIONS --------------------
void PlanesDialog::setPlanesProperties(QDoubleSpinBox *box, QLabel *label)
{
    box->setButtonSymbols(QAbstractSpinBox::NoButtons);
    box->setRange(-99.0,99.0);
    box->setSingleStep(0.1);
    box->setDecimals(2);
    box->setValue(1.);
    box->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    label->setMaximumWidth(40);
}

QString PlanesDialog::convertToStyleSheet(QString device, QColor rgbColor, QString option)
{
    QString outString = device + " { " + option +":";
    outString += QString(" rgb(%1,%2,%3)}").arg(
                QString::number(rgbColor.red()),
                QString::number(rgbColor.green()),
                QString::number(rgbColor.blue())
                );
    return outString;
}
