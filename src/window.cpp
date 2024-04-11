#include "window.h"
#include "glwidget.h"
#include <QtWidgets>
#include <QGridLayout>


Window::Window(){
    //now we can setup multiple other QTWidgets here
    setWindowTitle(tr("Shooter"));

    //GL Setup with buttons on bottom
    setupGLWidget();
}


void Window::setupGLWidget(){
    glWidget = new GLWidget;

    //sets keyboard input onto glWindow
    glWidget->setFocusPolicy(Qt::StrongFocus);

    //setup our text
    QLabel *healthText = new QLabel(tr("Health:[----------]"));
    healthText->setAlignment(Qt::AlignHCenter);

    QLabel *ammoText = new QLabel(tr("Ammo:[----------]"));
    ammoText->setAlignment(Qt::AlignHCenter);

    QLabel *pointText = new QLabel(tr("Points: 0"));
    pointText -> setAlignment(Qt::AlignCenter);

    QPushButton *reloadButton = new QPushButton("Reload", this);
    QPushButton *healButton = new QPushButton("Heal(0)", this);

    //We don't use QMainWindow because that already sets up our layout for us
    //we want to use QGridLayout with QWidget as our window
    //Grid layout to have our window separate to buttons on the bottom
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(glWidget, 0,0, 1, 3); //last two digits, rowspan, colspan
    layout->addWidget(healthText, 1, 0);
    layout->addWidget(ammoText, 1, 1);
    layout->addWidget(pointText, 1, 2);

    layout->addWidget(healButton, 2, 0);
    layout->addWidget(reloadButton, 2, 1);
    setLayout(layout);

}
