#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include "timer.h"

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

    QPixmap bkgnd(":/res/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QLabel *label4 = new QLabel(this);
    label4->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label4->setStyleSheet("border-image: url(:/res/Mano2.png) stretch;");
    label4->setAlignment(Qt::AlignCenter);
    label4->setGeometry(QRect(75,50,150,150));

    QLabel *label6 = new QLabel(this);
    label6->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label6->setAlignment(Qt::AlignCenter);
    label6->setText("-");
    label6->setGeometry(QRect(125,25,50,25));

    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    label->setText("-");
    label->setAlignment(Qt::AlignCenter);
    label->setGeometry(QRect(100,200,100,30));

    QLabel *label2 = new QLabel(this);
    label2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label2->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    label2->setText("-10%");
    label2->setAlignment(Qt::AlignCenter);
    label2->setGeometry(QRect(50,200,50,30));

    QLabel *label3 = new QLabel(this);
    label3->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label3->setStyleSheet("border: 1px solid; border-color:rgba(212,225,229,122); ");
    label3->setText("+10%");
    label3->setAlignment(Qt::AlignCenter);
    label3->setGeometry(QRect(200,200,50,30));

    QPushButton *button = new QPushButton(this);
    button->setStyleSheet("border-image: url(:/res/dead-head.png) stretch;");
    button->setGeometry(QRect(200,300,50,50));
    QObject::connect(&button, &QPushButton::clicked, on_pushButton_clicked);

    Timer t;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //t.ActivateTimer();
}

