#include "cell.h"

Cell::Cell(int gen, bool status){
    Cell::counter += 1;
    this->id = counter;
    this->generation = gen;
    this->alive = status;
}

unsigned long long int Cell::GetID(){
    return this->id;
}

bool Cell::GetAlive(){
    return this->alive;
}

int Cell::GetGen(){
    return this->generation;
}

void Cell::SetAlive(bool status){
    this->alive = status;
}

void Cell::IncreaseGen(){
    this->generation += 1;
}

void Cell::NullifyGen(){
    this->generation = 0;
}

int Cell::counter = 0;
