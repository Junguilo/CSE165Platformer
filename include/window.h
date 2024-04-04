#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

class GLWidget;

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window();

private:
    //keep a seperate window for OpenGL to have other QTWidgets draw over it.
    GLWidget *glWidget;

    void setupGLWidget();
};
#endif // WINDOW_H
