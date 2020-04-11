#include "lifeboard.h"
#include <string>
#include <iostream>

LifeBoard::LifeBoard(){

}

LifeBoard::LifeBoard(bool large_map){
    board_width_ = 40;
    board_height_ = 20;
    int cell_width = 20;
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

QString LifeBoard::PopulationAsString(){
    int alive_count = 0;
    for(Cell *c : cells_){
        if(c->get_cell_state() == 1){
            alive_count++;
        }
    }
    return ("Population: " + std::to_string(alive_count) + " (" + std::to_string((alive_count*100)/(board_height_*board_width_)) + "%)").c_str();
}

int LifeBoard::PopulationAsPercent(){
    int alive_count = 0;
    for(Cell *c : cells_){
        if(c->get_cell_state() == 1){
            alive_count++;
        }
    }
    return (alive_count*100)/(board_height_*board_width_);
}


//Algorithm doesn't quite work right
void LifeBoard::PopulateCellNeighbors(){
    int board_size = board_width_*board_height_;
    int cell_index = 0;
    std::vector<Cell*> neighbors;
    for(Cell *c : cells_){
        neighbors = {};
        std::tuple<int, int> cell_index_3d = this->twoDto3D(cell_index);
        //std::cout << std::get<0>(cell_index_3d) << " " << std::get<1>(cell_index_3d) << std::endl;
        int i = std::get<0>(cell_index_3d);
        int j = std::get<1>(cell_index_3d);
        //{(i - (board_width_ - 1))%board_width_, (j - (board_height_ - 1))%board_height_};
        std::tuple<int, int> n1((i + (board_width_ - 1))%board_width_, (j + (board_height_ - 1))% board_height_);
        std::tuple<int, int> n2((i + (board_width_ - 1))%board_width_, j);
        std::tuple<int, int> n3((i + (board_width_ - 1))%board_width_, (j + (board_height_ + 1))% board_height_);
        std::tuple<int, int> n4(i, (j + (board_height_ - 1))%board_height_);
        std::tuple<int, int> n5(i, (j + (board_height_ + 1))%board_height_);
        std::tuple<int, int> n6((i + (board_width_ + 1))%board_width_, (j + (board_height_ - 1))% board_height_);
        std::tuple<int, int> n7((i + (board_width_ + 1))%board_width_, j);
        std::tuple<int, int> n8((i + (board_width_ + 1))%board_width_, (j + (board_height_ + 1))% board_height_);

        std::cout << std::get<0>(n1) << " " << std::get<1>(n1) << " " << this->threeDto2D(n1) << std::endl;
        neighbors.push_back(cells_[this->threeDto2D(n1)]);
        neighbors.push_back(cells_[this->threeDto2D(n2)]);
        neighbors.push_back(cells_[this->threeDto2D(n3)]);
        neighbors.push_back(cells_[this->threeDto2D(n4)]);
        neighbors.push_back(cells_[this->threeDto2D(n5)]);
        neighbors.push_back(cells_[this->threeDto2D(n6)]);
        neighbors.push_back(cells_[this->threeDto2D(n7)]);
        neighbors.push_back(cells_[this->threeDto2D(n8)]);

        c->set_neighbors(neighbors);
        cell_index++;
    }
}

void LifeBoard::TakeStep(){
    int live_neighbors;
    //Goes through cells, decides if they should live or die, then prepares them to live or die when the board siwtches
    for(Cell *c : cells_){
        if(c->get_cell_state() == 2){
            for(Cell *n : c->get_neighbors()){
                if(n->get_cell_state() == 1){
                    if((rand() % 100) < 5){
                        n->PrepareToBecomeInfected();
                    }
                }
            }
            if((rand() % 100) < 10){
                c->PrepareToRecover();
            }
        }
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

void LifeBoard::UpdateAllCells(){
    for(Cell *c : cells_){
        c->update();
    }
}


std::tuple<int, int> LifeBoard::twoDto3D(int i_2d){
    int i = i_2d / board_height_;
    int j = i_2d % board_height_;
    return std::tuple<int, int>{i, j};
}

int LifeBoard::threeDto2D(std::tuple<int, int> coordinates){
    return (std::get<0>(coordinates)*board_height_) + std::get<1>(coordinates);
}
