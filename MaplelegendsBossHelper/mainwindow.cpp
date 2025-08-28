#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QWidget>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QAbstractButton>
#include <string>
#include <QDesktopServices>
#include <QMessageBox>
#include <QScrollBar>
#include <QScrollArea>
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include "monster.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    monster = new Monster();

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    height = screenGeometry.height();
    width = screenGeometry.width();
    this->resize(width, height);

    displayTime = true;
    displaySideMenu = false;

    QFont font("Courier New", 16, QFont::Bold);
    QFont filterLabelFont("Segoe UI", 15, QFont::Bold);

    QFontMetrics fm(font);
    buttonDisplayx = width - 75, buttonDisplayy = 25, buttonDisplayDimensionx = 50, buttonDisplayDimensiony = 50;
    bossImagex = 75, bossImagey = 50, bossImageDimensionx = 150, bossImageDimensiony = 150;
    bossCombox = 50, bossComboy = 175, bossComboDimensionx = 20, bossComboDimensiony = 20;
    bossNamex = 75, bossNamey = 25, bossNameDimensionx = 25, bossNameDimensiony = 30;
    bossx = 50, bossy = 200, bossDimensionx = 50, bossDimensiony = 30;
    spaceBetweenBossy = 30;
    timerBossx = 100, timerBossy = 200, timerBossDimensionx = 50, timerBossDimensiony = 30;
    spaceBetweenTimerx = 50, spaceBetweenTimery = 30;
    buttonBossx = 210, buttonBossy = 200, buttonBossDimensionx = 30, buttonBossDimensiony = 30;
    spaceBetweenButtonx = 40, spaceBetweenButtony = 30;
    spaceBetweenBossesx = 300, spaceBetweenBossesy = 400;
    numRow = 0;
    numBossesPerRow = width / spaceBetweenBossesx;

    sidePanelButtonx = width - 45, sidePanelButtony = height / 2, sidePanelButtonDimensionx = 30, sidePanelButtonDimensiony = 30;
    sidePanelx = width, sidePanely = 0, sidePanelDimensionx = 200, sidePanelDimensiony = height;

    filterLabelx = width - sidePanelDimensionx, filterLabely = 0, filterLabelDimensionx = sidePanelDimensionx, filterLabelDimensiony = 30;
    checkboxx = width - sidePanelDimensionx + 10, checkboxy = 40, checkboxDimensionx = sidePanelDimensionx - 10, checkboxDimensiony = 30;

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("background: transparent;");
    scrollArea->setGeometry(0, 0, width, height);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);

    contentWidget = new QWidget();

    QPixmap bkgnd(":/images/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    QPushButton *sidePanelButton = new QPushButton(this);
    sidePanelButton->setGeometry(sidePanelButtonx, sidePanelButtony, sidePanelButtonDimensionx, sidePanelButtonDimensiony);
    sidePanelButton->setText("◀");
    sidePanelButton->setStyleSheet("QPushButton { background-color: #2C3E50; color: white; font-size: 16px; font-weight: bold; border: none; border-radius: 15px; } "
                                     "QPushButton:hover { background-color: #34495E; } QPushButton:pressed { background-color: #1A252F; }");

    QWidget *sidePanel = new QWidget(this);
    sidePanel->setGeometry(sidePanelx, sidePanely, sidePanelDimensionx, sidePanelDimensiony);
    sidePanel->setStyleSheet("background-color: lightgrey;");
    sidePanel->hide();

    QLabel *filterLabel = new QLabel(this);
    filterLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    filterLabel->setFont(filterLabelFont);
    filterLabel->setStyleSheet("QLabel { background-color:#d3d3d3; border-bottom:2px solid #aaa; padding:6px; }");
    filterLabel->setText("Filter Bosses");
    filterLabel->setAlignment(Qt::AlignCenter);
    filterLabel->setGeometry(QRect(filterLabelx, filterLabely, filterLabelDimensionx, filterLabelDimensiony));
    filterLabel->setObjectName("FilterLabel");
    filterLabel->hide();

    QObject::connect(sidePanelButton, &QPushButton::clicked, this, [=]() { expandFilters(sidePanelButton, sidePanel, filterLabel); });

    QPushButton *buttonDisplayTimer = new QPushButton(contentWidget);
    buttonDisplayTimer->setStyleSheet("QPushButton {border-image: url(:/images/timeChange.png) stretch; } QPushButton::hover { border-image: url(:/images/timeChangeHover.png) stretch; }");
    buttonDisplayTimer->setGeometry(QRect(buttonDisplayx, buttonDisplayy, buttonDisplayDimensionx, buttonDisplayDimensiony));
    connect(buttonDisplayTimer, &QPushButton::clicked, this, [=]() { changeDisplayTime(); });

    listBossUI.reserve(monster->monsterList.size());
    for(int i=0;i< monster->monsterList.size();i++)
    {
        if(i != 0 && i % numBossesPerRow == 0)
            numRow++;

        MonsterUI bossUI;

        mapMonster.push_back(0);
        mapFilterMonster.push_back(false);

        bossUI.checkbox = new QCheckBox(std::get<0>(monster->monsterList[i]), this);
        bossUI.checkbox->setGeometry(checkboxx, checkboxy + i * 30, checkboxDimensionx, checkboxDimensiony);
        bossUI.checkbox->setStyleSheet(
            "QCheckBox { font-size: 16px; color: #333; spacing: 8px; }"
            "QCheckBox::indicator { width: 18px; height: 18px; border-radius: 4px; border: 2px solid #888; background-color: white; }"
            "QCheckBox::indicator:hover { border: 2px solid #555; }"
            "QCheckBox::indicator:checked { background-color: #4CAF50; border: 2px solid #4CAF50; }"
        );
        bossUI.checkbox->hide();
        connect(bossUI.checkbox, &QCheckBox::toggled, this, [=]() { filterMonster(i); });

        bossUI.bossImage = new QLabel(contentWidget);
        bossUI.bossImage->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        bossUI.bossImage->setStyleSheet("border-image: url(:/images/Bosses/" + std::get<0>(monster->monsterList[i]) + ".png) stretch;");
        bossUI.bossImage->setAlignment(Qt::AlignCenter);
        bossUI.bossImage->setGeometry(QRect(bossImagex + spaceBetweenBossesx * (i % numBossesPerRow),bossImagey + spaceBetweenBossesy * numRow,bossImageDimensionx,bossImageDimensiony));

        QStringList commands = std::get<2>(monster->monsterList[i]);
        bossUI.combo = new QComboBox(contentWidget);
        bossUI.combo->addItems(commands);
        bossUI.combo->setGeometry(QRect(bossCombox + spaceBetweenBossesx * (i % numBossesPerRow),bossComboy + spaceBetweenBossesy * numRow, bossComboDimensionx, bossComboDimensiony));
        bossUI.combo->setStyleSheet(
            "QComboBox { background-color: white; color: black; }"
            "QComboBox QAbstractItemView { background-color: white; color: black; }"
            );
        connect(bossUI.combo, &QComboBox::currentTextChanged, this, [=](const QString &text) { changeMap(text, i); });

        bossUI.bossName = new QPushButton(contentWidget);
        bossUI.bossName->setStyleSheet("QLabel { color : white; border: 0px;} QPushButton { background-color: #4caf50; color: white; outline: none;}");
        bossUI.bossName->setText(std::get<0>(monster->monsterList[i]));
        bossUI.bossName->setFont(font);
        int widthNameBoss = fm.horizontalAdvance(std::get<0>(monster->monsterList[i]));
        bossUI.bossName->setGeometry(QRect(bossNamex + spaceBetweenBossesx * (i % numBossesPerRow),bossNamey + spaceBetweenBossesy * numRow,widthNameBoss + bossNameDimensionx,bossNameDimensiony));
        connect(bossUI.bossName, &QPushButton::clicked, this, [=]() { linkLabelClick(i); });

        bossUI.groupBoss = new QButtonGroup(contentWidget);

        bossUI.bossCC.resize(monster->numCC);
        bossUI.timer1BossCC.resize(monster->numCC);
        bossUI.timer2BossCC.resize(monster->numCC);
        bossUI.button1BossCC.resize(monster->numCC);
        bossUI.button2BossCC.resize(monster->numCC);
        bossUI.timerList.resize(monster->numCC);
        for(int c = 0; c < monster->numCC; c++)
        {
            bossUI.bossCC[c] = new QLabel(contentWidget);
            bossUI.bossCC[c]->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            bossUI.bossCC[c]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
            bossUI.bossCC[c]->setText("CC" + QString::number(c+1));
            bossUI.bossCC[c]->setAlignment(Qt::AlignCenter);
            bossUI.bossCC[c]->setGeometry(QRect(bossx + spaceBetweenBossesx * (i % numBossesPerRow),bossy + spaceBetweenBossy * c + spaceBetweenBossesy * numRow,bossDimensionx,bossDimensiony));

            bossUI.timer1BossCC[c] = new QLabel(contentWidget);
            bossUI.timer1BossCC[c]->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            bossUI.timer1BossCC[c]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
            bossUI.timer1BossCC[c]->setText("");
            bossUI.timer1BossCC[c]->setAlignment(Qt::AlignCenter);
            bossUI.timer1BossCC[c]->setGeometry(QRect(timerBossx + spaceBetweenBossesx * (i % numBossesPerRow),timerBossy + spaceBetweenTimery * c + spaceBetweenBossesy * numRow,timerBossDimensionx,timerBossDimensiony));
            bossUI.timer1BossCC[c]->setObjectName("timer1Boss" + QString::number(i + 1) + "CC" + QString::number(c + 1));

            bossUI.timer2BossCC[c] = new QLabel(contentWidget);
            bossUI.timer2BossCC[c]->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            bossUI.timer2BossCC[c]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
            bossUI.timer2BossCC[c]->setText("");
            bossUI.timer2BossCC[c]->setAlignment(Qt::AlignCenter);
            bossUI.timer2BossCC[c]->setGeometry(QRect(timerBossx + spaceBetweenTimerx + spaceBetweenBossesx * (i % numBossesPerRow),timerBossy + spaceBetweenTimery * c + spaceBetweenBossesy * numRow,timerBossDimensionx,timerBossDimensiony));
            bossUI.timer2BossCC[c]->setObjectName("timer2Boss" + QString::number(i + 1) + "CC" + QString::number(c + 1));

            bossUI.button1BossCC[c] = new QPushButton(contentWidget);
            bossUI.button1BossCC[c]->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
            bossUI.button1BossCC[c]->setGeometry(QRect(buttonBossx + spaceBetweenBossesx * (i % numBossesPerRow),buttonBossy + spaceBetweenButtony * c + spaceBetweenBossesy * numRow,buttonBossDimensionx,buttonBossDimensiony));
            bossUI.button1BossCC[c]->setObjectName("button1Boss" + QString::number(i + 1) + "CC" + QString::number(c + 1));

            bossUI.button2BossCC[c] = new QPushButton(contentWidget);
            bossUI.button2BossCC[c]->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
            bossUI.button2BossCC[c]->setGeometry(QRect(buttonBossx + spaceBetweenButtonx + spaceBetweenBossesx * (i % numBossesPerRow),buttonBossy + spaceBetweenButtony * c + spaceBetweenBossesy * numRow,buttonBossDimensionx,buttonBossDimensiony));
            bossUI.button2BossCC[c]->setObjectName("button2Boss" + QString::number(i + 1) + "CC" + QString::number(c + 1));

            bossUI.groupBoss->addButton(bossUI.button1BossCC[c]);
            bossUI.groupBoss->addButton(bossUI.button2BossCC[c]);

            bossUI.timerList[c].resize(std::get<2>(monster->monsterList[i]).size());
            for(int m = 0; m < std::get<2>(monster->monsterList[i]).size(); m++)
            {
                bossUI.timerList[c][m] = std::make_tuple(new QTimer(this), QDateTime(), QDateTime(), QDateTime(), mapMonster[i]);
                connect(get<0>(bossUI.timerList[c][m]), &QTimer::timeout, this, [=]() { timerUpdate(i, c, get<4>(listBossUI[i].timerList[c][m])); });
            }
        }
        listBossUI.push_back(bossUI);

        connect(listBossUI[i].groupBoss, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(timerButtonClick(QAbstractButton*)));
    }

    file = new Backup(monster->numCC, monster->monsterList);
    for(auto &it : std::as_const(file->backupTimerToProcess))
    {
        get<1>(listBossUI[get<3>(it)].timerList[get<4>(it)][get<5>(it)]) = get<0>(it);
        get<2>(listBossUI[get<3>(it)].timerList[get<4>(it)][get<5>(it)]) = get<1>(it);
        get<3>(listBossUI[get<3>(it)].timerList[get<4>(it)][get<5>(it)]) = get<2>(it);
        get<4>(listBossUI[get<3>(it)].timerList[get<4>(it)][get<5>(it)]) = get<5>(it);

        if(get<5>(it) == mapMonster[get<3>(it)])
            processTimer(get<0>(it), get<1>(it), get<2>(it), get<3>(it), get<4>(it), get<5>(it));

        get<0>(listBossUI[get<3>(it)].timerList[get<4>(it)][get<5>(it)])->start(1000);
    }

    contentWidget->setMinimumSize(width, bossImagey + spaceBetweenBossesy * (numRow + 1));
    scrollArea->setWidget(contentWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::timerButtonClick(QAbstractButton* button)
{
    QString buttonName = button->objectName();
    int buttonBossIndex = buttonName.lastIndexOf('s');
    int buttonCCIndex = buttonName.lastIndexOf('C');

    int bossIndex = buttonName.mid(buttonBossIndex + 1, buttonCCIndex - buttonBossIndex - 2).toInt() - 1;
    int ccIndex = buttonName.mid(buttonCCIndex + 1, buttonName.size()).toInt() - 1;
    qDebug() << buttonName;


    if(buttonName.left(7) == "button2")
    {
        QString descriptionString = "Are you sure you want to reset\nthe timer on boss " +  std::get<0>(monster->monsterList[bossIndex]) + " CC" + QString::number(ccIndex + 1) + "?";

        switch( QMessageBox::question(
            this,
            tr("Reset Timer"),
            tr(descriptionString.toUtf8().constData()),

            QMessageBox::Yes |
                QMessageBox::Cancel,

            QMessageBox::Cancel ) )
        {
        case QMessageBox::Yes:
            qDebug( "yes" );

            get<0>(listBossUI[bossIndex].timerList[ccIndex][mapMonster[bossIndex]])->stop();
            get<1>(listBossUI[bossIndex].timerList[ccIndex][mapMonster[bossIndex]]) = QDateTime();
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122);");
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122);");
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setText("");
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setText("");

            file->writeTimerBackup(monster->monsterList.size(), bossIndex, ccIndex, mapMonster[bossIndex]);

            break;
        case QMessageBox::Cancel:
            qDebug( "cancel" );
            break;
        default:
            qDebug( "close" );
            break;
        }
    }
    else if(buttonName.left(7) == "button1" && !get<0>(listBossUI[bossIndex].timerList[ccIndex][mapMonster[bossIndex]])->isActive())
    {
        QDateTime boundTime = QDateTime::currentDateTime();

        int timerValue = std::get<1>(monster->monsterList[bossIndex])[0];
        QDateTime lowerBoundTime = boundTime.addSecs(timerValue * 0.9 * 60);
        QDateTime upperBoundTime = boundTime.addSecs(timerValue * 1.1 * 60);

        get<1>(listBossUI[bossIndex].timerList[ccIndex][mapMonster[bossIndex]]) = boundTime;
        get<2>(listBossUI[bossIndex].timerList[ccIndex][mapMonster[bossIndex]]) = lowerBoundTime;
        get<3>(listBossUI[bossIndex].timerList[ccIndex][mapMonster[bossIndex]]) = upperBoundTime;
        get<4>(listBossUI[bossIndex].timerList[ccIndex][mapMonster[bossIndex]]) = mapMonster[bossIndex];

        processTimer(boundTime, lowerBoundTime, upperBoundTime, bossIndex, ccIndex, get<4>(listBossUI[bossIndex].timerList[ccIndex][mapMonster[bossIndex]]));

        get<0>(listBossUI[bossIndex].timerList[ccIndex][mapMonster[bossIndex]])->start(1000);

        file->writeTimerBackup(monster->monsterList.size(), bossIndex, ccIndex, mapMonster[bossIndex], boundTime.toString());
    }
}

void MainWindow::linkLabelClick(int index)
{
    QDesktopServices::openUrl( QUrl( std::get<3>(monster->monsterList[index])));
}

void MainWindow::timerUpdate(int bossIndex, int ccIndex, int mapIndex)
{
    qDebug() << "boss: " << bossIndex << " cc: " << ccIndex << " map: " << mapIndex;
    qDebug() << get<1>(listBossUI[bossIndex].timerList[ccIndex][mapIndex]).toString("hh:mm");

    if(mapIndex == mapMonster[bossIndex])
        processTimer(get<1>(listBossUI[bossIndex].timerList[ccIndex][mapIndex]),
                 get<2>(listBossUI[bossIndex].timerList[ccIndex][mapIndex]),
                 get<3>(listBossUI[bossIndex].timerList[ccIndex][mapIndex]), bossIndex, ccIndex, mapIndex);
}

void MainWindow::filterMonster(int bossIndex)
{
    mapFilterMonster[bossIndex] = !mapFilterMonster[bossIndex];

    qDebug() << "Monster:" << std::get<0>(monster->monsterList[bossIndex]) << (mapFilterMonster[bossIndex] ? "checked" : "unchecked");

    if(mapFilterMonster[bossIndex])
    {
        listBossUI[bossIndex].bossImage->hide();
        listBossUI[bossIndex].bossName->hide();
        listBossUI[bossIndex].combo->hide();
        for(int c=0;c<6;c++)
        {
            listBossUI[bossIndex].bossCC[c]->hide();
            listBossUI[bossIndex].button1BossCC[c]->hide();
            listBossUI[bossIndex].button2BossCC[c]->hide();
            listBossUI[bossIndex].timer1BossCC[c]->hide();
            listBossUI[bossIndex].timer2BossCC[c]->hide();
        }
    }
    else
    {
        listBossUI[bossIndex].bossImage->show();
        listBossUI[bossIndex].bossName->show();
        listBossUI[bossIndex].combo->show();
        for(int c=0;c<6;c++)
        {
            listBossUI[bossIndex].bossCC[c]->show();
            listBossUI[bossIndex].button1BossCC[c]->show();
            listBossUI[bossIndex].button2BossCC[c]->show();
            listBossUI[bossIndex].timer1BossCC[c]->show();
            listBossUI[bossIndex].timer2BossCC[c]->show();
        }
    }

    renderMonster();
}

void MainWindow::renderMonster()
{
    numRow = 0;

    for(int i=0, actuali=0;actuali<monster->monsterList.size();actuali++)
    {
        if(mapFilterMonster[actuali])
            continue;

        if(i != 0 && i % numBossesPerRow == 0)
            numRow++;

        listBossUI[actuali].bossImage->move(bossImagex + spaceBetweenBossesx * (i % numBossesPerRow),bossImagey + spaceBetweenBossesy * numRow);
        listBossUI[actuali].combo->move(bossCombox + spaceBetweenBossesx * (i % numBossesPerRow),bossComboy + spaceBetweenBossesy * numRow);
        listBossUI[actuali].bossName->move(bossNamex + spaceBetweenBossesx * (i % numBossesPerRow),bossNamey + spaceBetweenBossesy * numRow);

        for(int c = 0; c < monster->numCC; c++)
        {
            listBossUI[actuali].bossCC[c]->move(bossx + spaceBetweenBossesx * (i % numBossesPerRow),bossy + spaceBetweenBossy * c + spaceBetweenBossesy * numRow);
            listBossUI[actuali].timer1BossCC[c]->move(timerBossx + spaceBetweenBossesx * (i % numBossesPerRow),timerBossy + spaceBetweenTimery * c + spaceBetweenBossesy * numRow);
            listBossUI[actuali].timer2BossCC[c]->move(timerBossx + spaceBetweenTimerx + spaceBetweenBossesx * (i % numBossesPerRow),timerBossy + spaceBetweenTimery * c + spaceBetweenBossesy * numRow);
            listBossUI[actuali].button1BossCC[c]->move(buttonBossx + spaceBetweenBossesx * (i % numBossesPerRow),buttonBossy + spaceBetweenButtony * c + spaceBetweenBossesy * numRow);
            listBossUI[actuali].button2BossCC[c]->move(buttonBossx + spaceBetweenButtonx + spaceBetweenBossesx * (i % numBossesPerRow),buttonBossy + spaceBetweenButtony * c + spaceBetweenBossesy * numRow);
        }

        i++;
    }

    contentWidget->setMinimumSize(width, bossImagey + spaceBetweenBossesy * (numRow + 1));
}

void MainWindow::expandFilters(QPushButton *sidePanelButton, QWidget *sidePanel, QLabel *filterLabel)
{
    displaySideMenu = !displaySideMenu;

    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);

    QPropertyAnimation *animationButton = new QPropertyAnimation(sidePanelButton, "geometry");
    animationButton->setDuration(500);
    animationButton->setStartValue(sidePanelButton->geometry());
    QRect endRectButton = sidePanelButton->geometry();

    QPropertyAnimation *animationPanel = new QPropertyAnimation(sidePanel, "geometry");
    animationPanel->setDuration(500);
    animationPanel->setStartValue(sidePanel->geometry());
    QRect endRectPanel= sidePanel->geometry();
    int panelWidth = endRectPanel.width();

    if(displaySideMenu)
    {
        endRectButton.translate(-panelWidth, 0);
        sidePanelButton->setText("▶");

        filterLabel->show();
        sidePanel->show();
        for(int i=0;i<listBossUI.size();i++)
            listBossUI[i].checkbox->show();

        endRectPanel = QRect(width - panelWidth, 0, panelWidth, sidePanel->height());
    }
    else
    {
        endRectButton.translate(panelWidth, 0);
        sidePanelButton->setText("◀");

        filterLabel->hide();
        for(int i=0;i<listBossUI.size();i++)
            listBossUI[i].checkbox->hide();

        endRectPanel = QRect(width, 0, panelWidth, sidePanel->height());
    }

    animationButton->setEndValue(endRectButton);
    animationPanel->setEndValue(endRectPanel);

    animationButton->setEasingCurve(QEasingCurve::OutCubic);
    animationPanel->setEasingCurve(QEasingCurve::OutCubic);

    group->addAnimation(animationButton);
    group->addAnimation(animationPanel);

    connect(group, &QParallelAnimationGroup::finished, this, [=]() {
        if (!displaySideMenu) {
            sidePanel->hide();
        }
    });

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::changeMap(const QString& map, int bossIndex)
{
    qDebug() << "changeMap: " << map;
    qDebug() << std::get<2>(monster->monsterList[bossIndex]).indexOf(map);

    mapMonster[bossIndex] = std::get<2>(monster->monsterList[bossIndex]).indexOf(map);

    for(int c = 0; c < monster->numCC; c++)
    {
        if(get<1>(listBossUI[bossIndex].timerList[c][mapMonster[bossIndex]]) != QDateTime())
        {
            processTimer(get<1>(listBossUI[bossIndex].timerList[c][mapMonster[bossIndex]]),
                         get<2>(listBossUI[bossIndex].timerList[c][mapMonster[bossIndex]]),
                         get<3>(listBossUI[bossIndex].timerList[c][mapMonster[bossIndex]]), bossIndex, c, mapMonster[bossIndex]);
        }
        else
        {
            listBossUI[bossIndex].timer1BossCC[c]->setText("");
            listBossUI[bossIndex].timer1BossCC[c]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
            listBossUI[bossIndex].timer2BossCC[c]->setText("");
            listBossUI[bossIndex].timer2BossCC[c]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
        }
    }
}

void MainWindow::changeDisplayTime()
{
    displayTime = !displayTime;

    for(int i=0;i< monster->monsterList.size();i++)
        for(int c = 0; c < monster->numCC; c++)
            if(get<0>(listBossUI[i].timerList[c][mapMonster[i]])->isActive())
                processTimer(get<1>(listBossUI[i].timerList[c][mapMonster[i]]),
                             get<2>(listBossUI[i].timerList[c][mapMonster[i]]),
                             get<3>(listBossUI[i].timerList[c][mapMonster[i]]), i, c, mapMonster[i]);
}

void MainWindow::processTimer(QDateTime boundTime, QDateTime lowerBoundTime, QDateTime upperBoundTime, int bossIndex, int ccIndex, int mapIndex)
{
    QDateTime curTime = QDateTime::currentDateTime();
    qDebug() << bossIndex << " --- " << mapIndex;

    if(displayTime)
    {
        qDebug() << boundTime.toString();
        qDebug() << curTime.secsTo(lowerBoundTime);
        if(curTime.secsTo(lowerBoundTime) > 0)
        {
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setText(lowerBoundTime.toString("hh:mm"));
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #ce2f32; color: white; outline: none;");
        }
        else
        {
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setText("");
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
        }

        qDebug() << curTime.secsTo(upperBoundTime);
        if(curTime.secsTo(upperBoundTime) > 0)
        {
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setText(upperBoundTime.toString("hh:mm"));
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #ce2f32; color: white; outline: none;");

            get<1>(listBossUI[bossIndex].timerList[ccIndex][mapIndex]) = boundTime;
            get<2>(listBossUI[bossIndex].timerList[ccIndex][mapIndex]) = lowerBoundTime;
            get<3>(listBossUI[bossIndex].timerList[ccIndex][mapIndex]) = upperBoundTime;
        }
        else
        {
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setText("");
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setStyleSheet("border: 1px solid; font-size: 14px; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
            get<0>(listBossUI[bossIndex].timerList[ccIndex][mapIndex])->stop();
        }
    }
    else
    {
        int differenceTimers1 = curTime.secsTo( lowerBoundTime);
        if(differenceTimers1 > 0)
        {
            QString timer1 = QDateTime(curTime.date() ,QTime(0,0)).addSecs(differenceTimers1).toString("hh:mm");
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setText("•" + timer1);
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #ce2f32; color: white; outline: none;");
        }
        else
        {
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setText("");
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
        }

        int differenceTimers2 = curTime.secsTo( upperBoundTime);
        if(differenceTimers2> 0)
        {
            QString timer2 = QDateTime(curTime.date() ,QTime(0,0)).addSecs(differenceTimers2).toString("hh:mm");

            listBossUI[bossIndex].timer2BossCC[ccIndex]->setText("•" + timer2);
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #ce2f32; color: white; outline: none;");

            get<1>(listBossUI[bossIndex].timerList[ccIndex][mapIndex]) = boundTime;
            get<2>(listBossUI[bossIndex].timerList[ccIndex][mapIndex]) = lowerBoundTime;
            get<3>(listBossUI[bossIndex].timerList[ccIndex][mapIndex]) = upperBoundTime;
        }
        else
        {
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setText("");
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
            get<0>(listBossUI[bossIndex].timerList[ccIndex][mapIndex])->stop();
        }
    }
}
