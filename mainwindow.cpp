#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    draw_number_scene = new QGraphicsScene();
    ui->graphicsView->setScene(draw_number_scene);
    draw_number_scene->setSceneRect(-50,50,100,100);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Рисуем чёрный эллипс диаметром 4
    draw_number_scene->addEllipse(event->scenePos().x() - 2, event->scenePos().y() - 2, 4, 4, QPen(Qt::NoPen), QBrush(Qt::black));
    //Сохраняем координаты
    prev_point = event->screenPos();
}

void MainWindow::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    draw_number_scene->addLine(prev_point.x(), prev_point.y(), event->scenePos().x(), event->scenePos().y(), QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap));
    prev_point = event->screenPos();
}
