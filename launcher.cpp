#include "launcher.h"


Launcher::Launcher()
{

}

void Launcher::Run(){
    Settings::Init(100);
    Life::Init(Settings::Instance);
    this->game = Life::Instance;
}

Life* Launcher::GetGame(){
    return this->game;
}
