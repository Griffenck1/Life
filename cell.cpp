#include "cell.h"

/**
Cell constructor takes cell_state, x coordinate, y coordinate, and width all as ints
*/
Cell::Cell(int cell_state, const int x, const int y, int width){
    cell_state_ = cell_state;
    next_cell_state_ = cell_state;
    //defines the cell's color on initialization
    //green = alive, black = dead, red = infected, blue = recovered
    if(cell_state_ == 0){
        color_ = QColor(0, 0, 0);
    }
    else{
        color_ = QColor(0, 255, 0);
    }
    x_ = x;
    y_ = y;
    width_ = width;
}

/**
this function creates the bounds of the cell
*/
QRectF Cell::boundingRect() const {
    return QRectF(x_, y_, width_, width_);
}

/**
This function defines the cell's shape
*/
QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(this->boundingRect());
    return path;
}

/**
This function paints the cell on the graphics view when needed
*/
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    Q_UNUSED(widget);

    QBrush b = painter->brush();

    painter->setBrush(QBrush(color_));

    painter->drawRect(this->boundingRect());

    painter->setBrush(b);
}

/**
This sets the next cell state to 0 so that it can properly be set to dead after at the end of each step
*/
void Cell::PrepareToDie(){
    next_cell_state_ = 0;
}

/**
This sets the next cell state to 1 so that it can properly be set to alive after at the end of each step
*/
void Cell::PrepareToLive(){
    if(cell_state_ == 0){
        next_cell_state_ = 1;
    }
    else{
        next_cell_state_ = cell_state_;
    }
}

/**
Sets next cell state to infected (aka 2)
*/
void Cell::PrepareToBecomeInfected(){
    next_cell_state_ = 2;
}

/**
Sets next cell state to recovered (aka 3)
*/
void Cell::PrepareToRecover(){
    next_cell_state_ = 3;
}

/**
Sets cell state to 1, changes color accordingly, and updates
*/
void Cell::Die(){
    cell_state_ = 0;
    color_ = QColor(0, 0, 0);
    update();
}

/**
Sets cell state to 1, changes color accordingly, and updates
*/
void Cell::Live(){
    if(cell_state_ == 0){
        cell_state_ = 1;
        color_ = QColor(0, 255, 0);
        update();
    }
}

/**
Sets cell state to 2, changes color accordingly, and updates
*/
void Cell::BecomeInfected(){
    cell_state_ = 2;
    color_ = QColor(255, 0, 0);
    update();
}

/**
Sets cell state to 3, changes color accordingly, and updates
*/
void Cell::Recover(){
    cell_state_ = 3;
    color_ = QColor(0, 0, 255);
    update();
}

/**
Handles the logic of what should happen when a user presses a cell, left click makes a cell alive,
right click makes a cell dead, shift left click infects a cell.
*/
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        if(event->modifiers() == Qt::ShiftModifier){
            this->BecomeInfected();
        }
        else{
            this->Live();
        }
    }
    else if(event->button() == Qt::RightButton){
        this->Die();
    }
}
