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

#include "monster.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    monster = new Monster();

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    this->resize(width, height);

    displayTime = true;

    QFont font("Courier New", 16, QFont::Bold);
    int buttonDisplayx = width - 75, buttonDisplayy = 25, buttonDisplayDimensionx = 50, buttonDisplayDimensiony = 50;
    int bossImagex = 75, bossImagey = 50, bossImageDimensionx = 150, bossImageDimensiony = 150;
    int bossNamex = 75, bossNamey = 25, bossNameDimensionx = 175, bossNameDimensiony = 30;
    int bossx = 50, bossy = 200, bossDimensionx = 50, bossDimensiony = 30;
    int spaceBetweenBossy = 30;
    int timerBossx = 100, timerBossy = 200, timerBossDimensionx = 50, timerBossDimensiony = 30;
    int spaceBetweenTimerx = 50, spaceBetweenTimery = 30;
    int buttonBossx = 210, buttonBossy = 200, buttonBossDimensionx = 30, buttonBossDimensiony = 30;
    int spaceBetweenButtonx = 40, spaceBetweenButtony = 30;
    int spaceBetweenBossesx = 300, spaceBetweenBossesy = 400;
    int numRow = 0;
    int numBossesPerRow = width / spaceBetweenBossesx;

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("background: transparent;");
    scrollArea->setGeometry(0, 0, width, height);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);

    QWidget *contentWidget = new QWidget();

    QPixmap bkgnd(":/images/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    QPushButton *buttonDisplayTimer = new QPushButton(contentWidget);
    buttonDisplayTimer->setStyleSheet("QPushButton {border-image: url(:/images/timeChange.png) stretch; } QPushButton::hover { border-image: url(:/images/timeChangeHover.png) stretch; }");
    buttonDisplayTimer->setGeometry(QRect(buttonDisplayx, buttonDisplayy, buttonDisplayDimensionx, buttonDisplayDimensiony));
    connect(buttonDisplayTimer, &QPushButton::clicked, this, [=]() { changeDisplayTime(); });

    for(int i=0;i< monster->monsterList.size();i++)
    {
        if(i != 0 && i % numBossesPerRow == 0)
            numRow++;

        listBossUI.reserve(monster->monsterList.size());
        MonsterUI bossUI;

        bossUI.bossImage = new QLabel(contentWidget);
        bossUI.bossImage->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        bossUI.bossImage->setStyleSheet("border-image: url(:/images/Bosses/" + std::get<0>(monster->monsterList[i]) + ".png) stretch;");
        bossUI.bossImage->setAlignment(Qt::AlignCenter);
        bossUI.bossImage->setGeometry(QRect(bossImagex + spaceBetweenBossesx * (i % numBossesPerRow),bossImagey + spaceBetweenBossesy * numRow,bossImageDimensionx,bossImageDimensiony));

        bossUI.bossName = new QPushButton(contentWidget);
        bossUI.bossName->setStyleSheet("QLabel { color : white; border: 0px;} QPushButton { background-color: #4caf50; color: white; outline: none;}");
        bossUI.bossName->setText(std::get<0>(monster->monsterList[i]));
        bossUI.bossName->setFont(font);
        bossUI.bossName->setGeometry(QRect(bossNamex + spaceBetweenBossesx * (i % numBossesPerRow),bossNamey + spaceBetweenBossesy * numRow,bossNameDimensionx,bossNameDimensiony));
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

            bossUI.timerList[c] = std::make_tuple(new QTimer(this), QDateTime(), QDateTime(), QDateTime());
            connect(get<0>(bossUI.timerList[c]), &QTimer::timeout, this, [=]() { timerUpdate(bossUI.timer1BossCC[c], bossUI.timer2BossCC[c], i, c); });
        }
        listBossUI.push_back(bossUI);
        connect(listBossUI[i].groupBoss, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(timerButtonClick(QAbstractButton*)));
    }

    file = new Backup(monster->numCC, monster->monsterList);
    for(auto it : file->backupTimerToProcess)
        activateTimer(get<0>(it), get<1>(it), get<2>(it));

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

            get<0>(listBossUI[bossIndex].timerList[ccIndex])->stop();

            listBossUI[bossIndex].timer1BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122);");
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122);");
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setText("");
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setText("");

            file->formatTimerBackup(bossIndex, ccIndex);
            file->writeTimerBackup(monster->monsterList.size());

            break;
        case QMessageBox::Cancel:
            qDebug( "cancel" );
            break;
        default:
            qDebug( "close" );
            break;
        }
    }
    else if(buttonName.left(7) == "button1" && !get<0>(listBossUI[bossIndex].timerList[ccIndex])->isActive())
    {
        QDateTime boundTime = QDateTime::currentDateTime();

        activateTimer(boundTime, bossIndex, ccIndex);

        file->formatTimerBackup(bossIndex, ccIndex, boundTime.toString());
        file->writeTimerBackup(monster->monsterList.size());
    }
}

void MainWindow::linkLabelClick(int index)
{
    QDesktopServices::openUrl( QUrl( std::get<2>(monster->monsterList[index])));
}

void MainWindow::activateTimer(QDateTime boundTime, int bossIndex, int ccIndex)
{
    QDateTime lowerBoundTime = boundTime;
    QDateTime upperBoundTime = boundTime;

    lowerBoundTime = lowerBoundTime.addSecs(std::get<1>(monster->monsterList[bossIndex]) * 0.9 * 60);
    upperBoundTime = upperBoundTime.addSecs(std::get<1>(monster->monsterList[bossIndex]) * 1.1 * 60);

    QDateTime curTime = QDateTime::currentDateTime();

    if(displayTime)
    {
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

            get<1>(listBossUI[bossIndex].timerList[ccIndex]) = boundTime;
            get<2>(listBossUI[bossIndex].timerList[ccIndex]) = lowerBoundTime;
            get<3>(listBossUI[bossIndex].timerList[ccIndex]) = upperBoundTime;
            get<0>(listBossUI[bossIndex].timerList[ccIndex])->start(1000); //mudar * 60
        }
        else
        {
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setText("");
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
            get<0>(listBossUI[bossIndex].timerList[ccIndex])->stop();
        }
    }
    else
    {
        int boundTimeSeconds = QDateTime(boundTime.date() ,QTime(0,0)).secsTo(boundTime);
        if(curTime.secsTo(lowerBoundTime) > 0)
        {
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setText(lowerBoundTime.addSecs(-boundTimeSeconds).toString("hh:mm"));
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #ce2f32; color: white; outline: none;");
        }
        else
        {
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setText("");
            listBossUI[bossIndex].timer1BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
        }

        if(curTime.secsTo(upperBoundTime) > 0)
        {
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setText(upperBoundTime.addSecs(-boundTimeSeconds).toString("hh:mm"));
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #ce2f32; color: white; outline: none;");
            get<1>(listBossUI[bossIndex].timerList[ccIndex]) = boundTime;
            get<2>(listBossUI[bossIndex].timerList[ccIndex]) = lowerBoundTime;
            get<3>(listBossUI[bossIndex].timerList[ccIndex]) = upperBoundTime;
            get<0>(listBossUI[bossIndex].timerList[ccIndex])->start(1000); //mudar * 60
        }
        else
        {
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setText("");
            listBossUI[bossIndex].timer2BossCC[ccIndex]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
            get<0>(listBossUI[bossIndex].timerList[ccIndex])->stop();
        }
    }
}

void MainWindow::timerUpdate(QLabel *labelTimer1, QLabel *labelTimer2, int bossIndex, int ccIndex)
{
    if(displayTime)
    {
        get<1>(listBossUI[bossIndex].timerList[ccIndex]) = get<1>(listBossUI[bossIndex].timerList[ccIndex]).addSecs(1 * 60);

        qDebug() << get<1>(listBossUI[bossIndex].timerList[ccIndex]).toString("hh:mm");
        qDebug() << get<2>(listBossUI[bossIndex].timerList[ccIndex]).toString("hh:mm");
        qDebug() << get<3>(listBossUI[bossIndex].timerList[ccIndex]).toString("hh:mm");

        if(labelTimer1->text() != "")
        {
            int differenceTimers1 = get<1>(listBossUI[bossIndex].timerList[ccIndex]).secsTo( get<2>(listBossUI[bossIndex].timerList[ccIndex]));
            qDebug() << differenceTimers1;
            if(differenceTimers1 > 0)
            {
                QString timer1 = get<2>(listBossUI[bossIndex].timerList[ccIndex]).toString("hh:mm");
                labelTimer1->setText(timer1);
            }
            else if(differenceTimers1 <= 0)
            {
                labelTimer1->setText("");
                labelTimer1->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
            }
        }

        int differenceTimers2 = get<1>(listBossUI[bossIndex].timerList[ccIndex]).secsTo( get<3>(listBossUI[bossIndex].timerList[ccIndex]));
        qDebug() << differenceTimers2;
        if(differenceTimers2 > 0)
        {
            QString timer2 = get<3>(listBossUI[bossIndex].timerList[ccIndex]).toString("hh:mm");
            labelTimer2->setText(timer2);
        }
        else if(differenceTimers2 <= 0)
        {
            labelTimer2->setText("");
            labelTimer2->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
            get<0>(listBossUI[bossIndex].timerList[ccIndex])->stop();
        }
    }
    else
    {
        get<1>(listBossUI[bossIndex].timerList[ccIndex]) = get<1>(listBossUI[bossIndex].timerList[ccIndex]).addSecs(1 * 60);

        qDebug() << get<1>(listBossUI[bossIndex].timerList[ccIndex]).toString("hh:mm");
        qDebug() << get<2>(listBossUI[bossIndex].timerList[ccIndex]).toString("hh:mm");
        qDebug() << get<3>(listBossUI[bossIndex].timerList[ccIndex]).toString("hh:mm");

        if(labelTimer1->text() != "")
        {
            int differenceTimers1 = get<1>(listBossUI[bossIndex].timerList[ccIndex]).secsTo( get<2>(listBossUI[bossIndex].timerList[ccIndex]));
            qDebug() << differenceTimers1;
            if(differenceTimers1 > 0)
            {
                QString timer1 = QDateTime(get<1>(listBossUI[bossIndex].timerList[ccIndex]).date() ,QTime(0,0)).addSecs(differenceTimers1).toString("hh:mm");
                labelTimer1->setText(timer1);
            }
            else if(differenceTimers1 <= 0)
            {
                labelTimer1->setText("");
                labelTimer1->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
            }
        }

        int differenceTimers2 = get<1>(listBossUI[bossIndex].timerList[ccIndex]).secsTo( get<3>(listBossUI[bossIndex].timerList[ccIndex]));
        qDebug() << differenceTimers2;
        if(differenceTimers2 > 0)
        {
            QString timer2 = QDateTime(get<1>(listBossUI[bossIndex].timerList[ccIndex]).date() ,QTime(0,0)).addSecs(differenceTimers2).toString("hh:mm");
            labelTimer2->setText(timer2);
        }
        else if(differenceTimers2 <= 0)
        {
            labelTimer2->setText("");
            labelTimer2->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
            get<0>(listBossUI[bossIndex].timerList[ccIndex])->stop();
        }
    }
}

void MainWindow::changeDisplayTime()
{
    displayTime = !displayTime;

    for(int i=0;i< monster->monsterList.size();i++)
    {
        for(int c = 0; c < monster->numCC; c++)
        {
            QString timer1, timer2;
            if(displayTime)
            {
                timer1 = get<2>(listBossUI[i].timerList[c]).toString("hh:mm");
                timer2 = get<3>(listBossUI[i].timerList[c]).toString("hh:mm");
            }
            else
            {
                int differenceTimers1 = get<1>(listBossUI[i].timerList[c]).secsTo( get<2>(listBossUI[i].timerList[c]));
                int differenceTimers2 = get<1>(listBossUI[i].timerList[c]).secsTo( get<3>(listBossUI[i].timerList[c]));
                timer1 = QDateTime(get<1>(listBossUI[i].timerList[c]).date() ,QTime(0,0)).addSecs(differenceTimers1).toString("hh:mm");
                timer2 = QDateTime(get<1>(listBossUI[i].timerList[c]).date() ,QTime(0,0)).addSecs(differenceTimers2).toString("hh:mm");
            }

            if(listBossUI[i].timer1BossCC[c]->text() != "")
                listBossUI[i].timer1BossCC[c]->setText(timer1);
            if(listBossUI[i].timer2BossCC[c]->text() != "")
                listBossUI[i].timer2BossCC[c]->setText(timer2);
        }
    }
}

