#include "life.h"
#include "time.h"
#include "stdlib.h"
#include <typeinfo>
#include <QDebug>
#include <iostream>


//life's ctor
Life::Life(Settings *settings){
    this->m_settings = settings;
    unsigned long long int lengthX = this->m_settings->GetSizeOfField().LengthX;
    unsigned long long int lengthY = this->m_settings->GetSizeOfField().LengthY;
    //initializing array of cells by certain length.
    this->m_cells = new Cell**[lengthX];

    for (int i = 0; i < lengthX; i++)
        m_cells[i] = new Cell*[lengthY];


    for (int i = 0; i < lengthX; i++)
        for (int j = 0; j < lengthY; j++){
            bool cell_creating_condition = rand() % 2 == 1;
            m_cells[i][j] = new Cell(0, cell_creating_condition);
            this->populaty = (cell_creating_condition) ? ++this->populaty : this->populaty;
        }

    /*for (int i = 0; i < lengthX; i++)
            for (int j = 0; j < lengthY; j++){
                std::cout << m_cells[i][j]->GetAlive();
            }*/

}


Life::Life(Settings *settings, Map *map){
    this->m_settings = settings;
    unsigned long long int lengthX = this->m_settings->GetSizeOfField().LengthX;
    unsigned long long int lengthY = this->m_settings->GetSizeOfField().LengthY;
    //initializing array of cells by certain length.
    this->m_cells = new Cell**[lengthX];

    for (int i = 0; i < lengthX; i++)
        m_cells[i] = new Cell*[lengthY];

    for (int i = 0; i < lengthX; i++)
        for (int j = 0; j < lengthY; j++){
            bool cell_creating_condition = false;
            m_cells[i][j] = new Cell(0, cell_creating_condition);
            for (int k = 0; k < map->GetPoints()->size(); k++){
                if (map->GetPoints()->at(k).x == i && map->GetPoints()->at(k).y == j){
                    m_cells[i][j]->SetAlive(true);
                    this->populaty++;
                }
            }
        }

    /*for (int i = 0; i < lengthX; i++)
            for (int j = 0; j < lengthY; j++){
                std::cout << m_cells[i][j]->GetAlive();
            }*/

}

void Life::Init(Settings *settings, Map *map){
    if (!Life::Instance){
        if (map != nullptr)
            Life::Instance = new Life(settings, map);
        else
            Life::Instance = new Life(settings);
    }
}

Cell*** Life::GetCells(){
    return this->m_cells;
}

Settings* Life::GetSettings(){
    return this->m_settings;
}

unsigned long int Life::GetPopulaty(){
    return this->populaty;
}

unsigned long long int Life::GetGeneration(){
    return this->generation;
}

int Life::GetAliveCellsAround(Cell*** ref, int i, int j){
    Point points[] = {
        Point(0, 1),
        Point(0, -1),
        Point(1, 0),
        Point(1, -1),
        Point(1, 1),
        Point(-1, 0),
        Point(-1, -1),
        Point(-1, 1),
    };
    Cell **surrounding_cells = new Cell*[8];
    int counter = 0;
    for (int k = 0; k < 8; k++){
        int indentX = i + points[k].x;
        int indentY = j + points[k].y;
        //bool is_out_of_range = sizeof(*(*(ref + indentX) + indentY)) < sizeof(Cell);
        bool is_out_of_range = indentX < 0 || indentY < 0 || indentX > this->GetSettings()->GetSizeOfField().LengthX - 1 || indentY > this->GetSettings()->GetSizeOfField().LengthY - 1;
        if (is_out_of_range)
            continue;
        surrounding_cells[counter] = *(*(ref + indentX) + indentY);
        counter++;
    }

    int life_counter = 0;
    for (int k = 0; k < counter; k++){
        Cell cell = *surrounding_cells[k];
        //std::cout << typeid(surrounding_cells[i]);
        //if (typeid(surrounding_cells[i]) == typeid(Cell)){
        if (cell.GetAlive()){
            life_counter += 1;
        }

        //}
    }
            //qDebug() << ref->GetID();
    return life_counter;

}

void Life::Proceed(){
    unsigned long long int lenX = this->GetSettings()->GetSizeOfField().LengthX;
    unsigned long long int lenY = this->GetSettings()->GetSizeOfField().LengthY;
    for (int i = 0; i < lenX; i++)
        for (int j = 0; j < lenY; j++){
            Cell *ptr = *(*(this->GetCells()+i)+j);
            //throw "stop point";
            int cells_count = Life::GetAliveCellsAround(this->GetCells(), i, j);
            if (ptr->GetAlive()){
                bool is_cell_died = cells_count > this->top_death_count_condition || cells_count < this->bottom_death_count_condition;
                ptr->SetAliveStatusInNextGen(!is_cell_died);
                if (!is_cell_died){
                    ptr->IncreaseGen();
                    this->generation++;
                }
                else{
                    this->populaty--;
                    ptr->NullifyGen();
                }
            }
            else{
                bool is_cell_revived = cells_count == this->reviving_cell_condition;
                ptr->SetAliveStatusInNextGen(is_cell_revived);
                this->populaty = (is_cell_revived) ? ++this->populaty : this->populaty;
            }

        }
    for (int i = 0; i < lenX; i++)
        for (int j = 0; j < lenY; j++){
            this->GetCells()[i][j]->SetAlive(this->GetCells()[i][j]->GetAliveStatusNextGen());
        }

}

Life *Life::Instance = nullptr;

