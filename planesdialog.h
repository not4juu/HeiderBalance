#ifndef PLANESDIALOG_H
#define PLANESDIALOG_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include "QColorDialog"
#include "plane.h"
#include "colorproperties.h"


namespace Ui {
class PlanesDialog;
}

class PlanesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlanesDialog(QWidget *parent = 0);
    ~PlanesDialog();

signals:
    void emitPlanes(std::vector<Plane>, double);

private slots:
    void on_addPlane_clicked();

    void on_deletePlane_clicked();

    void on_alphaChannel_valueChanged(double arg1);

    void changePlaneColor();

    void on_darawPlanes_clicked();

private:
    Ui::PlanesDialog *ui;

    std::vector<std::vector<QDoubleSpinBox *> > allSpinBoxes;
    std::vector<QLabel *> allLabels;
    std::vector<QPushButton *> allColorButtons;
    std::vector<QHBoxLayout *> allLayouts;

    double alphaChannel;

    void setPlanesProperties(QDoubleSpinBox *box, QLabel *label);
    QString convertToStyleSheet(QString device, QColor rgbColor, QString option = "background-color");
};

#endif // PLANESDIALOG_H
