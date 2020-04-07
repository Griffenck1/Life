#ifndef LIFEWINDOW_H
#define LIFEWINDOW_H

#include <QMainWindow>

namespace Ui {
class LifeWindow;
}

class LifeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LifeWindow(QWidget *parent = 0);
    ~LifeWindow();

private:
    Ui::LifeWindow *ui;
};

#endif // LIFEWINDOW_H
