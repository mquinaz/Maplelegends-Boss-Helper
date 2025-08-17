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
    QVector<QVector<std::tuple<QTimer *, QDateTime, QDateTime, QDateTime>>> timerList;
};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool displayTime;

    void processTimer(QDateTime boundTime, QDateTime lowerBoundTime, QDateTime upperBoundTime, int bossIndex, int ccIndex);

public slots:
    void timerButtonClick(QAbstractButton*);
    void linkLabelClick(int index);
    void changeDisplayTime();
    void timerUpdate(int bossIndex, int ccIndex, int mapIndex);
    void changeMap(const QString& map, int bossIndex);
    void expandFilters(QPushButton *sidePanelExpander, QWidget *sidePanel);

private:
    void updateTimerLabels(int bossIndex);

private:
    Ui::MainWindow *ui;
    Backup *file;
    Monster *monster;
    QVector<MonsterUI> listBossUI;
    QVector<int> mapMonster;
};
#endif // MAINWINDOW_H
