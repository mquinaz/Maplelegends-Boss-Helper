#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QAbstractButton>
#include <string>
#include <QDesktopServices>

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

    QLabel *label4 = new QLabel(this);
    label4->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label4->setStyleSheet("border-image: url(:/images/Bosses/" + QString::fromStdString(std::get<0>(monsterList[0])) + ".png) stretch;");
    label4->setAlignment(Qt::AlignCenter);
    label4->setGeometry(QRect(75,50,150,150));

    QPushButton *label6 = new QPushButton(this);
    label6->setStyleSheet("QLabel { color : white; border: 0px;} QPushButton { background-color: #4caf50; color: white; outline: none;}");
    label6->setText(QString::fromStdString(std::get<0>(monsterList[0])));
    QFont font("Courier New", 16, QFont::Bold);
    label6->setFont(font);
    label6->setGeometry(QRect(100,25,100,50));
    connect(label6, SIGNAL(clicked()), this, SLOT(linkLabelClick()));

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
    button->setStyleSheet("QPushButton {border-image: url(:/images/time.png) stretch; } QPushButton::hover { border-image: url(:/images/timeHover.png) stretch; }");
    button->setGeometry(QRect(80,240,50,50));

    QPushButton *button2 = new QPushButton(this);
    button2->setStyleSheet("QPushButton {border-image: url(:/images/cancel.png) stretch; } QPushButton::hover { border-image: url(:/images/cancelHover.png) stretch; }");
    button2->setGeometry(QRect(160,240,50,50));


    QButtonGroup* buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(button);
    buttonGroup->addButton(button2);
    connect(buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(timerButtonClick(QAbstractButton*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::timerButtonClick(QAbstractButton* button)
{
    qDebug() << "Here" << button->text();

    t.activateTimer();
}

void MainWindow::linkLabelClick()
{
    QDesktopServices::openUrl( QUrl( QString::fromStdString( std::get<2>(monsterList[0]))));
}
