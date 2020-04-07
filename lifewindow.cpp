#include "lifewindow.h"
#include "ui_lifewindow.h"

LifeWindow::LifeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LifeWindow)
{
    ui->setupUi(this);
    QGraphicsView * view = ui->cellsGraphicsView;
}

LifeWindow::~LifeWindow()
{
    delete ui;
}
