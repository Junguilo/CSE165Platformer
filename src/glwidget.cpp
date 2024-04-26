#include "glwidget.h"

//sets the size of our openGLWindow
GLWidget::GLWidget() {
    elapsed = 0;
    setFixedSize(800,800);

    //Initializing Health bar & Reload Sprites
    healthBar1.load(":/Images/UISprites/HealthBar/CSE165HealthBar1.png");
    healthBar2.load(":/Images/UISprites/HealthBar/CSE165HealthBar2.png");
    healthBar3.load(":/Images/UISprites/HealthBar/CSE165HealthBar3.png");
    healthBar4.load(":/Images/UISprites/HealthBar/CSE165HealthBar4.png");
    healthBar5.load(":/Images/UISprites/HealthBar/CSE165HealthBar5.png");
    healthBar6.load(":/Images/UISprites/HealthBar/CSE165HealthBar6.png");

    reload1.load(":/Images/UISprites/Reload/Reloading1.png");
    reload2.load(":/Images/UISprites/Reload/Reloading2.png");
    reload3.load(":/Images/UISprites/Reload/Reloading3.png");
    reload4.load(":/Images/UISprites/Reload/Reloading4.png");
    reload5.load(":/Images/UISprites/Reload/Reloading5.png");
    reload6.load(":/Images/UISprites/Reload/Reloading6.png");
    reload7.load(":/Images/UISprites/Reload/Reloading7.png");

    reloadBullets1.load(":/Images/UISprites/Reload/ReloadingBullets1.png");
    reloadBullets2.load(":/Images/UISprites/Reload/ReloadingBullets2.png");
    reloadBullets3.load(":/Images/UISprites/Reload/ReloadingBullets3.png");

    // sound effects
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
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


    // Initialize bullet count
    bulletsLeft = maxBullets;


    // Initialize the reload timer
    reloadTimer = new QTimer(this);
    connect(reloadTimer, &QTimer::timeout, this, &GLWidget::onReloadTimeout);


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
    mungusOne = new EnemyMongus(0.8f, -0.2f);

    mungusTwo = new EnemyMongus(-0.8f, -0.2f);

    skeletonEnemy = new SkeletonEnemy(300, 300);

    skeletonKnife = new SkeletonKnife(420, 350);
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
    if (skeletonEnemy && skeletonEnemy->alive) {
        skeletonEnemy->draw(this);
        skeletonEnemy->updateHitbox();
    }

    if (mungusOne && mungusOne->alive) {
        mungusOne->draw();
        mungusOne->updateHitbox();
    }

    if (mungusTwo && mungusTwo->alive) {
        mungusTwo->draw();
        mungusTwo->updateHitbox();
    }

    // down here, needs to be drawn on top of enemies
    if (skeletonEnemy && skeletonEnemy->alive) {
        if(skeletonEnemy->isThrowing){
            skeletonKnife->draw(this);
            skeletonKnife->updateSkeleThrow(*skeletonEnemy);
        }
    }

    //Need to draw down here for GUI
    //Health Bar
    QPainter healthBar(this);
    //position, scale
    QRectF healthTarget = QRectF(0,0,200,80);
    //we can change the current image depending on health here
    QImage currentHealthImage;
    //Put the if statement here
    currentHealthImage = healthBar1;
    //
    QImage healthImage(currentHealthImage);
    healthBar.drawImage(healthTarget, healthImage);


    //Reload Sprite
    QPainter reloadSprite(this);
    QRectF reloadTarget = QRectF(650,650,160,160);
    QImage currentReloadImage;
    //if statement for reload here
    switch(bulletsLeft){
    case 6:
        currentReloadImage = reload1;
        break;
    case 5:
        currentReloadImage = reload2;
        break;
    case 4:
        currentReloadImage = reload3;
        break;
    case 3:
        currentReloadImage = reload4;
        break;
    case 2:
        currentReloadImage = reload5;
        break;
    case 1:
        currentReloadImage = reload6;
        break;
    case 0:
        currentReloadImage = reload7;
        break;
    default:
        currentReloadImage = reload1;
    }
    if(isReloading){
        currentReloadImage = reloadBullets2;
    }
    //
    QImage reloadImage(currentReloadImage);
    reloadSprite.drawImage(reloadTarget, reloadImage);



    //needed in order to draw every frame
    update();
}

void GLWidget::reloadBullets() {
    // Replenish the bullet count
    bulletsLeft = maxBullets;

    qDebug() << "Bullets reloaded!";
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    bool hitAnyEntity = false; // Flag to track if any entity was hit

    // Play sound when the left button is clicked
    if (event->button() == Qt::LeftButton) {
        // Check if there are bullets left before allowing the player to shoot
        if (bulletsLeft > 0) {
            // Play shooting sound
            mediaPlayer->setSource(QUrl("qrc:/sounds/shooting.mp3"));
            mediaPlayer->stop();
            mediaPlayer->play();

            // Decrease bullet count each time the player shoots
            bulletsLeft--;
        } else {
            // Notify the player they need to reload
            qDebug() << "Out of bullets! Reload needed.";
            return; // Early return to avoid processing further when out of bullets
        }
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
        if (mungusOne) {
            mungusOne->checkHitbox(normalizedX, normalizedY);
            if (mungusOne->isEnemyHit()) {
                hitAnyEntity = true;
                qDebug() << "Hit first entity with health:" << mungusOne->getEnemyHealth();
                // Reduce the health of the first entity
                mungusOne->reduceHealth();

                // Check if the entity is dead and handle it
                if (!mungusOne->alive) {
                    delete mungusOne;
                    mungusOne = nullptr;
                }
            }
        }

        // Check if the click hit the second entity
        if (mungusTwo) {
            mungusTwo->checkHitbox(normalizedX, normalizedY);
            if (mungusTwo->isEnemyHit()) {
                hitAnyEntity = true;
                qDebug() << "Hit second entity with health:" << mungusTwo->getEnemyHealth();
                // Reduce the health of the second entity
                mungusTwo->reduceHealth();

                // Check if the entity is dead and handle it
                if (!mungusTwo->alive) {
                    delete mungusTwo;
                    mungusTwo = nullptr;
                }
            }
        }

        // Check if the click hit the third entity
        if (skeletonEnemy) {
            skeletonEnemy->checkHitbox(normalizedX, normalizedY);
            if (skeletonEnemy->isEnemyHit()) {
                hitAnyEntity = true;
                qDebug() << "Hit third enemy";
                // Reduce the health of the third entity
                skeletonEnemy->reduceHealth();

                // Check if the entity is dead and handle it
                if (!skeletonEnemy->alive) {
                    delete skeletonEnemy;
                    skeletonEnemy = nullptr;
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


void GLWidget::keyPressEvent(QKeyEvent *event) {
    // Check if the 'R' key is pressed
    if (event->key() == Qt::Key_R) {
        // Call the reload function if 'R' key is pressed
        reload();
    }
}

void GLWidget::reload() {
    // Play reloading sound
    mediaPlayer->setSource(QUrl("qrc:/sounds/reloading.mp3"));
    mediaPlayer->play();


    //added isReloading for 1 frame animation
    isReloading = true;
    // Start the timer for 5 seconds
    reloadTimer->start(4350); //can decrease this timer to reload faster <-----------------------eguinos here imp emoji

}

void GLWidget::onReloadTimeout() {
    // Replenish the bullet count
    bulletsLeft = maxBullets;
    qDebug() << "Bullets reloaded after 5-second delay!";

    isReloading = false;
    // Stop the timer
    reloadTimer->stop();
}


//Heal
void GLWidget::heal(){
    qDebug() << "Healing";
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
