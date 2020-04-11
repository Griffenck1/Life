#include "lifeboard.h"
#include <string>
#include <iostream>

/**
Empty default constructor because otherwise the compiler gets mad
*/
LifeBoard::LifeBoard(){

}

/**
Constructor that takes the map size as a booleon
*/
LifeBoard::LifeBoard(bool large_map){
    board_width_ = 40;
    board_height_ = 20;
    int cell_width = 20;
    //Changes parameters if the map is small
    if(!large_map){
        board_width_ = 20;
        board_height_ = 10;
        cell_width = 40;
    }
    turn_ = 0;
    for(int i = 0; i < board_width_; i++){
        for(int j = 0; j < board_height_; j++){
            //determines the cells start state (alive or dead) with 50/50 odds
            int start_state = rand() % 2;
            Cell *cell = new Cell(start_state, i*cell_width, j*cell_width, cell_width);
            cells_.push_back(cell);
        }
    }
    this->PopulateCellNeighbors();
}

/**
Takes a 1D index and converts it into a 2D index, useful as my algorithm to find neighbors only works in 2D and it was to late to
change cells_ from a 1D vector into a 2D vector
*/
std::tuple<int, int> LifeBoard::oneDto2D(int i_2d){
    int i = i_2d / board_height_;
    int j = i_2d % board_height_;
    return std::tuple<int, int>{i, j};
}

/**
Takes a 2D index and converts it into a 1D index, useful as my algorithm to find neighbors only works in 2D and it was to late to
change cells_ from a 1D vector into a 2D vector
*/
int LifeBoard::twoDto1D(std::tuple<int, int> coordinates){
    return (std::get<0>(coordinates)*board_height_) + std::get<1>(coordinates);
}

/**
Calculates the live population and returns a QString to make it easty to print to the population label
*/
QString LifeBoard::PopulationAsString(){
    int alive_count = 0;
    for(Cell *c : cells_){
        if(c->get_cell_state() != 0){
            alive_count++;
        }
    }
    return ("Population: " + std::to_string(alive_count) + " (" + std::to_string((alive_count*100)/(board_height_*board_width_)) + "%)").c_str();
}

/**
Returns population as a percent rounded down to an integer
*/
int LifeBoard::PopulationAsPercent(){
    int alive_count = 0;
    for(Cell *c : cells_){
        if(c->get_cell_state() != 0){
            alive_count++;
        }
    }
    return (alive_count*100)/(board_height_*board_width_);
}


/**
This is used to populate each cell's neighbor field before the game of life can begin
*/
void LifeBoard::PopulateCellNeighbors(){
    int board_size = board_width_*board_height_;
    int cell_index = 0;
    std::vector<Cell*> neighbors;
    for(Cell *c : cells_){
        neighbors = {};
        std::tuple<int, int> cell_index_3d = this->oneDto2D(cell_index);

        int i = std::get<0>(cell_index_3d);
        int j = std::get<1>(cell_index_3d);

        //Calculates all eight neighbors using % to accomodate for wrapping
        std::tuple<int, int> n1((i + (board_width_ - 1))%board_width_, (j + (board_height_ - 1))% board_height_);
        std::tuple<int, int> n2((i + (board_width_ - 1))%board_width_, j);
        std::tuple<int, int> n3((i + (board_width_ - 1))%board_width_, (j + (board_height_ + 1))% board_height_);
        std::tuple<int, int> n4(i, (j + (board_height_ - 1))%board_height_);
        std::tuple<int, int> n5(i, (j + (board_height_ + 1))%board_height_);
        std::tuple<int, int> n6((i + (board_width_ + 1))%board_width_, (j + (board_height_ - 1))% board_height_);
        std::tuple<int, int> n7((i + (board_width_ + 1))%board_width_, j);
        std::tuple<int, int> n8((i + (board_width_ + 1))%board_width_, (j + (board_height_ + 1))% board_height_);

        neighbors.push_back(cells_[this->twoDto1D(n1)]);
        neighbors.push_back(cells_[this->twoDto1D(n2)]);
        neighbors.push_back(cells_[this->twoDto1D(n3)]);
        neighbors.push_back(cells_[this->twoDto1D(n4)]);
        neighbors.push_back(cells_[this->twoDto1D(n5)]);
        neighbors.push_back(cells_[this->twoDto1D(n6)]);
        neighbors.push_back(cells_[this->twoDto1D(n7)]);
        neighbors.push_back(cells_[this->twoDto1D(n8)]);

        c->set_neighbors(neighbors);
        cell_index++;
    }
}

/**
Handles the logic for taking a step, updates the board as well as each cell
*/
void LifeBoard::TakeStep(){
    int live_neighbors;
    //Goes through cells, decides if they should live or die, then prepares them to live or die when the board siwtches
    for(Cell *c : cells_){
        //if cell is infected, it has a chance to infect neighbors
        if(c->get_cell_state() == 2){
            for(Cell *n : c->get_neighbors()){
                if(n->get_cell_state() == 1){
                    //COVID-19 odds of spreading from contact is %5
                    if((rand() % 100) < 5){
                        n->PrepareToBecomeInfected();
                    }
                }
            }
            //COVID-19 odds of recovering is roughly 10% per day
            if((rand() % 100) < 10){
                c->PrepareToRecover();
            }
        }
        //calculates live neighbors in order to decide if a cell should live or die
        live_neighbors = 0;
        for(Cell *n : c->get_neighbors()){
            if(n->get_cell_state() != 0){
                live_neighbors++;
            }
        }
        if(live_neighbors == 3){
            c->PrepareToLive();
        }
        else if((live_neighbors > 3) | (live_neighbors < 2)){
            c->PrepareToDie();
        }
    }
    //Goes through the cells after each of their fates has been decided, and changes them
    for(Cell *c : cells_){
        if(c->get_next_cell_state() == 0){
            c->Die();
        }

        else if(c->get_next_cell_state() == 1){
            c->Live();
        }
        else if(c->get_next_cell_state() ==2){
            c->BecomeInfected();
        }
        else{
            c->Recover();
        }
    }
    turn_++;
}
