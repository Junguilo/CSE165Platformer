#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QApplication>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QDebug>
#include <QKeyEvent>

//move this to its own enemy Spawner class
#include "enemymongus.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    GLWidget();
    ~GLWidget() override;
private:
    //Standard OpenGLWidget Functions
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    //Other QT functions to handle input
    //void keyPressEvent(QKeyEvent *event) override;
    //void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *event) override;
    //void mouseMoveEvent(QMouseEvent *event) override;

    EnemyMongus *test;
    EnemyMongus *testTwo;
    void mapDraw();


    //another method for time used in another example
    int elapsed;

    //calculating the currentTime - elapsedTime diff
    float timeDelta;
    std::chrono::time_point<std::chrono::steady_clock> lastFrameTime;
};

#endif // GLWIDGET_H
