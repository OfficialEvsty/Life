
#ifndef LIFE_H
#define LIFE_H
#include "cell.h"
#include "settings.h"

struct Point{
    int x;
    int y;
    Point(int x, int y);
};

class Life{
    Cell ***m_cells;
    Settings *m_settings;


    Life(Settings *settings = nullptr);
    Life(Settings *settings, bool flag);
    int bottom_death_count_condition = 2;
    int top_death_count_condition = 3;
    int reviving_cell_condition = 3;

public:
    static Life *Instance;
    static void Init(Settings *settings = nullptr);
    Cell*** GetCells();
    Settings* GetSettings();
    int GetAliveCellsAround(Cell*** ptr, int i, int j);
    void Proceed();
};

#endif // LIFE_H
