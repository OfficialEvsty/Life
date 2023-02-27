#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "launcher.h"
#include <QDialog>
#include "point.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QTimer *timer;
    QTimer *windowUpdateTimer;
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    Launcher *launcher = nullptr;
    QDialog *dialog;

    QRect dialog_geometry = QRect(900, 560, 250, 150);

    QLabel *populaty_label = new QLabel(this);
    QLabel *generation_label = new QLabel(this);

    void DialogInit();

private slots:
    void proceedLogic();
    void windowUpdate();
    void start();
    void freezeTimer();
};
#endif // MAINWINDOW_H
