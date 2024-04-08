#include "glwidget.h"

//sets the size of our openGLWindow
GLWidget::GLWidget() {
    elapsed = 0;
    setFixedSize(800,800);
}

//not really needed, just so it destroys the opengl stuff
GLWidget::~GLWidget(){
    makeCurrent();
    doneCurrent();
}

void GLWidget::initializeGL(){
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //i think these were drawn on top of the screen, rather than any viewport
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
    glVertex2f(0.1f + triangleX, 0.1f + triangleY);
    glVertex2f(0.4f + triangleX, 0.1f + triangleY);
    glVertex2f(0.25f + triangleX, 0.4f + triangleY);
    glEnd();

    //put in another function for use later for gravity and animation
    //put here for testing
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrameTime);
    timeDelta = diff.count(); // compute time diff between frames in seconds
    lastFrameTime = now;

    qDebug() << timeDelta;
    update();
}

void GLWidget::keyPressEvent(QKeyEvent *event){
    //needs to be changed to handle multiple button inputs
    //this only takes in one key at a time
    switch(event->key()) {
    case Qt::Key_W:
        //Handle 'w' key pressed
        triangleY += 0.01f;
        qDebug() << "W";
        break;
    case Qt::Key_A:
        triangleX -= 0.01;
        // Handle 'a' key pressed
        qDebug() << "A";
        break;
    case Qt::Key_S:
        triangleY -= 0.01f;
        // Handle 's' key pressed
        qDebug() << "S";
        break;
    case Qt::Key_D:
        triangleX += 0.01f;
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
