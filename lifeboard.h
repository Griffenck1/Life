#ifndef LIFEBOARD_H
#define LIFEBOARD_H

#include "cell.h"
#include <QVector>

class LifeBoard{
    public:
        LifeBoard();
        LifeBoard(bool large_map);

        std::tuple<int, int> oneDto2D(int i_2d);
        int twoDto1D(std::tuple<int, int> coordinates);

        const std::vector<Cell*> get_cells() const {return cells_;}
        int get_turn() const {return turn_;}
        int get_board_width() const {return board_width_;}
        int get_board_height() const {return board_height_;}

        QString PopulationAsString();

        int PopulationAsPercent();

        void PopulateCellNeighbors();

        void TakeStep();

    private:
        std::vector<Cell*> cells_;
        int turn_;
        int board_width_;
        int board_height_;
};

#endif // LIFEBOARD_H
