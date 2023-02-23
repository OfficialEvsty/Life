#ifndef CELL_H
#define CELL_H

class Cell{
    unsigned long long int id;
    int generation;
    bool alive;
    bool is_alive_in_next_gen;
    static int counter;

public:
    Cell(int gen = 0, bool status = false);
    unsigned long long int GetID();
    bool GetAlive();
    int GetGen();
    bool GetAliveStatusNextGen();

    void SetAlive(bool status);
    void IncreaseGen();
    void NullifyGen();

    void SetAliveStatusInNextGen(bool status);
};

#endif // CELL_H
