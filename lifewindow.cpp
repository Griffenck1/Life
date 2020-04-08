#include "lifewindow.h"
#include "ui_lifewindow.h"
#include <QDebug>
#include <QTime>

LifeWindow::LifeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LifeWindow)
{
    ui->setupUi(this);

    /**
    To avoid any confusion, life_board_view_ and life_board_view_local are used to display the board, life_board_
    is the actual LifeBoard object
    */
    QGraphicsView * life_board_view_local = ui->cellsGraphicsView;
    life_board_view = new QGraphicsScene;
    life_board_view_local->setScene(life_board_view);
    life_board_view_local->setSceneRect(0,0,life_board_view_local->frameSize().width(),life_board_view_local->frameSize().height());

    //The following line of code are used to create the outline for the graph
    QGraphicsView * life_graph_view_local = ui->graphGraphicsView;
    life_graph_view = new QGraphicsScene;
    life_graph_view_local->setScene(life_graph_view);
    life_graph_view_local->setSceneRect(0, 0, life_graph_view_local->frameSize().width(), life_graph_view_local->frameSize().height());

    life_graph_view->addLine(0, 0, 800, 0, QPen(QColor(255,255,255)));
    life_graph_view->addLine(0, 100, 800, 100, QPen(QColor(255,255,255)));
    life_graph_view->addLine(0, 0, 0, 100, QPen(QColor(255,255,255)));
    life_graph_view->addLine(800, 0, 800, 100, QPen(QColor(255,255,255)));

    //These lines initialize the life_board_ and print it to life_board_view and also set the appropriate labels
    this->PaintLifeBoard(life_board_);
    ui->turnLabel->setText("Turn: 0");
    ui->populationLabel->setText(life_board_.PopulationAsString());

}

void LifeWindow::PaintLifeBoard(LifeBoard life_board_real){
    for(Cell *c : life_board_real.get_cells()){
        life_board_view->addItem(c);
    }
}

LifeWindow::~LifeWindow()
{
    delete ui;
}
