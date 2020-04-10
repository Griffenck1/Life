#include "graphbar.h"

GraphBar::GraphBar(int x, int y){
    x_ = x;
    y_ = 100 - y;
    height_ = y;
}

QRectF GraphBar::boundingRect() const{
    return QRectF(x_, y_, width_, height_);
}

QPainterPath GraphBar::shape() const{
    QPainterPath path;
    path.addRect(this->boundingRect());
    return path;
}
void GraphBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(QColor(0, 255, 0)));

    painter->drawRect(this->boundingRect());

    painter->setBrush(b);
}

void GraphBar::RelocateBack(){
    x_ -= 20;
}
