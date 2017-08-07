#include "generator.h"


Generator::Generator(QObject *parent) :
    QThread(parent)
{
}

void Generator::run()
{
    while(this->getPaintTrajectories())
    {
        emit repaintGenerator();
        msleep(this->sleepTime);
    }
}
bool Generator::getPaintTrajectories() const
{
    return paintTrajectories;
}

void Generator::setPaintTrajectories(bool value)
{
    paintTrajectories = value;
}

int Generator::getSleepTime() const
{
    return sleepTime;
}

void Generator::setSleepTime(int value)
{
    sleepTime = value;
}




