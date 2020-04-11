#ifndef CELL_H
#define CELL_H

#include "graphbar.h"

class Cell : public QObject, public QGraphicsItem {

    Q_OBJECT

    public:
        Cell(int cell_state, const int x, const int y, int width);

        int get_x() const {return x_;}
        int get_y() const {return y_;}

        int get_cell_state() const {return cell_state_;}
        int get_next_cell_state() const {return next_cell_state_;}

        std::vector<Cell*> get_neighbors() const {return neighbors_;}

        void set_neighbors(std::vector<Cell*> neighbors){neighbors_ = neighbors;}

        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void Update() {update();}

        void PrepareToDie();
        void PrepareToLive();
        void PrepareToBecomeInfected();
        void PrepareToRecover();

        void Die();
        void Live();
        void BecomeInfected();
        void Recover();

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    private:
        int x_;
        int y_;
        //0 = dead, 1 = alive, 2 = infected, 3 = recovered
        int cell_state_;
        int next_cell_state_;
        QColor color_;
        int width_;
        std::vector<Cell*> neighbors_;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CELL_H
