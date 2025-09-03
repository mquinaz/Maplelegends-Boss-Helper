#ifndef TIMER_H
#define TIMER_H

#include <QTimer>

class Timer : public QObject
{
    Q_OBJECT
    QTimer *t;
public:
    Timer();
    void activateTimer();

public slots:
    void TimerSlot();
};

#endif // TIMER_H
