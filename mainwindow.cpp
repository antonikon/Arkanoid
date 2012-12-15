#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startTimer(20);
    setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    setCursor(QCursor(QPixmap(cursorImage)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,_world.surface());
}

void MainWindow::timerEvent(QTimerEvent *)
{
    _world.paint();
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *pos)
{
    _world.move(pos->x());
}
