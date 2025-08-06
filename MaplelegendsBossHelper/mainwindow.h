#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QLabel>
#include <QFile>
#include <QPushButton>

#include "backup.h"
#include "monster.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

struct MonsterUI {
    QLabel *bossImage;
    QPushButton *bossName;
    QVector<QLabel *> bossCC;
    QVector<QLabel *> timer1BossCC;
    QVector<QLabel *> timer2BossCC;
    QVector<QPushButton *> button1BossCC;
    QVector<QPushButton *> button2BossCC;
    QButtonGroup* groupBoss;
    QVector<std::tuple<QTimer *, QDateTime, QDateTime, QDateTime>> timerList;
};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool displayTime;

    void activateTimer(QDateTime boundTime, int bossIndex, int ccIndex);

public slots:
    void timerButtonClick(QAbstractButton*);
    void linkLabelClick(int index);
    void changeDisplayTime();
    void timerUpdate(QLabel *labelTimer1, QLabel *labelTimer2, int bossIndex, int ccIndex);

private:
    Ui::MainWindow *ui;
    Backup *file;
    Monster *monster;
    QVector<MonsterUI> listBossUI;

};
#endif // MAINWINDOW_H
