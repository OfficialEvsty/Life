#include "constructor.h"
#include <QDebug>

Constructor::Constructor(Settings *sett){
    m_settings = sett;
    map = new Map(m_settings);
}

void Constructor::Init(Settings *settings){
    if (!Constructor::Instance){
        Constructor::Instance = new Constructor(settings);
    }
}

void Constructor::deletePoint(vector<Point>::iterator iterator){
    vector<Point> *points = map->GetPoints();
    points->erase(iterator);
}

void Constructor::addPoint(Point p){
    vector<Point> *points = map->GetPoints();
    points->push_back(p);
    qDebug() << points->size();
}

bool Constructor::isPointValid(Point p){
    unsigned long long int lengthX = this->GetSettings()->GetSizeOfField().LengthX;
    unsigned long long int lengthY = this->GetSettings()->GetSizeOfField().LengthY;
    bool is_point_out_of_bounds = p.x < 0 || p.y < 0 || p.x > lengthX || p.y > lengthY;
    if (is_point_out_of_bounds)
        return false;
    return true;
}

Point Constructor::convertMouseXYToCellPoint(int x, int y){
    int cell_size = this->m_settings->GetCellWidth();
    int calculatedX = x / cell_size;
    int calculatedY = y / cell_size;
    return Point(calculatedX, calculatedY);
}

void Constructor::EditMap(int x, int y){
    Point p = convertMouseXYToCellPoint(x, y);

    if (!isPointValid(p))
        return;

    vector<Point> *points = map->GetPoints();
    vector<Point>::iterator point_iterator = points->begin();
    for (int i = 0; i < points->size(); i++){
        point_iterator++;
        if (points[i] == p.x && points[i].y == p.y){
            deletePoint(point_iterator);
            break;
        }
    }
    addPoint(p);
}



Map* Constructor::GetMap(){
    return this->map;
}

Settings* Constructor::GetSettings(){
    return this->m_settings;
}

Constructor *Constructor::Instance = nullptr;
