#ifndef LIFEWINDOW_H
#define LIFEWINDOW_H

#include <QMainWindow>
#include "lifeboard.h"

namespace Ui {
class LifeWindow;
}

class LifeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LifeWindow(QWidget *parent = 0);
    ~LifeWindow();

private slots:

private:
    Ui::LifeWindow *ui;
    QGraphicsScene *life_board_;
    QGraphicsScene *life_graph_;

    void PaintLifeBoard(LifeBoard life_board_real);
};

#endif // LIFEWINDOW_H
