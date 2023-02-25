#include "launcher.h"


Launcher::Launcher()
{

}

void Launcher::Run(QTimer *timer){
    Settings::Init(100);
    Life::Init(Settings::Instance);
    this->game = Life::Instance;
    timer->start(200);
    this->is_ctor_mode = false;
    this->is_game_mode = true;
}

void Launcher::RunCtor(){
    Settings::Init(100);
    Constructor::Init(Settings::Instance);
    this->ctor = Constructor::Instance;
    this->is_ctor_mode = true;
    this->is_game_mode = false;
}

Life* Launcher::GetGame(){
    return this->game;
}

Constructor* Launcher::GetCtor(){
    return this->ctor;
}

bool Launcher::IsGameMode(){
    return this->is_game_mode;
}

bool Launcher::IsCtorMode(){
    return this->is_ctor_mode;
}
