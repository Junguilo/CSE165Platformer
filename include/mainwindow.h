#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWidget>
#include <QApplication>
#include <QOpenGLFunctions>
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

class MainWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    //These are basic QOpenGLWidget Functions, overrided to use.
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    //not an OpenGLFunction
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
