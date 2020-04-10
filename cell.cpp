#include "cell.h"

Cell::Cell(int cell_state, const int x, const int y){
    cell_state_ = cell_state;
    next_cell_state_ = cell_state;
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

void Cell::PrepareToDie(){
    next_cell_state_ = 0;
}

void Cell::PrepareToLive(){
    if(cell_state_ == 0){
        next_cell_state_ = 1;
    }
    else{
        next_cell_state_ = cell_state_;
    }
}

void Cell::PrepareToBecomeInfected(){
    next_cell_state_ = 2;
}

void Cell::PrepareToRecover(){
    next_cell_state_ = 3;
}

void Cell::Die(){
    cell_state_ = 0;
    color_ = QColor(0, 0, 0);
    update();
}

void Cell::Live(){
    if(cell_state_ == 0){
        cell_state_ = 1;
        color_ = QColor(0, 255, 0);
        update();
    }
}

void Cell::BecomeInfected(){
    cell_state_ = 2;
    color_ = QColor(255, 0, 0);
    update();
}

void Cell::Recover(){
    cell_state_ = 3;
    color_ = QColor(0, 0, 255);
    update();
}

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
