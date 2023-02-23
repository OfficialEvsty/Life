#include "life.h"
#include "time.h"
#include "stdlib.h"
#include <typeinfo>
#include <QDebug>
#include <iostream>


//ctor for support entity class point.
Point::Point(int x, int y){
    this->x = x;
    this->y = y;
}

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
            bool cell_creating_condition = rand() % 10 == 1;
            m_cells[i][j] = new Cell(0, cell_creating_condition);
        }

    /*for (int i = 0; i < lengthX; i++)
            for (int j = 0; j < lengthY; j++){
                std::cout << m_cells[i][j]->GetAlive();
            }*/

}

void Life::Init(Settings *settings){
    if (!Life::Instance){
        Life::Instance = new Life(settings);
    }
}

Cell*** Life::GetCells(){
    return this->m_cells;
}

Settings* Life::GetSettings(){
    return this->m_settings;
}

int Life::GetAliveCellsAround(Cell*** ref, int i, int j){
    /*Cell *surrounding_cells[] = {ref+1,
                             ref+length+1,
                             ref+length,
                             ref+length-1,
                             ref-1,
                             ref-length-1,
                             ref-length,
                             ref-length+1};*/
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
    for (int k = 0; i < 8; i++){
        int indentX = i + points[k].x;
        int indentY = j + points[k].y;
        //bool is_out_of_range = sizeof(*(*(ref + indentX) + indentY)) < sizeof(Cell);
        bool is_out_of_range = indentX < 0 || indentY < 0 || indentX > this->GetSettings()->GetSizeOfField().LengthX || indentY > this->GetSettings()->GetSizeOfField().LengthY;
        if (is_out_of_range)
            continue;
        surrounding_cells[counter] = *(*(ref + indentX) + indentY);
        qDebug() << surrounding_cells[counter]->GetID();
        counter++;
    }
    qDebug() << sizeof(surrounding_cells) / sizeof(Cell);

    int life_counter = 0;
    for (int i = counter; i > 0; i--){
        if(surrounding_cells[i] == nullptr)
            continue;
        //std::cout << typeid(surrounding_cells[i]);
        //if (typeid(surrounding_cells[i]) == typeid(Cell)){
        qDebug() << surrounding_cells[i]->GetID();
        if (surrounding_cells[i]->GetAlive())
            life_counter += 1;
        //}
    }
            //qDebug() << ref->GetID();
    return life_counter;

}

void Life::Proceed(){
    for (int i = 0; i < this->GetSettings()->GetSizeOfField().LengthX; i++)
        for (int j = 0; j < this->GetSettings()->GetSizeOfField().LengthY; j++){
            Cell *ptr = *(*(this->GetCells()+i)+j);
            //throw "stop point";
            int cells_count = Life::GetAliveCellsAround(this->GetCells(), i, j);
            qDebug() << cells_count;
            if (ptr->GetAlive()){
                bool is_cell_died = cells_count > this->top_death_count_condition && cells_count < this->bottom_death_count_condition;
                ptr->SetAlive(!is_cell_died);
                if (!is_cell_died)
                    ptr->IncreaseGen();
                else
                    ptr->NullifyGen();

            }
            else{
                bool is_cell_revived = cells_count == this->reviving_cell_condition;
                ptr->SetAlive(is_cell_revived);
            }
        }
}

Life *Life::Instance = nullptr;

