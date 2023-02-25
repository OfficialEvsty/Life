#ifndef LAUNCHER_H
#define LAUNCHER_H
#include "life.h"
#include "constructor.h"
#include <QTimer>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Launcher; }
QT_END_NAMESPACE

class Launcher
{
    Constructor *ctor = nullptr;
    Life *game = nullptr;

    bool is_game_mode = false;
    bool is_ctor_mode = false;
public:
    Launcher();
    void Run(QTimer *timer);
    void RunCtor();

    Life* GetGame();
    Constructor* GetCtor();
    bool IsGameMode();
    bool IsCtorMode();
};

#endif // LAUNCHER_H
