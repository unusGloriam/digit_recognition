#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) :
    QGraphicsScene(parent),
    painted(false) // по умолчанию ничего не нарисовано на сцене
{
    // here nothing to do
}

PaintScene::~PaintScene() {
    // here nothing to do
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    // при нажатии кнопки мыши отрисовываем эллипс
    addEllipse(
        event->scenePos().x() - 1,
        event->scenePos().y() - 1,
        4,
        4,
        QPen(Qt::NoPen),
        QBrush(Qt::white)
    );

    // сохраняем координаты точки нажатия
    previousPoint = event->scenePos();
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    // отрисовываем линии с использованием предыдущей координаты
    addLine(
        previousPoint.x(),
        previousPoint.y(),
        event->scenePos().x(),
        event->scenePos().y(),
        QPen(Qt::white,4,Qt::SolidLine,Qt::RoundCap)
    );

    // обновляем данные о предыдущей координате
    previousPoint = event->scenePos();

    painted = true; // считаем, что теперь что-то да нарисовано на сцене
}

void PaintScene::setPainted(const bool painted) {
    this->painted = painted;
}

bool PaintScene::isPainted() const {
    return painted;
}
