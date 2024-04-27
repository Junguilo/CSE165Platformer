#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QApplication>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QDebug>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QTimer>

//move this to its own enemy Spawner class
#include "enemymongus.h"
#include "skeletonenemy.h"
#include "skeletonknife.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget();
    ~GLWidget() override;

    int points = 0;
    int health = 5;
    int bulletsLeft;

    bool isReloading = false;

public slots:
    void reload();
    void heal();

signals:
    void pointsChanged(int newPoints);
    void bulletsChanged(int newBullets);
    void healthChanged(int newHealth);

private:
    //Standard OpenGLWidget Functions
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
    QMediaPlayer *backgroundPlayer;
    void keyPressEvent(QKeyEvent *event) override;

    //respawning enemies
    QTimer *mungusOneRespawnTimer;
    QTimer *mungusTwoRespawnTimer;
    QTimer *skeletonEnemyRespawnTimer;

    void respawnMungusOne();
    void respawnMungusTwo();
    void respawnSkeletonEnemy();


    // Bullet count and maximum capacity
    const int maxBullets = 6;

    // Reload bullets
    void reloadBullets();
    void onReloadTimeout();

    QTimer *reloadTimer;

    //all Signal Functions needed for the QTtext
    void updatePoints(int newPoints);
    void updateBullets();
    void updateHealth();


    //Other QT functions to handle input
    //void keyPressEvent(QKeyEvent *event) override;
    //void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *event) override;
    //void mouseMoveEvent(QMouseEvent *event) override;

    EnemyMongus *mungusOne;
    EnemyMongus *mungusTwo;
    SkeletonEnemy *skeletonEnemy;
    SkeletonKnife *skeletonKnife;
    void mapDraw();
    //drawing health bar & reload sprites
    QImage healthBar1;
    QImage healthBar2;
    QImage healthBar3;
    QImage healthBar4;
    QImage healthBar5;
    QImage healthBar6;

    QImage reload1;
    QImage reload2;
    QImage reload3;
    QImage reload4;
    QImage reload5;
    QImage reload6;
    QImage reload7;

    QImage reloadBullets1;
    QImage reloadBullets2;
    QImage reloadBullets3;
};

#endif // GLWIDGET_H
