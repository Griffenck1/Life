#include "graphbar.h"

/**
Constructor for GraphBar takes x and y coordinates as itns
*/
GraphBar::GraphBar(int x, int y){
    x_ = x;
    y_ = 100 - y;
    height_ = y;
}

/**
This tells a graph bar to move back 20 pixels, this is useful for when the graph reaches the edge and
needs to start "scrolling" to the left
*/
void GraphBar::RelocateBack(){
    x_ -= 20;
}

/**
Creates the bounds for the graph bars, may not be necessary as you don't need to click on the bars
for anything, but maybe could be used to add a feature later
*/
QRectF GraphBar::boundingRect() const{
    return QRectF(x_, y_, width_, height_);
}

/**
Defines the shape of the graph bars
*/
QPainterPath GraphBar::shape() const{
    QPainterPath path;
    path.addRect(this->boundingRect());
    return path;
}

/**
Paints the graph bars
*/
void GraphBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(QColor(0, 255, 0)));

    painter->drawRect(this->boundingRect());

    painter->setBrush(b);
}
