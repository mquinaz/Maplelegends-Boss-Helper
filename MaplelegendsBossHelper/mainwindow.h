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
    QVector<int> mapMonster;
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
    void timerUpdate(int bossIndex, int ccIndex);
    void changeMap(const QString& map, int bossIndex);
    void expandFilters(QPushButton *sidePanelExpander, QWidget *sidePanel);

private:
    Ui::MainWindow *ui;
    Backup *file;
    Monster *monster;
    QVector<MonsterUI> listBossUI;
};
#endif // MAINWINDOW_H
