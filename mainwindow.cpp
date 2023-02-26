#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "launcher.h"
#include <QPainter>
#include <iostream>
#include <QDebug>
#include <QPalette>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Window, Qt::black);
    setAutoFillBackground(true);
    setPalette(Pal);


    this->windowUpdateTimer = new QTimer();
    connect(windowUpdateTimer, SIGNAL(timeout()), this, SLOT(windowUpdate()));
    this->windowUpdateTimer->start(20);

    DialogInit();
    launcher = new Launcher();

    launcher->RunCtor();
    setMouseTracking(true);
}

void MainWindow::start(){
    this->timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(proceedLogic()));
    MainWindow::launcher->Run(timer);
}

void MainWindow::DialogInit(){
    //label data
    QString game_name = "The Life Game";
    int pixelSize = 25;
    QFont game_font = QFont();
    game_font.setPixelSize(pixelSize);
    //button data
    QString start_game_button_name = "Draw map";
    int start_button_width = 200;
    int start_button_height = 50;
    //dialog data
    QString dialog_title = "Life Settings";


    dialog = new QDialog();
    dialog->setGeometry(dialog_geometry);
    dialog->setWindowTitle(dialog_title);

    QGroupBox *group = new QGroupBox();
    group->setParent(dialog);
    group->setGeometry(0, 0, dialog->geometry().width(), dialog->geometry().height());

    QLabel *game_label = new QLabel();
    game_label->setText(game_name);
    game_label->setParent(group);
    game_label->setAlignment(Qt::AlignCenter);
    game_label->setFixedSize(dialog->geometry().width(), 50);
    game_label->setFont(game_font);
    game_label->show();

    QPushButton *start_game = new QPushButton(group);
    start_game->setText(start_game_button_name);

    QRect start_game_button_size = QRect(dialog->geometry().width()/2 - start_button_width/2, dialog->geometry().height()/2,
                                   start_button_width, start_button_height);
    start_game->setGeometry(start_game_button_size);
    start_game->show();

    connect(start_game, SIGNAL(clicked()), this, SLOT(start()));

    dialog->show();
}

void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    QPen pen(Qt::white, 1, Qt::SolidLine);
    painter.setPen(pen);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    brush.setColor(QColor(255, 255, 255));
    painter.setBrush(brush);

    bool is_game_running = launcher->GetGame() && launcher->IsGameMode();
    if (is_game_running){
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

    bool is_ctor_running = launcher->GetCtor() && launcher->IsCtorMode();
    if (is_ctor_running){
        Constructor *ctor = launcher->GetCtor();
        vector<Point> *points = ctor->GetMap()->GetPoints();
        unsigned int cell_width = ctor->GetSettings()->GetCellWidth();
        for (int i = 0; i < points->size(); i++){
            QRect rect_to_draw = QRect(points->at(i).x * cell_width, points->at(i).y * cell_width, cell_width, cell_width);
            painter.fillRect(rect_to_draw, painter.brush());
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    bool is_ctor_running = launcher->GetCtor() && launcher->IsCtorMode();
    if (is_ctor_running){
        launcher->GetCtor()->EditMap(event->position().rx(), event->position().ry());
    }
}

void MainWindow::proceedLogic(){
    //procedure of class main window
    this->launcher->GetGame()->Proceed();
}

void MainWindow::windowUpdate(){
    this->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

