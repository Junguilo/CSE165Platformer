#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QOpenGLWidget(parent) {}

MainWindow::~MainWindow() {}

//Runs all the other OpenGL Functions
void MainWindow::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

//The size of the window
void MainWindow::resizeGL(int w, int h){
    glViewport(0,0,w,h);
}

//Drawing the sprites
void MainWindow::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.4f, 0.1f);
    glVertex2f(0.25f, 0.4f);
    glEnd();
}

//KeyPress events
void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_W:
        //Handle 'w' key pressed
        qDebug() << "W";
        break;
    case Qt::Key_A:
        // Handle 'a' key pressed
        qDebug() << "A";
        break;
    case Qt::Key_S:
        // Handle 's' key pressed
        qDebug() << "S";
        break;
    case Qt::Key_D:
        // Handle 'd' key pressed
        qDebug() << "D";
        break;
    case Qt::Key_Escape:
        QApplication::exit();
        break;
    default:
        QOpenGLWidget::keyPressEvent(event);
    }
}