#include "lifeboard.h"
#include <string>

LifeBoard::LifeBoard(){
    turn_ = 0;
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            //determines the cells start state (alive or dead) with 50/50 odds
            int start_state = rand() % 2;
            Cell *cell = new Cell(start_state, i*40, j*40);
            cells_.push_back(cell);
        }
    }
}

QString LifeBoard::PopulationAsString(){
    int alive_count = 0;
    for(Cell *c : cells_){
        if(c->get_cell_state() == 1){
            alive_count++;
        }
    }
    return ("Population: " + std::to_string(alive_count) + " (" + std::to_string((alive_count*100)/200) + "%)").c_str();
}
