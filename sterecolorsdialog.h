#ifndef STERECOLORSDIALOG_H
#define STERECOLORSDIALOG_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
class StereColorsDialog;
}

class StereColorsDialog : public QDialog
{
    Q_OBJECT

private slots:
    void changeChosenColor();

    void on_defaultButton_clicked();

    void on_overwriteButton_clicked();

public:
    explicit StereColorsDialog(QWidget *parent = 0);
    ~StereColorsDialog();

private:
    Ui::StereColorsDialog *ui;
    QString convertToStyleSheet(QString device, QColor rgbColor, QString option = "background-color");
    void setDefaultColors(int type = 0);

    enum {BACK_TO_DEFAULT_COLOR = 1};
};

#endif // STERECOLORSDIALOG_H
