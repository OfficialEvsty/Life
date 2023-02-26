#ifndef MAP_H
#define MAP_H
using namespace std;
#include <vector>
#include "point.h"
class Map
{
    vector<Point> *m_spawn_points;

public:
    Map();

    vector<Point>* GetPoints();
};

#endif // MAP_H
