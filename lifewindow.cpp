#include "lifewindow.h"
#include "ui_lifewindow.h"
#include <QDebug>
#include <QTime>

LifeWindow::LifeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LifeWindow)
{
    ui->setupUi(this);

    QGraphicsView * view = ui->cellGraphicsView;
    scene = new QGraphicsScene;
    view->setScene(scene);
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());

    for(int i = 0; i < 21; i++){
        scene->addLine(i*40, 0, i*40, 400, QPen(QColor(255,255,255)));
        if(i < 11){
            scene->addLine(0, i*40, 800, i*40, QPen(QColor(255,255,255)));
        }
    }
}

LifeWindow::~LifeWindow()
{
    delete ui;
}
