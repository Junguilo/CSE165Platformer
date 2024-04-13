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

    //testMongus, health, attack, posX, posY
    //will have to have an enemy spawner later.
    test = new EnemyMongus(10, 2, 0.0f, 0.0f);
    //state setting Function
    glClearColor(0.07f,0.13f,0.17f,1.0f);
}

void GLWidget::resizeGL(int w, int h){

    glViewport(0,0,w,h);
}

void GLWidget::paintGL(){
    //state using function
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mapDraw();
    //End of Map
    //will draw the enemies
    test->draw();

    //input test, del later
    glColor3f(0.5f, 0.5f, 0.5f);
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

    //qDebug() << timeDelta;
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

void GLWidget::mousePressEvent(QMouseEvent *event) {
    switch(event->button()) {
    case Qt::LeftButton:{
        //This code just gets the position so it makes drawing w/ code easier
            // Translate position to center
            float centerX = event->pos().x() - width() / 2.0f;
            float centerY = height() / 2.0f - event->pos().y();

            // Scale to range -1 to 1
            float normalizedX = (2.0f * centerX) / width();
            float normalizedY = (2.0f * centerY) / height();

            qDebug() << "Position:" << normalizedX << "," << normalizedY;
            break;
    }
    case Qt::RightButton:{
        qDebug() << "------------------";
        break;
    }
        default:
            QOpenGLWidget::mousePressEvent(event);
    }
}


void GLWidget::mapDraw(){
    //Draw the map, move to a function later
    //Center
    glColor3f(0.82, 0.82, 0.82);
    glBegin(GL_QUADS);
    glVertex2f(-0.5, -0.5);   // Bottom-left vertex
    glVertex2f(0.5, -0.5);    // Bottom-right vertex
    glVertex2f(0.5, 0.5);     // Top-right vertex
    glVertex2f(-0.5, 0.5);    // Top-left vertex
    glEnd();

    //Center Bottom
    glColor3f(0.549, 0.549, 0.549);
    glBegin(GL_QUADS);
    glVertex2f(-1, -1);   // Bottom-left vertex
    glVertex2f(1, -1);    // Bottom-right vertex
    glVertex2f(0.5, -0.5);     // Top-right vertex
    glVertex2f(-0.5, -0.5);    // Top-left vertex
    glEnd();

    //CenterTop
    glColor3f(0.549, 0.549, 0.549);
    glBegin(GL_QUADS);
    glVertex2f(-0.5, 0.5);   // Bottom-left vertex
    glVertex2f(0.5, 0.5);    // Bottom-right vertex
    glVertex2f(1, 1);     // Top-right vertex
    glVertex2f(-1, 1);    // Top-left vertex
    glEnd();
}
