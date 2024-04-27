#ifndef WINDOW_H
#define WINDOW_H

#include "qlabel.h"
#include <QWidget>

class GLWidget;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private:
    //keep a seperate window for OpenGL to have other QTWidgets draw over it.
    GLWidget *glWidget;

    //QLabels
    QLabel *pointText;
    QLabel *ammoText;
    QLabel *healthText;

    void updatePointsLabel(int newPoints);
    void updateAmmoLabel(int newAmmo);
    void updateHealthLabel(int newHealth);

    //the QOpenGLWindow
    void setupGLWidget();
};
#endif // WINDOW_H
