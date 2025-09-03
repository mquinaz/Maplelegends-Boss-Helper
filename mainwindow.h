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

private slots:
    void timerButtonClick(QAbstractButton*);
    void linkLabelClick(int index);
    void changeDisplayTime();
    void timerUpdate(int bossIndex, int ccIndex, int mapIndex);
    void changeMap(const QString& map, int bossIndex);
    void expandFilters(QPushButton *sidePanelButton, QWidget *sidePanel, QLabel *filterLabel);
    void filterMonster(int bossIndex);

private:
    void renderMonster();
    void processTimer(QDateTime boundTime, QDateTime lowerBoundTime, QDateTime upperBoundTime, int bossIndex, int ccIndex, int mapIndex);

private:
    Ui::MainWindow *ui;
    Backup *file;
    Monster *monster;
    QVector<MonsterUI> listBossUI;
    QVector<int> mapMonster;
    QVector<bool> mapFilterMonster;
    bool displaySideMenu;
    bool displayTime;

    QWidget *contentWidget;

    int width, height;
    int buttonDisplayx, buttonDisplayy, buttonDisplayDimensionx, buttonDisplayDimensiony;
    int bossImagex, bossImagey, bossImageDimensionx, bossImageDimensiony;
    int bossCombox, bossComboy, bossComboDimensionx, bossComboDimensiony, bossComboMaxDimensionx;
    int bossNamex, bossNamey, bossNameDimensionx, bossNameDimensiony;
    int bossx, bossy, bossDimensionx, bossDimensiony;
    int spaceBetweenBossy;
    int filterLabelx, filterLabely, filterLabelDimensionx, filterLabelDimensiony;
    int checkboxx, checkboxy, checkboxDimensionx, checkboxDimensiony;
    int timerBossx, timerBossy, timerBossDimensionx, timerBossDimensiony;
    int spaceBetweenTimerx, spaceBetweenTimery;
    int buttonBossx, buttonBossy, buttonBossDimensionx, buttonBossDimensiony;
    int spaceBetweenButtonx, spaceBetweenButtony;
    int spaceBetweenBossesx, spaceBetweenBossesy;
    int numRow;
    int numBossesPerRow;
    int sidePanelButtonx, sidePanelButtony, sidePanelButtonDimensionx, sidePanelButtonDimensiony;
    int sidePanelx, sidePanely, sidePanelDimensionx, sidePanelDimensiony;
};
#endif // MAINWINDOW_H
