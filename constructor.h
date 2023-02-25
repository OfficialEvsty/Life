#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H
#include "map.h"


class Constructor{
    Map *map;
    Settings *m_settings;

    Constructor(Settings *sett);

    void addPoint(Point p);
    void deletePoint(vector<Point>::iterator iterator);
    bool isPointValid(Point p);
    Point convertMouseXYToCellPoint(int x, int y);
public:
    static Constructor *Instance;
    static void Init(Settings *sett);
    void EditMap(int x, int y);
    Settings* GetSettings();
    Map* GetMap();
};

#endif // CONSTRUCTOR_H
