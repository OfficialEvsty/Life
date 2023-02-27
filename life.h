
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

    unsigned long int populaty = 0;
    unsigned long long int generation = 0;

public:
    static Life *Instance;
    static void Init(Settings *settings = nullptr, Map *map = nullptr);
    Cell*** GetCells();
    Settings* GetSettings();
    unsigned long int GetPopulaty();
    unsigned long long int GetGeneration();
    int GetAliveCellsAround(Cell*** ptr, int i, int j);
    void Proceed();
};

#endif // LIFE_H
