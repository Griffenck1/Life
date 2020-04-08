#include "lifeboard.h"

LifeBoard::LifeBoard(){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            Cell *cell = new Cell(0, i*40, j*40);
            cells_.push_back(cell);
        }
    }
}
