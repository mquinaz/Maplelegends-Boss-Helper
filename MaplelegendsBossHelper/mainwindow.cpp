#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTimer>
#include <QTime>
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
#include <QVBoxLayout>

#include "monster.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    displayTime = true;
    //scrollArea->setStyleSheet("background: transparent;");
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    this->resize(width, height);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(0, 0, width, height);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);

    QWidget *contentWidget = new QWidget();
    scrollArea->setWidget(contentWidget);

    QPixmap bkgnd(":/images/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    QPushButton *buttonDisplayTimer = new QPushButton(contentWidget);
    buttonDisplayTimer->setStyleSheet("QPushButton {border-image: url(:/images/timeChange.png) stretch; } QPushButton::hover { border-image: url(:/images/timeChangeHover.png) stretch; }");
    buttonDisplayTimer->setGeometry(QRect(width - 75, 25, 50, 50));
    connect(buttonDisplayTimer, &QPushButton::clicked, this, [=]() { changeDisplayTime(); });

    int numCC = 6;
    QFont font("Courier New", 16, QFont::Bold);
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

    for(int i=0;i<(int) monsterList.size();i++)
    {
        if(i != 0 && i % numBossesPerRow == 0)
            numRow++;

        listBossUI.reserve(monsterList.size());
        MonsterUI bossUI;

        bossUI.bossImage = new QLabel(contentWidget);
        bossUI.bossImage->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        bossUI.bossImage->setStyleSheet("border-image: url(:/images/Bosses/" + QString::fromStdString(std::get<0>(monsterList[i])) + ".png) stretch;");
        bossUI.bossImage->setAlignment(Qt::AlignCenter);
        bossUI.bossImage->setGeometry(QRect(bossImagex + spaceBetweenBossesx * (i % numBossesPerRow),bossImagey + spaceBetweenBossesy * numRow,bossImageDimensionx,bossImageDimensiony));

        bossUI.bossName = new QPushButton(contentWidget);
        bossUI.bossName->setStyleSheet("QLabel { color : white; border: 0px;} QPushButton { background-color: #4caf50; color: white; outline: none;}");
        bossUI.bossName->setText(QString::fromStdString(std::get<0>(monsterList[i])));
        bossUI.bossName->setFont(font);
        bossUI.bossName->setGeometry(QRect(bossNamex + spaceBetweenBossesx * (i % numBossesPerRow),bossNamey + spaceBetweenBossesy * numRow,bossNameDimensionx,bossNameDimensiony));
        connect(bossUI.bossName, &QPushButton::clicked, this, [=]() { linkLabelClick(i); });

        bossUI.groupBoss = new QButtonGroup(contentWidget);

        bossUI.bossCC.resize(numCC);
        bossUI.timer1BossCC.resize(numCC);
        bossUI.timer2BossCC.resize(numCC);
        bossUI.button1BossCC.resize(numCC);
        bossUI.button2BossCC.resize(numCC);
        bossUI.timerList.resize(numCC);
        for(int c = 0; c < numCC; c++)
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

            bossUI.timerList[c] = std::make_tuple(new QTimer(this), QTime(), QTime(), QTime());
            connect(get<0>(bossUI.timerList[c]), &QTimer::timeout, this, [=]() { timerUpdate(bossUI.timer1BossCC[c], bossUI.timer2BossCC[c], i, c); });
        }
        listBossUI.push_back(bossUI);
        connect(listBossUI[i].groupBoss, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(timerButtonClick(QAbstractButton*)));
    }

    contentWidget->resize(width, (numRow + 1) * spaceBetweenBossesy);
    qDebug() << "Main window height:" << height;
    qDebug() << "Content height:" << (numRow + 1) * spaceBetweenBossesy;
    //scrollArea->setWidget(contentWidget);
    //QVBoxLayout *mainLayout = new QVBoxLayout(this);
    //mainLayout->addWidget(scrollArea);
    //layout->addWidget(scrollbar);
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
    QString bossIndex = buttonName.mid(buttonBossIndex + 1, buttonCCIndex - buttonBossIndex - 2);
    QString ccIndex = buttonName.mid(buttonCCIndex + 1, buttonName.size());
    qDebug() << buttonName;


    if(buttonName.left(7) == "button2")
    {
        QString descriptionString = "Are you sure you want to reset\nthe timer on boss " +  QString::fromStdString(std::get<0>(monsterList[bossIndex.toInt() - 1])) + " CC" + ccIndex + "?";

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
            get<0>(listBossUI[bossIndex.toInt() - 1].timerList[ccIndex.toInt() - 1])->stop();

            this->findChild<QLabel *>("timer1Boss" + bossIndex + "CC" + ccIndex)->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122);");
            this->findChild<QLabel *>("timer2Boss" + bossIndex + "CC" + ccIndex)->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122);");
            this->findChild<QLabel *>("timer1Boss" + bossIndex + "CC" + ccIndex)->setText("");
            this->findChild<QLabel *>("timer2Boss" + bossIndex + "CC" + ccIndex)->setText("");
            break;
        case QMessageBox::Cancel:
            qDebug( "cancel" );
            break;
        default:
            qDebug( "close" );
            break;
        }
    }
    else if(buttonName.left(7) == "button1" && !get<0>(listBossUI[bossIndex.toInt() - 1].timerList[ccIndex.toInt() - 1])->isActive())
    {
        qDebug() << "Entered";
        QTime boundTime = QTime::currentTime();
        QTime lowerBoundTime = boundTime;
        QTime upperBoundTime = boundTime;

        lowerBoundTime = lowerBoundTime.addSecs(std::get<1>(monsterList[bossIndex.toInt() - 1]) * 0.9 * 60);
        upperBoundTime = upperBoundTime.addSecs(std::get<1>(monsterList[bossIndex.toInt() - 1]) * 1.1 * 60);

        QString timer1, timer2;
        if(displayTime)
        {
            timer1 = lowerBoundTime.toString("hh:mm");
            timer2 = upperBoundTime.toString("hh:mm");
        }
        else
        {
            int boundTimeSeconds = QTime(0,0).secsTo(boundTime);
            timer1 = lowerBoundTime.addSecs(-boundTimeSeconds).toString("hh:mm");
            timer2 = upperBoundTime.addSecs(-boundTimeSeconds).toString("hh:mm");
        }

        this->findChild<QLabel *>("timer1Boss" + bossIndex + "CC" + ccIndex)->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #ce2f32; color: white; outline: none;");
        this->findChild<QLabel *>("timer2Boss" + bossIndex + "CC" + ccIndex)->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #ce2f32; color: white; outline: none;");
        this->findChild<QLabel *>("timer1Boss" + bossIndex + "CC" + ccIndex)->setText(timer1);
        this->findChild<QLabel *>("timer2Boss" + bossIndex + "CC" + ccIndex)->setText(timer2);

        get<1>(listBossUI[bossIndex.toInt() - 1].timerList[ccIndex.toInt() - 1]) = boundTime;
        get<2>(listBossUI[bossIndex.toInt() - 1].timerList[ccIndex.toInt() - 1]) = lowerBoundTime;
        get<3>(listBossUI[bossIndex.toInt() - 1].timerList[ccIndex.toInt() - 1]) = upperBoundTime;
        get<0>(listBossUI[bossIndex.toInt() - 1].timerList[ccIndex.toInt() - 1])->start(1000); //mudar * 60
    }
}

void MainWindow::linkLabelClick(int index)
{
    QDesktopServices::openUrl( QUrl( QString::fromStdString( std::get<2>(monsterList[index]))));
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
                QString timer1 = QTime(0,0).addSecs(differenceTimers1).toString("hh:mm");
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
            QString timer2 = QTime(0,0).addSecs(differenceTimers2).toString("hh:mm");
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
    //atualizar os labels
}
