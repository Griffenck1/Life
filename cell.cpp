#include "cell.h"
#include <QtWidgets>

Cell::Cell(int cell_state, const int x, const int y){
    cell_state_ = cell_state;
    if(cell_state_ == 0){
        color_ = QColor(0, 0, 0);
    }
    else{
        color_ = QColor(0, 255, 0);
    }
    x_ = x;
    y_ = y;
}

QRectF Cell::boundingRect() const {
    return QRectF(x_, y_, width_, width_);
}

QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(this->boundingRect());
    return path;
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    Q_UNUSED(widget);

    QBrush b = painter->brush();

    painter->setBrush(QBrush(color_));

    painter->drawRect(this->boundingRect());

    painter->setBrush(b);
}
