#include "lifewindow.h"
#include <QApplication>

/**
Name: Griffen Cook
CSCI 3010 HW4 - Life
*/


int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    LifeWindow w;
    w.show();

    return a.exec();
}
