#include "lifewindow.h"
#include "ui_lifewindow.h"
#include <QDebug>
#include <QTime>

/**
Sets up the starting state of the life window
*/
LifeWindow::LifeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LifeWindow)
{
    ui->setupUi(this);

    //pause starts as false
    pause_ = false;
    //slider speed starts at 1000 miliseconds per step
    slider_speed_ = 1000;

    //life_board_ starts as a large board
    life_board_ = LifeBoard(true);

    //Displays a proper starting value for the speed label
    float initial_speed = 1;
    std::string s = "Speed: " + std::to_string(initial_speed) + "x";
    QString qs = s.c_str();
    ui->speedLabel->setText(qs);

    //Sets an appropriate maximum and minumum value for the speed slider
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

    //The following lines of code are used to create the outline for the graph
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

    //Adds a bar displaying the initial state to the life graph
    life_graph_.AddBar(life_board_.PopulationAsPercent());
    PaintGraphBar(life_graph_.get_last_bar());

    //connects the speedSlider to a slot to handle it
    connect(ui->speedSlider, &QSlider::sliderReleased, this, &LifeWindow::SpeedSliderChanged);
}

/**
Destructor
*/
LifeWindow::~LifeWindow()
{
    delete ui;
}

/**
Used to call a step, handles the logic on the window level as well as communication between life_board_ and life_graph_
*/
void LifeWindow::CallStep(){
    //deletes the map size button during first step as it would not work after
    if(life_board_.get_turn() == 0){
        ui->mapSizeButton->deleteLater();
    }

    life_board_.TakeStep();
    GraphBar* to_delete = life_graph_.AddBar(life_board_.PopulationAsPercent());
    //If something was deleted form life_graph_ do the following
    if(to_delete != NULL){
        //delete the item
        delete to_delete;
        //go through each graph bar in life_graph_, delete it then repaint it to prevent artifacting
        for(GraphBar *b : life_graph_.get_graph_bars()){
            if(b != life_graph_.get_last_bar()){
                life_graph_view->removeItem(b);
            }
            life_graph_view->addItem(b);
        }
    }
    else{
        //If nothing was deleted just paint another graph bar
        PaintGraphBar(life_graph_.get_last_bar());
    }
    //Update appropriate labels
    std::string s = "Turn: " + std::to_string(life_board_.get_turn());
    QString qs = s.c_str();
    ui->turnLabel->setText(qs);
    ui->populationLabel->setText(life_board_.PopulationAsString());
}

/**
Handles playing the game automatically
*/
void LifeWindow::Play(){
    //while not paused
    if(!pause_){
        //Call a step
        this->CallStep();
        //every time interval dependant on slider_speed_, calls itself again to continue
        QTimer::singleShot(slider_speed_, this, SLOT(Play()));
    }
}

/**
Calls for a step when the step button is clicked
*/
void LifeWindow::on_stepButton_clicked(){
    this->CallStep();
}

/**
Calls play when the play button is clicked
*/
void LifeWindow::on_playButton_clicked(){
    //when play button is clicked pause_ must become true, however this and Play had to be
    //seperate as if you set pause_ to false before each recursion it will go on forever
    pause_ = false;
    this->Play();
}

/**
Pauses the game when pause button is clicked if it was playing
*/
void LifeWindow::on_pauseButton_clicked(){
    pause_ = true;
}

/**
Changes the slider_speed when the slider is dragged, then let go
*/
void LifeWindow::SpeedSliderChanged(){
    slider_speed_ = 10000/ui->speedSlider->value();
    float speed = ui->speedSlider->value()/10.0;
    std::string s = "Speed: " + std::to_string(speed) + "x";
    QString qs = s.c_str();
    //Also handels updating the speedLabel
    ui->speedLabel->setText(qs);
}

/**
Changes the map size when mapSizeButton is clicked
*/
void LifeWindow::on_mapSizeButton_clicked(){
    if(life_board_.get_board_width() == 40){
        ui->mapSizeButton->setText("Large Map");
        life_board_ = LifeBoard(false);
        PaintLifeBoard();
    }
    else{
        ui->mapSizeButton->setText("Small Map");
        life_board_ = LifeBoard(true);
        PaintLifeBoard();
    }
}

/**
Paints the life board when called, is a private fucntion as it should only be called by other member fucntions
*/
void LifeWindow::PaintLifeBoard(){
    for(Cell *c : life_board_.get_cells()){
        life_board_view->addItem(c);
    }
}

/**
Paints a graph bar when called, is a private fucntion as it should only be called by other member fucntions
*/
void LifeWindow::PaintGraphBar(GraphBar *b){
    life_graph_view->addItem(b);
}
