#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QApplication>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QDebug>
#include <QKeyEvent>


class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    GLWidget();
    ~GLWidget() override;
private:
    //Standard OpenGLFunctions
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    //Other QT functions to handle input
    void keyPressEvent(QKeyEvent *event) override;
    //void keyReleaseEvent(QKeyEvent *event) override;
    //void mousePressEvent(QMouseEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *event) override;
    //void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // GLWIDGET_H
