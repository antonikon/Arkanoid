#pragma once

#include <QMainWindow>
#include "world.h"
#include <QPaintEvent>
#include <QTimerEvent>
#include <QPainter>
#include <QMouseEvent>
#include "values.h"
#include <QCursor>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void mouseMoveEvent(QMouseEvent *pos);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    TWorld _world;
};
