#ifndef LIFEWINDOW_H
#define LIFEWINDOW_H

#include <QMainWindow>
#include "cell.h"

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
};

#endif // LIFEWINDOW_H
