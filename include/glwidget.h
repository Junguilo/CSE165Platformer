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

private:
    //Standard OpenGLFunctions
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    //Other QT functions
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // GLWIDGET_H
