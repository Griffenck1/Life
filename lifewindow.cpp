#include "lifewindow.h"
#include "ui_lifewindow.h"
#include <QDebug>
#include <QTime>

LifeWindow::LifeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LifeWindow)
{
    ui->setupUi(this);

    pause_ = false;
    slider_speed_ = 1000;

    ui->speedSlider->setMaximum(100);
    ui->speedSlider->setMinimum(10);

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
    this->PaintLifeBoard();
    ui->turnLabel->setText("Turn: 0");
    ui->populationLabel->setText(life_board_.PopulationAsString());

    life_graph_.AddBar(life_board_.PopulationAsPercent());
    PaintGraphBar(life_graph_.get_last_bar());

    connect(ui->speedSlider, &QSlider::sliderReleased, this, &LifeWindow::SpeedSliderChanged);
}

void LifeWindow::PaintLifeBoard(){
    for(Cell *c : life_board_.get_cells()){
        life_board_view->addItem(c);
    }
}

void LifeWindow::PaintGraphBar(GraphBar *b){
    life_graph_view->addItem(b);
}

void LifeWindow::CallStep(){
    life_board_.TakeStep();
    GraphBar* to_delete = life_graph_.AddBar(life_board_.PopulationAsPercent());
    if(to_delete != NULL){
        delete to_delete;
        for(GraphBar *b : life_graph_.get_graph_bars()){
            if(b != life_graph_.get_last_bar()){
                life_graph_view->removeItem(b);
            }
            life_graph_view->addItem(b);
        }
    }
    else{
        PaintGraphBar(life_graph_.get_last_bar());
    }
    std::string s = "Turn: " + std::to_string(life_board_.get_turn());
    QString qs = s.c_str();
    ui->turnLabel->setText(qs);
    ui->populationLabel->setText(life_board_.PopulationAsString());
    //qDebug() << "step!";
    //for(Cell *c : life_board_.get_cells()[0]->get_neighbors()){
        //std::string s = std::to_string(c->get_x()) + " : " + std::to_string(c->get_y());
        //QString qs = s.c_str();
        //qDebug() << qs;
    //}
}

void LifeWindow::Play(){
    if(!pause_){
        QTimer::singleShot(slider_speed_, this, SLOT(Play()));
        this->CallStep();
        pause_ = false;
    }
}

void LifeWindow::on_stepButton_clicked(){
    this->CallStep();
}

void LifeWindow::on_playButton_clicked(){
    pause_ = false;
    this->Play();
}

void LifeWindow::on_pauseButton_clicked(){
    pause_ = true;
}

void LifeWindow::SpeedSliderChanged(){
    slider_speed_ = 10000/ui->speedSlider->value();
    float speed = ui->speedSlider->value()/10.0;
    std::string s = "Speed: " + std::to_string(speed) + "x";
    QString qs = s.c_str();
    ui->speedLabel->setText(qs);
}

LifeWindow::~LifeWindow()
{
    delete ui;
}
