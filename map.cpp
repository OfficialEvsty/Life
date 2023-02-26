#include "map.h"

Map::Map()
{
    Map::m_spawn_points = new vector<Point>();
}


vector<Point>* Map::GetPoints(){
    return this->m_spawn_points;
}


