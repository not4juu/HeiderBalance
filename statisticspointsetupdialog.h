#ifndef STATISTICSPOINTSETUPDIALOG_H
#define STATISTICSPOINTSETUPDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "stere.h"


namespace Ui {
class StatisticsPointSetupDialog;
}

class StatisticsPointSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsPointSetupDialog(QWidget *parent = 0);

    ~StatisticsPointSetupDialog();
signals:
    void emitAmountPoint(int, int, double *, bool);

private slots:

    void on_rangeSetupBox_currentIndexChanged(int index);

    void on_addPointButton_clicked();
    void on_addAndRunButton_clicked();

    void on_defineXMin_valueChanged(double arg1);
    void on_defineXMax_valueChanged(double arg1);
    void on_defineYMin_valueChanged(double arg1);
    void on_defineYMax_valueChanged(double arg1);
    void on_defineZMin_valueChanged(double arg1);
    void on_defineZMax_valueChanged(double arg1);

private:
    Ui::StatisticsPointSetupDialog *ui;
    QString convertToStyleSheet(QString device, QColor rgbColor, QString option = "background-color");
};

#endif // STATISTICSPOINTSETUPDIALOG_H
