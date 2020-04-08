#ifndef LIFEBOARD_H
#define LIFEBOARD_H

#include "cell.h"
#include <QVector>

class LifeBoard{
    public:
        LifeBoard();

        const std::vector<Cell*> get_cells() const {return cells_;}

        int get_turn(){return turn_;}

        QString PopulationAsString();

    private:
        std::vector<Cell*> cells_;
        int turn_;
};

#endif // LIFEBOARD_H
