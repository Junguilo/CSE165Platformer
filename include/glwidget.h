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
public:
    GLWidget();
    ~GLWidget() override;
private:
    //Standard OpenGLWidget Functions
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
    QMediaPlayer *backgroundPlayer;
    void keyPressEvent(QKeyEvent *event) override;

    // Bullet count and maximum capacity
    int bulletsLeft;
    const int maxBullets = 6;

    // Reload bullets
    void reloadBullets();
    void onReloadTimeout();

    QTimer *reloadTimer;
    bool isReloading = false;
    void reload() ;

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

    //another method for time used in another example
    int elapsed;

    //calculating the currentTime - elapsedTime diff
    float timeDelta;
    std::chrono::time_point<std::chrono::steady_clock> lastFrameTime;
};

#endif // GLWIDGET_H
