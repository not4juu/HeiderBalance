#ifndef STATISTICSPOINTSETUP_H
#define STATISTICSPOINTSETUP_H

#include <QDialog>

namespace Ui {
class statisticsPointSetup;
}

class statisticsPointSetup : public QDialog
{
    Q_OBJECT

public:
    explicit statisticsPointSetup(QWidget *parent = 0);
    ~statisticsPointSetup();

private:
    Ui::statisticsPointSetup *ui;
};

#endif // STATISTICSPOINTSETUP_H
