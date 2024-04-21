#include "glwidget.h"

//sets the size of our openGLWindow
GLWidget::GLWidget() {
    elapsed = 0;
    setFixedSize(800,800);

    // sound effects
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl("qrc:/sounds/shooting.mp3"));
    audioOutput->setVolume(0.5);


    //  audio output and media player for the background song
    QAudioOutput *backgroundAudioOutput = new QAudioOutput(this);
    QMediaPlayer *backgroundPlayer = new QMediaPlayer(this);


    backgroundPlayer->setAudioOutput(backgroundAudioOutput);

    // source directory
    backgroundPlayer->setSource(QUrl("qrc:/sounds/theme.mp3"));

    //loop forever
    backgroundPlayer->setLoops(QMediaPlayer::Infinite);

    backgroundAudioOutput->setVolume(0.1);

    // play theme
    backgroundPlayer->play();

}

//not really needed, just so it destroys the opengl stuff when done
GLWidget::~GLWidget(){
    makeCurrent();
    doneCurrent();
}

void GLWidget::initializeGL(){
    initializeOpenGLFunctions();

    //testMongus, health, attack, posX, posY
    //will have to have an enemy spawner later.
    test = new EnemyMongus(0.6f, 0.5f);

    testTwo = new EnemyMongus(0.0f, 0.0f);
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

    //Draws Enemies & Hitboxes
    if (test && test->alive) {
        test->draw();
        test->updateHitbox();
    }

    if (testTwo && testTwo->alive) {
        testTwo->draw();
        testTwo->updateHitbox();
    }

    //needed in order to draw every frame
    update();
}

//MOUSE EVENT HERE
void GLWidget::mousePressEvent(QMouseEvent *event) {
    bool hitAnyEntity = false; // Flag to track if any entity was hit

    // Play sound when the left button is clicked
    if (event->button() == Qt::LeftButton) {

         mediaPlayer->stop();
         mediaPlayer->play();

    }

    switch(event->button()) {
    case Qt::LeftButton: {
        // Translate position to center
        float centerX = event->pos().x() - width() / 2.0f;
        float centerY = height() / 2.0f - event->pos().y();

        // Scale to range -1 to 1
        float normalizedX = (2.0f * centerX) / width();
        float normalizedY = (2.0f * centerY) / height();

        qDebug() << "Position:" << normalizedX << "," << normalizedY;

        // Check if the click hit the first entity
        if (test) {
            test->checkHitbox(normalizedX, normalizedY);
            if (test->isEnemyHit()) {
                hitAnyEntity = true;
                qDebug() << "Hit first entity with health:" << test->getEnemyHealth();
                // Reduce the health of the first entity
                test->reduceHealth();

                // Check if the entity is dead and handle it
                if (!test->alive) {
                    delete test;
                    test = nullptr;
                }
            }
        }

        // Check if the click hit the second entity
        if (testTwo) {
            testTwo->checkHitbox(normalizedX, normalizedY);
            if (testTwo->isEnemyHit()) {
                hitAnyEntity = true;
                qDebug() << "Hit second entity with health:" << testTwo->getEnemyHealth();
                // Reduce the health of the second entity
                testTwo->reduceHealth();

                // Check if the entity is dead and handle it
                if (!testTwo->alive) {
                    delete testTwo;
                    testTwo = nullptr;
                }
            }
        }

        // Handle click not hitting any entities
        if (!hitAnyEntity) {
            qDebug() << "No entity was hit.";
            // Optionally, you can perform some action here, e.g., moving the player character
        }

        break;
    }
    case Qt::RightButton: {
        qDebug() << "Right button clicked.";
        break;
    }
    default:
        qDebug() << "Unhandled mouse button event.";
        break;
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
