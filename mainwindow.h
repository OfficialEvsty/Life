#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "launcher.h"
#include <QDialog>
#include "point.h"

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

    QRect dialog_geometry = QRect(900, 560, 500, 400);

    void DialogInit();

private slots:
    void proceedLogic();
    void windowUpdate();
    void start();
};
#endif // MAINWINDOW_H
