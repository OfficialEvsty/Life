#include "settings.h"
#include <iostream>




Size Settings::GetSizeOfField(){
    return this->m_size;
}

unsigned int Settings::GetCellWidth(){
    return this->i_cell_width;
}

unsigned int Settings::GetTimeOfFrame(){
    return this->ui_tick;
}

Settings *Settings::Instance = nullptr;

Settings::Settings(unsigned int tick){
    Size size;
    size.LengthX = 240;
    size.LengthY = 135;
    this->m_size = size;
    this->ui_tick = tick;
}
