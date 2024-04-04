#include "window.h"
#include "glwidget.h"
#include <QtWidgets>


Window::Window(){
    //now we can setup multiple other QTWidgets here


    //GL Setup
    setupGLWidget();
}


void Window::setupGLWidget(){
    glWidget = new GLWidget;

    //sets keyboard input onto glWindow
    glWidget->setFocusPolicy(Qt::StrongFocus);
    setCentralWidget(glWidget);
}
