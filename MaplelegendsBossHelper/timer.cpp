#include "timer.h"

#include <QDebug>

Timer::Timer()
{
    t = new QTimer(this);

    connect(t, SIGNAL(timeout()), this, SLOT(TimerSlot()));

    t->start(1000);
}



void Timer::TimerSlot()
{
    qDebug() << "Timer...";
}
