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

#include "timer.h"
#include "monster.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    this->setFixedSize(QSize(width, height));

    QPixmap bkgnd(":/images/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

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

    QVector<MonsterUI> listBossUI;

    for(int i=0;i<(int) monsterList.size();i++)
    {
        if(i != 0 && i % numBossesPerRow == 0)
            numRow++;

        MonsterUI bossUI;

        bossUI.bossImage = new QLabel(this);
        bossUI.bossImage->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        bossUI.bossImage->setStyleSheet("border-image: url(:/images/Bosses/" + QString::fromStdString(std::get<0>(monsterList[i])) + ".png) stretch;");
        bossUI.bossImage->setAlignment(Qt::AlignCenter);
        bossUI.bossImage->setGeometry(QRect(bossImagex + spaceBetweenBossesx * (i % numBossesPerRow),bossImagey + spaceBetweenBossesy * numRow,bossImageDimensionx,bossImageDimensiony));

        bossUI.bossName = new QPushButton(this);
        bossUI.bossName->setStyleSheet("QLabel { color : white; border: 0px;} QPushButton { background-color: #4caf50; color: white; outline: none;}");
        bossUI.bossName->setText(QString::fromStdString(std::get<0>(monsterList[i])));
        bossUI.bossName->setFont(font);
        bossUI.bossName->setGeometry(QRect(bossNamex + spaceBetweenBossesx * (i % numBossesPerRow),bossNamey + spaceBetweenBossesy * numRow,bossNameDimensionx,bossNameDimensiony));
        connect(bossUI.bossName, &QPushButton::clicked, this, [=]() { linkLabelClick(i); });

        bossUI.groupBoss = new QButtonGroup(this);

        bossUI.bossCC.resize(numCC);
        bossUI.timer1BossCC.resize(numCC);
        bossUI.timer2BossCC.resize(numCC);
        bossUI.button1BossCC.resize(numCC);
        bossUI.button2BossCC.resize(numCC);
        for(int c = 0; c < numCC; c++)
        {
            bossUI.bossCC[c] = new QLabel(this);
            bossUI.bossCC[c]->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            bossUI.bossCC[c]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
            bossUI.bossCC[c]->setText("CC" + QString::number(c+1));
            bossUI.bossCC[c]->setAlignment(Qt::AlignCenter);
            bossUI.bossCC[c]->setGeometry(QRect(bossx + spaceBetweenBossesx * (i % numBossesPerRow),bossy + spaceBetweenBossy * c + spaceBetweenBossesy * numRow,bossDimensionx,bossDimensiony));

            bossUI.timer1BossCC[c] = new QLabel(this);
            bossUI.timer1BossCC[c]->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            bossUI.timer1BossCC[c]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
            bossUI.timer1BossCC[c]->setText("");
            bossUI.timer1BossCC[c]->setAlignment(Qt::AlignCenter);
            bossUI.timer1BossCC[c]->setGeometry(QRect(timerBossx + spaceBetweenBossesx * (i % numBossesPerRow),timerBossy + spaceBetweenTimery * c + spaceBetweenBossesy * numRow,timerBossDimensionx,timerBossDimensiony));
            bossUI.timer1BossCC[c]->setObjectName("timer1Boss" + QString::number(i + 1) + "CC" + QString::number(c + 1));

            bossUI.timer2BossCC[c] = new QLabel(this);
            bossUI.timer2BossCC[c]->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            bossUI.timer2BossCC[c]->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
            bossUI.timer2BossCC[c]->setText("");
            bossUI.timer2BossCC[c]->setAlignment(Qt::AlignCenter);
            bossUI.timer2BossCC[c]->setGeometry(QRect(timerBossx + spaceBetweenTimerx + spaceBetweenBossesx * (i % numBossesPerRow),timerBossy + spaceBetweenTimery * c + spaceBetweenBossesy * numRow,timerBossDimensionx,timerBossDimensiony));
            bossUI.timer2BossCC[c]->setObjectName("timer2Boss" + QString::number(i + 1) + "CC" + QString::number(c + 1));

            bossUI.button1BossCC[c] = new QPushButton(this);
            bossUI.button1BossCC[c]->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
            bossUI.button1BossCC[c]->setGeometry(QRect(buttonBossx + spaceBetweenBossesx * (i % numBossesPerRow),buttonBossy + spaceBetweenButtony * c + spaceBetweenBossesy * numRow,buttonBossDimensionx,buttonBossDimensiony));
            bossUI.button1BossCC[c]->setObjectName("button1Boss" + QString::number(i + 1) + "CC" + QString::number(c + 1));

            bossUI.button2BossCC[c] = new QPushButton(this);
            bossUI.button2BossCC[c]->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
            bossUI.button2BossCC[c]->setGeometry(QRect(buttonBossx + spaceBetweenButtonx + spaceBetweenBossesx * (i % numBossesPerRow),buttonBossy + spaceBetweenButtony * c + spaceBetweenBossesy * numRow,buttonBossDimensionx,buttonBossDimensiony));
            bossUI.button2BossCC[c]->setObjectName("button2Boss" + QString::number(i + 1) + "CC" + QString::number(c + 1));

            bossUI.groupBoss->addButton(bossUI.button1BossCC[c]);
            bossUI.groupBoss->addButton(bossUI.button2BossCC[c]);
        }
        listBossUI.push_back(bossUI);
        connect(listBossUI[i].groupBoss, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(timerButtonClick(QAbstractButton*)));
    }
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
            this->findChild<QLabel *>("timer1Boss" + bossIndex + "CC" + ccIndex)->setText("");
            break;
        case QMessageBox::Cancel:
            qDebug( "cancel" );
            break;
        default:
            qDebug( "close" );
            break;
        }
    }
    else if(buttonName.left(7) == "button1")
    {
        QTime time = QTime::currentTime();
        QString timeText = time.toString("hh:mm");
        this->findChild<QLabel *>("timer1Boss" + bossIndex + "CC" + ccIndex)->setText(timeText);
        //activate specifc timer
        //t.activateTimer();
    }
}

void MainWindow::linkLabelClick(int index)
{
    QDesktopServices::openUrl( QUrl( QString::fromStdString( std::get<2>(monsterList[index]))));
}

