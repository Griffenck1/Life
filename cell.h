#ifndef CELL_H
#define CELL_H

#include <QColor>
#include <QGraphicsItem>

class Cell : public QObject, public QGraphicsItem {

    Q_OBJECT

    public:
        Cell(QColor c, const int x, const int y);

        int get_x() const {return x_;}
        int get_y() const {return y_;}

        int get_id() const {return id_;}

        QRectF boundingRect() const override;
        QPainterPath shape() const override;

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    private:
        int x_;
        int y_;
        int id_;
        QColor color_;
        static const int width_ = 40;
};

#endif // CELL_H
