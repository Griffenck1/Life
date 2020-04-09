#include "lifeboard.h"
#include <string>

LifeBoard::LifeBoard(){
    turn_ = 0;
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 20; j++){
            //determines the cells start state (alive or dead) with 50/50 odds
            int start_state = rand() % 2;
            Cell *cell = new Cell(start_state, i*20, j*20);
            cells_.push_back(cell);
        }
    }
    this->PopulateCellNeighbors();
}

QString LifeBoard::PopulationAsString(){
    int alive_count = 0;
    for(Cell *c : cells_){
        if(c->get_cell_state() == 1){
            alive_count++;
        }
    }
    return ("Population: " + std::to_string(alive_count) + " (" + std::to_string((alive_count*100)/800) + "%)").c_str();
}

//Algorithm doesn't quite work right
void LifeBoard::PopulateCellNeighbors(){
    int cell_index = 0;
    std::vector<Cell*> neighbors;
    for(Cell *c : cells_){
        neighbors = {};
        neighbors.push_back(cells_[(((cell_index - 41)+800)%800)]);
        neighbors.push_back(cells_[(((cell_index - 40)+800)%800)]);
        neighbors.push_back(cells_[(((cell_index - 39)+800)%800)]);
        neighbors.push_back(cells_[(((cell_index - 1)+800)%800)]);
        neighbors.push_back(cells_[(((cell_index + 1)+800)%800)]);
        neighbors.push_back(cells_[(((cell_index + 39)+800)%800)]);
        neighbors.push_back(cells_[(((cell_index + 40)+800)%800)]);
        neighbors.push_back(cells_[(((cell_index + 41)+800)%800)]);
        cells_[cell_index]->set_neighbors(neighbors);
        cell_index++;
    }
}

void LifeBoard::TakeStep(){
    std::vector<Cell*> next_state;
    int live_neighbors;
    //Goes through cells, decides if they should live or die, then prepares them to live or die when the board siwtches
    for(Cell *c : cells_){
        live_neighbors = 0;
        for(Cell *n : c->get_neighbors()){
            if(n->get_cell_state() == 1){
                live_neighbors++;
            }
        }
        if((c->get_cell_state() == 0) & (live_neighbors == 3)){
            c->PrepareToLive();
        }
        else if((c->get_cell_state() == 1) & ((live_neighbors > 3) | (live_neighbors < 2))){
            c->PrepareToDie();
        }
    }
    //Goes through the cells after each of their fates has been decided, and changes them
    for(Cell *c : cells_){
        if(c->get_next_cell_state() == 1){
            c->Live();
        }
        else{
            c->Die();
        }
    }
    turn_++;
}
