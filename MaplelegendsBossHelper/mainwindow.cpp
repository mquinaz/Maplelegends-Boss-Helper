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

    QLabel *bossImage1 = new QLabel(this);
    bossImage1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    bossImage1->setStyleSheet("border-image: url(:/images/Bosses/" + QString::fromStdString(std::get<0>(monsterList[0])) + ".png) stretch;");
    bossImage1->setAlignment(Qt::AlignCenter);
    bossImage1->setGeometry(QRect(75,50,150,150));

    QPushButton *bossName1 = new QPushButton(this);
    bossName1->setStyleSheet("QLabel { color : white; border: 0px;} QPushButton { background-color: #4caf50; color: white; outline: none;}");
    bossName1->setText(QString::fromStdString(std::get<0>(monsterList[0])));
    QFont font("Courier New", 16, QFont::Bold);
    bossName1->setFont(font);
    bossName1->setGeometry(QRect(100,25,100,30));
    connect(bossName1, &QPushButton::clicked, this, [=]() { linkLabelClick(0); });

    QLabel *boss1CC1 = new QLabel(this);
    boss1CC1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    boss1CC1->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
    boss1CC1->setText("CC1");
    boss1CC1->setAlignment(Qt::AlignCenter);
    boss1CC1->setGeometry(QRect(50,200,50,30));

    QLabel *timer1Boss1CC1 = new QLabel(this);
    timer1Boss1CC1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer1Boss1CC1->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer1Boss1CC1->setText("");
    timer1Boss1CC1->setAlignment(Qt::AlignCenter);
    timer1Boss1CC1->setGeometry(QRect(100,200,50,30));
    timer1Boss1CC1->setObjectName("timer1Boss1CC1");

    QLabel *timer2Boss1CC1 = new QLabel(this);
    timer2Boss1CC1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer2Boss1CC1->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer2Boss1CC1->setText("");
    timer2Boss1CC1->setAlignment(Qt::AlignCenter);
    timer2Boss1CC1->setGeometry(QRect(150,200,50,30));

    QPushButton *button1Boss1CC1 = new QPushButton(this);
    button1Boss1CC1->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button1Boss1CC1->setGeometry(QRect(210,200,30,30));
    button1Boss1CC1->setObjectName("button1Boss1CC1");

    QPushButton *button2Boss1CC1 = new QPushButton(this);
    button2Boss1CC1->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2Boss1CC1->setGeometry(QRect(250,200,30,30));
    button2Boss1CC1->setObjectName("button2Boss1CC1");

    QLabel *boss1CC2 = new QLabel(this);
    boss1CC2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    boss1CC2->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
    boss1CC2->setText("CC2");
    boss1CC2->setAlignment(Qt::AlignCenter);
    boss1CC2->setGeometry(QRect(50,230,50,30));

    QLabel *timer1Boss1CC2 = new QLabel(this);
    timer1Boss1CC2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer1Boss1CC2->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer1Boss1CC2->setText("");
    timer1Boss1CC2->setAlignment(Qt::AlignCenter);
    timer1Boss1CC2->setGeometry(QRect(100,230,50,30));

    QLabel *timer2Boss1CC2 = new QLabel(this);
    timer2Boss1CC2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer2Boss1CC2->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer2Boss1CC2->setText("");
    timer2Boss1CC2->setAlignment(Qt::AlignCenter);
    timer2Boss1CC2->setGeometry(QRect(150,230,50,30));

    QPushButton *button1Boss1CC2 = new QPushButton(this);
    button1Boss1CC2->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button1Boss1CC2->setGeometry(QRect(210,230,30,30));
    button1Boss1CC2->setObjectName("button1Boss1CC2");

    QPushButton *button2Boss1CC2 = new QPushButton(this);
    button2Boss1CC2->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2Boss1CC2->setGeometry(QRect(250,230,30,30));
    button2Boss1CC2->setObjectName("button2Boss1CC2");

    QLabel *boss1CC3 = new QLabel(this);
    boss1CC3->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    boss1CC3->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
    boss1CC3->setText("CC3");
    boss1CC3->setAlignment(Qt::AlignCenter);
    boss1CC3->setGeometry(QRect(50,260,50,30));

    QLabel *timer1Boss1CC3 = new QLabel(this);
    timer1Boss1CC3->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer1Boss1CC3->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer1Boss1CC3->setText("");
    timer1Boss1CC3->setAlignment(Qt::AlignCenter);
    timer1Boss1CC3->setGeometry(QRect(100,260,50,30));

    QLabel *timer2Boss1CC3 = new QLabel(this);
    timer2Boss1CC3->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer2Boss1CC3->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer2Boss1CC3->setText("");
    timer2Boss1CC3->setAlignment(Qt::AlignCenter);
    timer2Boss1CC3->setGeometry(QRect(150,260,50,30));

    QPushButton *button1Boss1CC3 = new QPushButton(this);
    button1Boss1CC3->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button1Boss1CC3->setGeometry(QRect(210,260,30,30));
    button1Boss1CC3->setObjectName("button1Boss1CC3");

    QPushButton *button2Boss1CC3 = new QPushButton(this);
    button2Boss1CC3->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2Boss1CC3->setGeometry(QRect(250,260,30,30));
    button2Boss1CC3->setObjectName("button2Boss1CC3");

    QLabel *boss1CC4 = new QLabel(this);
    boss1CC4->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    boss1CC4->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
    boss1CC4->setText("CC4");
    boss1CC4->setAlignment(Qt::AlignCenter);
    boss1CC4->setGeometry(QRect(50,290,50,30));

    QLabel *timer1Boss1CC4 = new QLabel(this);
    timer1Boss1CC4->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer1Boss1CC4->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer1Boss1CC4->setText("");
    timer1Boss1CC4->setAlignment(Qt::AlignCenter);
    timer1Boss1CC4->setGeometry(QRect(100,290,50,30));

    QLabel *timer2Boss1CC4 = new QLabel(this);
    timer2Boss1CC4->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer2Boss1CC4->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer2Boss1CC4->setText("");
    timer2Boss1CC4->setAlignment(Qt::AlignCenter);
    timer2Boss1CC4->setGeometry(QRect(150,290,50,30));

    QPushButton *button1Boss1CC4 = new QPushButton(this);
    button1Boss1CC4->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button1Boss1CC4->setGeometry(QRect(210,290,30,30));
    button1Boss1CC4->setObjectName("button1Boss1CC4");

    QPushButton *button2Boss1CC4 = new QPushButton(this);
    button2Boss1CC4->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2Boss1CC4->setGeometry(QRect(250,290,30,30));
    button2Boss1CC4->setObjectName("button2Boss1CC4");

    QLabel *boss1CC5 = new QLabel(this);
    boss1CC5->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    boss1CC5->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
    boss1CC5->setText("CC5");
    boss1CC5->setAlignment(Qt::AlignCenter);
    boss1CC5->setGeometry(QRect(50,320,50,30));

    QLabel *timer1Boss1CC5 = new QLabel(this);
    timer1Boss1CC5->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer1Boss1CC5->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer1Boss1CC5->setText("");
    timer1Boss1CC5->setAlignment(Qt::AlignCenter);
    timer1Boss1CC5->setGeometry(QRect(100,320,50,30));

    QLabel *timer2Boss1CC5 = new QLabel(this);
    timer2Boss1CC5->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer2Boss1CC5->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer2Boss1CC5->setText("");
    timer2Boss1CC5->setAlignment(Qt::AlignCenter);
    timer2Boss1CC5->setGeometry(QRect(150,320,50,30));

    QPushButton *button1Boss1CC5 = new QPushButton(this);
    button1Boss1CC5->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button1Boss1CC5->setGeometry(QRect(210,320,30,30));
    button1Boss1CC5->setObjectName("button1Boss1CC5");

    QPushButton *button2Boss1CC5 = new QPushButton(this);
    button2Boss1CC5->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2Boss1CC5->setGeometry(QRect(250,320,30,30));
    button2Boss1CC5->setObjectName("button2Boss1CC5");

    QLabel *boss1CC6 = new QLabel(this);
    boss1CC6->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    boss1CC6->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
    boss1CC6->setText("CC6");
    boss1CC6->setAlignment(Qt::AlignCenter);
    boss1CC6->setGeometry(QRect(50,350,50,30));

    QLabel *timer1Boss1CC6 = new QLabel(this);
    timer1Boss1CC6->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer1Boss1CC6->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer1Boss1CC6->setText("");
    timer1Boss1CC6->setAlignment(Qt::AlignCenter);
    timer1Boss1CC6->setGeometry(QRect(100,350,50,30));

    QLabel *timer2Boss1CC6 = new QLabel(this);
    timer2Boss1CC6->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer2Boss1CC6->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer2Boss1CC6->setText("");
    timer2Boss1CC6->setAlignment(Qt::AlignCenter);
    timer2Boss1CC6->setGeometry(QRect(150,350,50,30));

    QPushButton *button1Boss1CC6 = new QPushButton(this);
    button1Boss1CC6->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button1Boss1CC6->setGeometry(QRect(210,350,30,30));
    button1Boss1CC6->setObjectName("button1Boss1CC6");

    QPushButton *button2Boss1CC6 = new QPushButton(this);
    button2Boss1CC6->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2Boss1CC6->setGeometry(QRect(250,350,30,30));
    button2Boss1CC6->setObjectName("button2Boss1CC6");

    QButtonGroup* groupBoss1 = new QButtonGroup(this);
    groupBoss1->addButton(button1Boss1CC1);
    groupBoss1->addButton(button2Boss1CC1);
    groupBoss1->addButton(button1Boss1CC2);
    groupBoss1->addButton(button2Boss1CC2);
    groupBoss1->addButton(button1Boss1CC3);
    groupBoss1->addButton(button2Boss1CC3);
    groupBoss1->addButton(button1Boss1CC4);
    groupBoss1->addButton(button2Boss1CC4);
    groupBoss1->addButton(button1Boss1CC5);
    groupBoss1->addButton(button2Boss1CC5);
    groupBoss1->addButton(button1Boss1CC6);
    groupBoss1->addButton(button2Boss1CC6);
    connect(groupBoss1, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(timerButtonClick(QAbstractButton*)));



    QLabel *bossImage2 = new QLabel(this);
    bossImage2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    bossImage2->setStyleSheet("border-image: url(:/images/Bosses/" + QString::fromStdString(std::get<0>(monsterList[1])) + ".png) stretch;");
    bossImage2->setAlignment(Qt::AlignCenter);
    bossImage2->setGeometry(QRect(375,50,150,150));

    QPushButton *bossName2 = new QPushButton(this);
    bossName2->setStyleSheet("QLabel { color : white; border: 0px;} QPushButton { background-color: #4caf50; color: white; outline: none;}");
    bossName2->setText(QString::fromStdString(std::get<0>(monsterList[1])));
    bossName2->setFont(font);
    bossName2->setGeometry(QRect(400,25,100,30));
    connect(bossName2, &QPushButton::clicked, this, [=]() { linkLabelClick(1); });

    QLabel *boss2CC1 = new QLabel(this);
    boss2CC1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    boss2CC1->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
    boss2CC1->setText("CC1");
    boss2CC1->setAlignment(Qt::AlignCenter);
    boss2CC1->setGeometry(QRect(350,200,50,30));

    QLabel *timer1Boss2CC1 = new QLabel(this);
    timer1Boss2CC1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer1Boss2CC1->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer1Boss2CC1->setText("");
    timer1Boss2CC1->setAlignment(Qt::AlignCenter);
    timer1Boss2CC1->setGeometry(QRect(400,200,50,30));
    timer1Boss2CC1->setObjectName("timer1Boss2CC1");

    QLabel *timer2Boss2CC1 = new QLabel(this);
    timer2Boss2CC1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer2Boss2CC1->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer2Boss2CC1->setText("");
    timer2Boss2CC1->setAlignment(Qt::AlignCenter);
    timer2Boss2CC1->setGeometry(QRect(450,200,50,30));

    QPushButton *button1Boss2CC1 = new QPushButton(this);
    button1Boss2CC1->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button1Boss2CC1->setGeometry(QRect(510,200,30,30));
    button1Boss2CC1->setObjectName("button1Boss2CC1");

    QPushButton *button2Boss2CC1 = new QPushButton(this);
    button2Boss2CC1->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2Boss2CC1->setGeometry(QRect(550,200,30,30));
    button2Boss2CC1->setObjectName("button2Boss2CC1");

    QLabel *boss2CC2 = new QLabel(this);
    boss2CC2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    boss2CC2->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
    boss2CC2->setText("CC2");
    boss2CC2->setAlignment(Qt::AlignCenter);
    boss2CC2->setGeometry(QRect(350,230,50,30));

    QLabel *timer1Boss2CC2 = new QLabel(this);
    timer1Boss2CC2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer1Boss2CC2->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer1Boss2CC2->setText("");
    timer1Boss2CC2->setAlignment(Qt::AlignCenter);
    timer1Boss2CC2->setGeometry(QRect(400,230,50,30));

    QLabel *timer2Boss2CC2 = new QLabel(this);
    timer2Boss2CC2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer2Boss2CC2->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer2Boss2CC2->setText("");
    timer2Boss2CC2->setAlignment(Qt::AlignCenter);
    timer2Boss2CC2->setGeometry(QRect(450,230,50,30));

    QPushButton *button1Boss2CC2 = new QPushButton(this);
    button1Boss2CC2->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button1Boss2CC2->setGeometry(QRect(510,230,30,30));
    button1Boss2CC2->setObjectName("button1Boss2CC2");

    QPushButton *button2Boss2CC2 = new QPushButton(this);
    button2Boss2CC2->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2Boss2CC2->setGeometry(QRect(550,230,30,30));
    button2Boss2CC2->setObjectName("button2Boss2CC2");

    QLabel *boss2CC3 = new QLabel(this);
    boss2CC3->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    boss2CC3->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
    boss2CC3->setText("CC3");
    boss2CC3->setAlignment(Qt::AlignCenter);
    boss2CC3->setGeometry(QRect(350,260,50,30));

    QLabel *timer1Boss2CC3 = new QLabel(this);
    timer1Boss2CC3->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer1Boss2CC3->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer1Boss2CC3->setText("");
    timer1Boss2CC3->setAlignment(Qt::AlignCenter);
    timer1Boss2CC3->setGeometry(QRect(400,260,50,30));

    QLabel *timer2Boss2CC3 = new QLabel(this);
    timer2Boss2CC3->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer2Boss2CC3->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer2Boss2CC3->setText("");
    timer2Boss2CC3->setAlignment(Qt::AlignCenter);
    timer2Boss2CC3->setGeometry(QRect(450,260,50,30));

    QPushButton *button1Boss2CC3 = new QPushButton(this);
    button1Boss2CC3->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button1Boss2CC3->setGeometry(QRect(510,260,30,30));
    button1Boss2CC3->setObjectName("button1Boss2CC3");

    QPushButton *button2Boss2CC3 = new QPushButton(this);
    button2Boss2CC3->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2Boss2CC3->setGeometry(QRect(550,260,30,30));
    button2Boss2CC3->setObjectName("button2Boss2CC3");

    QLabel *boss2CC4 = new QLabel(this);
    boss2CC4->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    boss2CC4->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
    boss2CC4->setText("CC4");
    boss2CC4->setAlignment(Qt::AlignCenter);
    boss2CC4->setGeometry(QRect(350,290,50,30));

    QLabel *timer1Boss2CC4 = new QLabel(this);
    timer1Boss2CC4->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer1Boss2CC4->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer1Boss2CC4->setText("");
    timer1Boss2CC4->setAlignment(Qt::AlignCenter);
    timer1Boss2CC4->setGeometry(QRect(400,290,50,30));

    QLabel *timer2Boss2CC4 = new QLabel(this);
    timer2Boss2CC4->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer2Boss2CC4->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer2Boss2CC4->setText("");
    timer2Boss2CC4->setAlignment(Qt::AlignCenter);
    timer2Boss2CC4->setGeometry(QRect(450,290,50,30));

    QPushButton *button1Boss2CC4 = new QPushButton(this);
    button1Boss2CC4->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button1Boss2CC4->setGeometry(QRect(510,290,30,30));
    button1Boss2CC4->setObjectName("button1Boss2CC4");

    QPushButton *button2Boss2CC4 = new QPushButton(this);
    button2Boss2CC4->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2Boss2CC4->setGeometry(QRect(550,290,30,30));
    button2Boss2CC4->setObjectName("button2Boss2CC4");

    QLabel *boss2CC5 = new QLabel(this);
    boss2CC5->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    boss2CC5->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
    boss2CC5->setText("CC5");
    boss2CC5->setAlignment(Qt::AlignCenter);
    boss2CC5->setGeometry(QRect(350,320,50,30));

    QLabel *timer1Boss2CC5 = new QLabel(this);
    timer1Boss2CC5->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer1Boss2CC5->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer1Boss2CC5->setText("");
    timer1Boss2CC5->setAlignment(Qt::AlignCenter);
    timer1Boss2CC5->setGeometry(QRect(400,320,50,30));

    QLabel *timer2Boss2CC5 = new QLabel(this);
    timer2Boss2CC5->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer2Boss2CC5->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer2Boss2CC5->setText("");
    timer2Boss2CC5->setAlignment(Qt::AlignCenter);
    timer2Boss2CC5->setGeometry(QRect(450,320,50,30));

    QPushButton *button1Boss2CC5 = new QPushButton(this);
    button1Boss2CC5->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button1Boss2CC5->setGeometry(QRect(510,320,30,30));
    button1Boss2CC5->setObjectName("button1Boss2CC5");

    QPushButton *button2Boss2CC5 = new QPushButton(this);
    button2Boss2CC5->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2Boss2CC5->setGeometry(QRect(550,320,30,30));
    button2Boss2CC5->setObjectName("button2Boss2CC5");

    QLabel *boss2CC6 = new QLabel(this);
    boss2CC6->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    boss2CC6->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); background-color: #4caf50; color: white; outline: none;");
    boss2CC6->setText("CC6");
    boss2CC6->setAlignment(Qt::AlignCenter);
    boss2CC6->setGeometry(QRect(350,350,50,30));

    QLabel *timer1Boss2CC6 = new QLabel(this);
    timer1Boss2CC6->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer1Boss2CC6->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer1Boss2CC6->setText("");
    timer1Boss2CC6->setAlignment(Qt::AlignCenter);
    timer1Boss2CC6->setGeometry(QRect(400,350,50,30));

    QLabel *timer2Boss2CC6 = new QLabel(this);
    timer2Boss2CC6->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer2Boss2CC6->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    timer2Boss2CC6->setText("");
    timer2Boss2CC6->setAlignment(Qt::AlignCenter);
    timer2Boss2CC6->setGeometry(QRect(450,350,50,30));

    QPushButton *button1Boss2CC6 = new QPushButton(this);
    button1Boss2CC6->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button1Boss2CC6->setGeometry(QRect(510,350,30,30));
    button1Boss2CC6->setObjectName("button1Boss2CC6");

    QPushButton *button2Boss2CC6 = new QPushButton(this);
    button2Boss2CC6->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2Boss2CC6->setGeometry(QRect(550,350,30,30));
    button2Boss2CC6->setObjectName("button2Boss2CC6");

    QButtonGroup* groupBoss2 = new QButtonGroup(this);
    groupBoss2->addButton(button1Boss2CC1);
    groupBoss2->addButton(button2Boss2CC1);
    groupBoss2->addButton(button1Boss2CC2);
    groupBoss2->addButton(button2Boss2CC2);
    groupBoss2->addButton(button1Boss2CC3);
    groupBoss2->addButton(button2Boss2CC3);
    groupBoss2->addButton(button1Boss2CC4);
    groupBoss2->addButton(button2Boss2CC4);
    groupBoss2->addButton(button1Boss2CC5);
    groupBoss2->addButton(button2Boss2CC5);
    groupBoss2->addButton(button1Boss2CC6);
    groupBoss2->addButton(button2Boss2CC6);
    connect(groupBoss2, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(timerButtonClick(QAbstractButton*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::timerButtonClick(QAbstractButton* button)
{
    QString buttonName = button->objectName();
    qDebug() << buttonName;

    if(buttonName.left(7) == "button2")
    {
        std::string data = buttonName.toStdString();
        std::string bossIndex = data.substr( data.find("Boss") + 4, data.find("CC") - data.find("Boss") - 4);
        std::string ccIndex = data.substr(data.find("CC") + 2, data.size());

        std::string descriptionString = "Are you sure you want to reset\nthe timer on boss " + std::get<0>(monsterList[stoi(bossIndex) - 1]) + " CC" + ccIndex + "?";
        char description[descriptionString.size() + 1];
        description[descriptionString.size()] = '\0';
        std::copy(descriptionString.begin(), descriptionString.end(), description);

        switch( QMessageBox::question(
            this,
            tr("Reset Timer"),
            tr(description),

            QMessageBox::Yes |
                QMessageBox::Cancel,

            QMessageBox::Cancel ) )
        {
        case QMessageBox::Yes:
            qDebug( "yes" );
            //need to reset timer
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
        this->findChild<QLabel*>("timer1Boss1CC1")->setText(timeText);
        //activate specifc timer
        //t.activateTimer();
    }
}

void MainWindow::linkLabelClick(int index)
{
    //QPushButton *button = qobject_cast<QPushButton*>(sender());
    //int index = button->objectName();
    QDesktopServices::openUrl( QUrl( QString::fromStdString( std::get<2>(monsterList[index]))));
}
