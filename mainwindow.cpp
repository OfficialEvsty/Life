#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "launcher.h"
#include <QPainter>
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::launcher = new Launcher();
    MainWindow::launcher->Run();
    this->timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(ProceedLogic()));
    timer->start(1000); // И запустим таймер
}

void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    QPen pen(Qt::black, 1, Qt::SolidLine);
    painter.setPen(pen);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    brush.setColor(QColor(0, 0, 0));
    painter.setBrush(brush);

    Life *game = MainWindow::launcher->GetGame();
    Size field_size = game->GetSettings()->GetSizeOfField();
    Cell ***cells = game->GetCells();
    unsigned int cell_width = game->GetSettings()->GetCellWidth();
    for (int i = 0; i < field_size.LengthX; i++)
        for (int j = 0; j < field_size.LengthY; j++){
            if (cells[i][j]->GetAlive()){
                QRect rect_to_draw = QRect(i * cell_width, j * cell_width, cell_width, cell_width);
                painter.fillRect(rect_to_draw, painter.brush());
            }
        }
}

void MainWindow::ProceedLogic(){
    //procedure of class main window
    this->launcher->GetGame()->Proceed();
    this->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

