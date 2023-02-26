
#ifndef LIFE_H
#define LIFE_H
#include "cell.h"
#include "settings.h"
#include "map.h"
#include "point.h"

class Life{
    Cell ***m_cells;
    Settings *m_settings;


    Life(Settings *settings);
    Life(Settings *settings, Map *map);
    int bottom_death_count_condition = 2;
    int top_death_count_condition = 3;
    int reviving_cell_condition = 3;

public:
    static Life *Instance;
    static void Init(Settings *settings = nullptr, Map *map = nullptr);
    Cell*** GetCells();
    Settings* GetSettings();
    int GetAliveCellsAround(Cell*** ptr, int i, int j);
    void Proceed();
};

#endif // LIFE_H
