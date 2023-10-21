#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "paintscene.h"
#include "teacher.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPointF prev_point;

    PaintScene* pScene;
    QTimer *timer;

private slots:
    void slotTimer();

    void onRecognizeButtonClicked();
    void onClearButtonClicked();
    void onLearnButtonClicked();
};
#endif // MAINWINDOW_H
