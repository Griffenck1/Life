#ifndef GRAPHBAR_H
#define GRAPHBAR_H

#include <stdio.h> //Random # generation
#include <stdlib.h> //Random # generation
#include <time.h> //Random # generation
#include <QColor>
#include <QGraphicsItem>
#include <QtWidgets>

class GraphBar : public QObject, public QGraphicsItem {
    Q_OBJECT

    public:
        GraphBar(int x, int y, int height);

        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    private:
        int x_;
        int y_;
        static const int width_ = 20;
        int height_;

};

#endif // GRAPHBAR_H
