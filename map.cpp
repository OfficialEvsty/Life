#include "map.h"

Map::Map()
{
    Map::m_spawn_points = new vector<Point>();
}

bool Map::IsEmpty(){
    if (!this->m_spawn_points->size())
        return true;
    return false;
}

vector<Point>* Map::GetPoints(){
    return this->m_spawn_points;
}


