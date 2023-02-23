#ifndef LAUNCHER_H
#define LAUNCHER_H
#include "life.h"
#include <QTimer>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Launcher; }
QT_END_NAMESPACE

class Launcher
{
    Life *game;
public:
    Launcher();
    void Run();
    Life* GetGame();
};

#endif // LAUNCHER_H
