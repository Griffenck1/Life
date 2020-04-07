#ifndef CELL_H
#define CELL_H

#include <QColor>
#include <QGraphicsItem>

class Cell : public QObject, public QGraphicsItem {

    Q_OBJECT

    public:
        Cell(QColor, const int x, const int y);
    private:
        int x_;
        int y_;
        QColor color_;
        static const int width_ = 20;
};

#endif // CELL_H
