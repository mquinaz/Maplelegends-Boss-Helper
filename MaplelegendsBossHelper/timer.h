#ifndef TIMER_H
#define TIMER_H

#include <QTimer>

class Timer : public QObject
{
    Q_OBJECT
public:
    Timer();
    QTimer *t;

public slots:
    void TimerSlot();
};

#endif // TIMER_H
