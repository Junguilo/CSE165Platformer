#include "glwidget.h"

//sets the size of our openGLWindow
GLWidget::GLWidget() {
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

    enemyDyingMediaPlayer = new QMediaPlayer(this);
    QAudioOutput *enemyAudioOutput = new QAudioOutput(this);
    enemyDyingMediaPlayer->setAudioOutput(enemyAudioOutput);


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


    //respawn enemies
    // Initialize respawn timers
    mungusOneRespawnTimer = new QTimer(this);
    mungusTwoRespawnTimer = new QTimer(this);
    skeletonEnemyRespawnTimer = new QTimer(this);

    // Connect the respawn timers to their respective methods
    connect(mungusOneRespawnTimer, &QTimer::timeout, this, &GLWidget::respawnMungusOne);
    connect(mungusTwoRespawnTimer, &QTimer::timeout, this, &GLWidget::respawnMungusTwo);
    connect(skeletonEnemyRespawnTimer, &QTimer::timeout, this, &GLWidget::respawnSkeletonEnemy);

    //settin curosr the cross hair
    QPixmap crosshairPixmap(":/Images/crosshair.png");
    QCursor crosshairCursor(crosshairPixmap, crosshairPixmap.width() / 2, crosshairPixmap.height() / 2);

    // Set the cursor for the widget to the crosshair
    setCursor(crosshairCursor);


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
//respawn enemies
void GLWidget::respawnMungusOne() {
    // Respawn mungusOne at its original spawn point and reset its health
    mungusOne = new EnemyMongus(0.8f, -0.2f);
    mungusOneRespawnTimer->stop(); // Stop the timer
}

void GLWidget::respawnMungusTwo() {
    // Respawn mungusTwo at its original spawn point and reset its health
    mungusTwo = new EnemyMongus(-0.8f, -0.2f);
    mungusTwoRespawnTimer->stop(); // Stop the timer
}

void GLWidget::respawnSkeletonEnemy() {
    // Respawn skeletonEnemy at its original spawn point and reset its health
    skeletonEnemy = new SkeletonEnemy(300, 300);
    skeletonKnife = new SkeletonKnife(420, 350);
    skeletonEnemyRespawnTimer->stop(); // Stop the timer
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
    } else {
        //if the skeleEnemy is dead stop the knives!!
        skeletonKnife->animationTimer->stop();
        skeletonKnife->scaleTimer->stop();
    }


    //check if enemies hit the player
    if(skeletonEnemy && skeletonKnife->hitPlayer){
        health -= skeletonKnife->attack;
        skeletonKnife->hitPlayer = false;
        updateHealth();
    }

    if(mungusOne && mungusOne->alive && mungusOne->hitPlayer){
        health -= mungusOne->attack;
        mungusOne->hitPlayer = false;
        updateHealth();
    }

    if(mungusTwo && mungusTwo->alive && mungusTwo->hitPlayer){
        health -= mungusTwo->attack;
        mungusTwo->hitPlayer = false;
        updateHealth();
    }

    //this does not stop despite health would be -1
    if(mungusOne && mungusOne->alive && mungusOne->isCenter){
        mungusOne->updateAttack();
        mungusOne->isCenter = false;
    }

    if(mungusTwo && mungusTwo->alive && mungusTwo->isCenter){
        mungusTwo->updateAttack();
        mungusTwo->isCenter = false;
    }



    //Need to draw down here for GUI
    //Health Bar
    QPainter healthBar(this);
    //position, scale
    QRectF healthTarget = QRectF(0,0,200,80);
    //we can change the current image depending on health here
    QImage currentHealthImage;
    //Put the if statement here
    switch(health){
    case 5:
        currentHealthImage = healthBar1;
        break;
    case 4:
        currentHealthImage = healthBar2;
        break;
    case 3:
        currentHealthImage = healthBar3;
        break;
    case 2:
        currentHealthImage = healthBar4;
        break;
    case 1:
        currentHealthImage = healthBar5;
        break;
    default:
        currentHealthImage = healthBar6;
    }
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
    // Mouse press event logic
    bool hitAnyEntity = false;

    if (event->button() == Qt::LeftButton && bulletsLeft > 0 && !isReloading) {
        // Shooting logic
        mediaPlayer->setSource(QUrl("qrc:/sounds/shooting.mp3"));
        mediaPlayer->play();
        bulletsLeft--;
        updateBullets();

        // Process mouse clicks on entities
        float centerX = event->pos().x() - width() / 2.0f;
        float centerY = height() / 2.0f - event->pos().y();
        float normalizedX = (2.0f * centerX) / width();
        float normalizedY = (2.0f * centerY) / height();

        qDebug() << "Position:" << normalizedX << "," << normalizedY;

        // Reset hitAnyEntity to false at the beginning of each check
        hitAnyEntity = false;

        // Check hitboxes of each entity
        // Each check is separate and independent
        if (mungusOne && mungusOne->alive) {
            mungusOne->checkHitbox(normalizedX, normalizedY);
            if (mungusOne->getHit()) {
                mungusOne->reduceHealth();
                qDebug() << "Hit mungusOne with health:" << mungusOne->getHealth();
                //mugus hit sound
                enemyDyingMediaPlayer->setSource(QUrl("qrc:/sounds/mugus.mp3"));
                enemyDyingMediaPlayer->play();


                if (!mungusOne->alive) {
                    updatePoints(points + mungusOne->pointsGiven);

                    delete mungusOne;
                    mungusOne = nullptr;
                    mungusOneRespawnTimer->start(5000);
                }
                hitAnyEntity = true;
            }
        }

        if (mungusTwo && mungusTwo->alive) {
            mungusTwo->checkHitbox(normalizedX, normalizedY);
            if (mungusTwo->getHit()) {
                mungusTwo->reduceHealth();
                qDebug() << "Hit mungusTwo with health:" << mungusTwo->getHealth();
                //mugus hit sound
                enemyDyingMediaPlayer->setSource(QUrl("qrc:/sounds/mugus.mp3"));
                enemyDyingMediaPlayer->play();

                if (!mungusTwo->alive) {
                    updatePoints(points + mungusTwo->pointsGiven);

                    delete mungusTwo;
                    mungusTwo = nullptr;
                    mungusTwoRespawnTimer->start(5000);
                }
                hitAnyEntity = true;
            }
        }

        if (skeletonEnemy && skeletonEnemy->alive) {
            skeletonEnemy->checkHitbox(normalizedX, normalizedY);
            if (skeletonEnemy->getHit()) {
                skeletonEnemy->reduceHealth();
                qDebug() << "Hit skeletonEnemy with health:" << skeletonEnemy->getHealth();
                //mugus hit sound
                enemyDyingMediaPlayer->setSource(QUrl("qrc:/sounds/skeleton.mp3"));
                enemyDyingMediaPlayer->play();

                if (!skeletonEnemy->alive) {
                    //gives the user points on enemy death
                    updatePoints(points + skeletonEnemy->pointsGiven);
                    //delete skeletonKnife;
                    delete skeletonEnemy;
                    skeletonEnemy = nullptr;
                    skeletonEnemyRespawnTimer->start(5000);
                }
                hitAnyEntity = true;
            }
        }

        // Check if no entity was hit
        if (!hitAnyEntity) {
            qDebug() << "No entity was hit.";
        }
    } else {
        mediaPlayer->setSource(QUrl("qrc:/sounds/empty.mp3"));
        mediaPlayer->play();

        qDebug() << "Out of bullets! Reload needed.";
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
    updateBullets();
    // Start the timer for 5 seconds //4350
    reloadTimer->start(3000); //can decrease this timer to reload faster <-----------------------eguinos here imp emoji :pensive:

}

void GLWidget::onReloadTimeout() {
    // Replenish the bullet count
    bulletsLeft = maxBullets;
    qDebug() << "Bullets reloaded after 5-second delay!";

    isReloading = false;
    updateBullets();
    // Stop the timer
    reloadTimer->stop();
}

void GLWidget::updatePoints(int newPoints){
    points = newPoints;
    emit pointsChanged(points);
}

void GLWidget::updateBullets(){
    emit bulletsChanged(bulletsLeft);
}

void GLWidget::updateHealth(){
    emit healthChanged(health);
}

//Heal
void GLWidget::heal(){
    health = 5;
    updateHealth();
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
