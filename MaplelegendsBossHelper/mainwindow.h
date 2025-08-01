#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void timerButtonClick(QAbstractButton*);
    void linkLabelClick(int index);

    void timerUpdate(QLabel *labelTimer1, QLabel *labelTimer2, int bossIndex, int ccIndex);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
