#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QLabel>
#include <QFile>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>

#include "backup.h"
#include "monster.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

struct MonsterUI {
    QCheckBox *checkbox;
    QComboBox* combo;
    QLabel *bossImage;
    QPushButton *bossName;
    QVector<QLabel *> bossCC;
    QVector<QLabel *> timer1BossCC;
    QVector<QLabel *> timer2BossCC;
    QVector<QPushButton *> button1BossCC;
    QVector<QPushButton *> button2BossCC;
    QButtonGroup* groupBoss;
    QVector<QVector<std::tuple<QTimer *, QDateTime, QDateTime, QDateTime, int>>> timerList;
    QVector<int> originalMap;
};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool displayTime;

    void processTimer(QDateTime boundTime, QDateTime lowerBoundTime, QDateTime upperBoundTime, int bossIndex, int ccIndex, int mapIndex);

public slots:
    void timerButtonClick(QAbstractButton*);
    void linkLabelClick(int index);
    void changeDisplayTime();
    void timerUpdate(int bossIndex, int ccIndex, int mapIndex);
    void changeMap(const QString& map, int bossIndex);
    void expandFilters(QPushButton *sidePanelButton, QWidget *sidePanel);
    void filterMonster(int bossIndex);

private:
    void updateTimerLabels(int bossIndex);
    void renderMonster(int bossIndex);

private:
    Ui::MainWindow *ui;
    Backup *file;
    Monster *monster;
    QVector<MonsterUI> listBossUI;
    QVector<int> mapMonster;
    QVector<bool> mapFilterMonster;
    bool displaySideMenu;

    QWidget *contentWidget;

    int width, height;
    int buttonDisplayx, buttonDisplayy, buttonDisplayDimensionx, buttonDisplayDimensiony;
    int bossImagex, bossImagey, bossImageDimensionx, bossImageDimensiony;
    int bossCombox, bossComboy, bossComboDimensionx, bossComboDimensiony;
    int bossNamex, bossNamey, bossNameDimensionx, bossNameDimensiony;
    int bossx, bossy, bossDimensionx, bossDimensiony;
    int spaceBetweenBossy;
    int timerBossx, timerBossy, timerBossDimensionx, timerBossDimensiony;
    int spaceBetweenTimerx, spaceBetweenTimery;
    int buttonBossx, buttonBossy, buttonBossDimensionx, buttonBossDimensiony;
    int spaceBetweenButtonx, spaceBetweenButtony;
    int spaceBetweenBossesx, spaceBetweenBossesy;
    int numRow;
    int numBossesPerRow;
    int sidePanelButtonx, sidePanelButtony, sidePanelButtonDimensionx, sidePanelButtonDimensiony;
};
#endif // MAINWINDOW_H
