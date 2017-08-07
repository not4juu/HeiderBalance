#ifndef GENERATOR_H
#define GENERATOR_H

#include <QThread>

/***
 *  Generator which generates independent(uses thread) signal in defined period of time
 *  Notice: time is calcualte in miliseconds
 ***/
class Generator : public QThread
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = 0);
    void run();


    bool getPaintTrajectories() const;
    void setPaintTrajectories(bool value);

    int getSleepTime() const;
    void setSleepTime(int value);   

signals:
    void repaintGenerator();

public slots:

private:
    int sleepTime;
    bool paintTrajectories;
};

#endif // GENERATOR_H
