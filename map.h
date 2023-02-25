#ifndef MAP_H
#define MAP_H
#include "settings.h"
#include "life.h"
#include <vector>
using namespace std;


class Map
{
    Size m_map_size;
    vector <Point> *m_spawn_points;

public:
    Map(Settings *sett);

    vector<Point>* GetPoints();
    Size GetSize();
};

#endif // MAP_H
