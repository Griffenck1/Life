#include "lifewindow.h"
#include "ui_lifewindow.h"
#include <QDebug>
#include <QTime>

LifeWindow::LifeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LifeWindow)
{
    ui->setupUi(this);

    //The following lines of code and for loop are used to create the grid that the game is played on
    QGraphicsView * life_board_view = ui->cellsGraphicsView;
    life_board_ = new QGraphicsScene;
    life_board_view->setScene(life_board_);
    life_board_view->setSceneRect(0,0,life_board_view->frameSize().width(),life_board_view->frameSize().height());

    for(int i = 0; i < 21; i++){
        life_board_->addLine(i*40, 0, i*40, 400, QPen(QColor(255,255,255)));
        if(i < 11){
            life_board_->addLine(0, i*40, 800, i*40, QPen(QColor(255,255,255)));
        }
    }

    //The following line of code are used to create the outline for the graph
    QGraphicsView * life_graph_view = ui->graphGraphicsView;
    life_graph_ = new QGraphicsScene;
    life_graph_view->setScene(life_graph_);
    life_graph_view->setSceneRect(0, 0, life_graph_view->frameSize().width(), life_graph_view->frameSize().height());

    life_graph_->addLine(0, 0, 800, 0, QPen(QColor(255,255,255)));
    life_graph_->addLine(0, 100, 800, 100, QPen(QColor(255,255,255)));
    life_graph_->addLine(0, 0, 0, 100, QPen(QColor(255,255,255)));
    life_graph_->addLine(800, 0, 800, 100, QPen(QColor(255,255,255)));

    QColor c(0, 255, 0);
    Cell *cell1 = new Cell(c, 0, 0);

    life_board_->addItem(cell1);
}

LifeWindow::~LifeWindow()
{
    delete ui;
}
