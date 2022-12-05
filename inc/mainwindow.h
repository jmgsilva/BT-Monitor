#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bt_model.h"
#include <QMainWindow>
#include <QThread>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    BehaviorTree *tree;

public:
    MainWindow(QWidget *parent = nullptr);
    void drawSomething();
    ~MainWindow();

private slots:
    void handleMessage(const std::string &message);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    QThread th;
    Ui::MainWindow *ui;
    QGraphicsView *graphicsview;
    QGraphicsScene *scene;

};

class MyQGraphicsView : public QGraphicsView {
    Q_OBJECT

private slots:
    void wheelEvent ( QWheelEvent * event );
    void scalingTime(qreal x);
    void animFinished();
private:
    int _numScheduledScalings;
};

#endif // MAINWINDOW_H
