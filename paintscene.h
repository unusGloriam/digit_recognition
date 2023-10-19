#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>

class PaintScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();

    /**
     * @brief setPainted
     * @param painted
     */

    void setPainted(const bool painted);

    /**
     * @brief isPainted
     * @return
     */

    bool isPainted() const;

protected:

    bool painted;

private:
    QPointF previousPoint; // координаты предыдущей точки

    // для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif // PAINTSCENE_H
