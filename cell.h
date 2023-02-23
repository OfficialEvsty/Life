#ifndef CELL_H
#define CELL_H

class Cell{
    unsigned long long int id;
    int generation;
    bool alive;
    static int counter;

public:
    Cell(int gen = 0, bool status = false);
    unsigned long long int GetID();
    bool GetAlive();
    int GetGen();

    void SetAlive(bool status);
    void IncreaseGen();
    void NullifyGen();
};

#endif // CELL_H
