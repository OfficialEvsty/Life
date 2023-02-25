#include "map.h"

Map::Map(Settings *sett)
{
    Map::m_spawn_points = new vector<Point>();
    Map::m_map_size = sett->GetSizeOfField();
}


vector<Point>* Map::GetPoints(){
    return this->m_spawn_points;
}

Size Map::GetSize(){
    return this->m_map_size;
}
