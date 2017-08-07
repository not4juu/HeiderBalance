#ifndef TRAJECTORIESDIALOG_H
#define TRAJECTORIESDIALOG_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QColorDialog>
#include <vector>
#include "point3d.h"
#include "stere.h"
#include "colorproperties.h"

namespace Ui {
class TrajectoriesDialog;
}

class TrajectoriesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrajectoriesDialog(std::vector<Point3D> allPoints, QWidget *parent = 0);
    ~TrajectoriesDialog();

signals:

    void appendPoints(std::vector<Point3D> allPoints);

private slots:

    void on_addTrajectoryButton_clicked();
    void on_deleteTrajectoryButton_clicked();
    void on_saveTrajetories_clicked();


    void on_buttonRanomPoints_clicked();
    void on_pointsRangeBox_currentIndexChanged(int index);

    void on_buttonColorPoints_clicked();
    void on_solidColorButton_clicked();
    void changeChosenColor();
    void colorSelectedByUser(QColor);

    void on_defineXMin_valueChanged(double arg1);
    void on_defineXMax_valueChanged(double arg1);
    void on_defineYMin_valueChanged(double arg1);
    void on_defineYMax_valueChanged(double arg1);
    void on_defineZMin_valueChanged(double arg1);
    void on_defineZMax_valueChanged(double arg1);

private:
    Ui::TrajectoriesDialog *ui;

    std::vector<QPushButton *> *allColorButtons;
    std::vector<QHBoxLayout *> *allLayouts;
    std::vector<QCheckBox *> *checkBoxes;
    std::vector<std::vector<QDoubleSpinBox *> > *allSpinBoxes;
    std::vector<std::vector<QLabel *> > *allLabels;

    enum {OLD_POINT, NEW_POINT};
    void addPoint(bool newPoint = NEW_POINT, double xPoint = 0., double yPoint = 0., double zPoint = 0. , QColor rgbPoint = ColorProperties::DEFAULT_POINT_COLOR );
    void setPointsProperties(QDoubleSpinBox *box);

    void randomAllPoints();
    void randomChosenPoints();
    Point3D randomStere();

    void solidColor();
    void stereColor();
    void randomColor();

    QColor chosenSolidColor;
    QString convertToStyleSheet(QString device, QColor rgbColor, QString option = "background-color");
};

#endif // TRAJECTORIESDIALOG_H
