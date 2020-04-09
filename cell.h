#ifndef CELL_H
#define CELL_H

#include "graphbar.h"

class Cell : public QObject, public QGraphicsItem {

    Q_OBJECT

    public:
        Cell(int cell_state, const int x, const int y);

        int get_x() const {return x_;}
        int get_y() const {return y_;}

        int get_cell_state() const {return cell_state_;}
        int get_next_cell_state() const {return next_cell_state_;}

        std::vector<Cell*> get_neighbors() const {return neighbors_;}

        void set_neighbors(std::vector<Cell*> neighbors){neighbors_ = neighbors;}

        QRectF boundingRect() const override;
        QPainterPath shape() const override;

        void Die();
        void Live();

        void PrepareToDie();
        void PrepareToLive();

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    private:
        int x_;
        int y_;
        int cell_state_;
        int next_cell_state_;
        QColor color_;
        static const int width_ = 20;
        std::vector<Cell*> neighbors_;
};

#endif // CELL_H
