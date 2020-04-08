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
    void on_stepButton_clicked();


private:
    Ui::LifeWindow *ui;
    LifeBoard life_board_;
    QGraphicsScene *life_board_view;
    QGraphicsScene *life_graph_view;

    void PaintLifeBoard();
};

#endif // LIFEWINDOW_H
