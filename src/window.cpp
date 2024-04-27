#include "window.h"
#include "glwidget.h"
#include <QtWidgets>
#include <QGridLayout>


Window::Window(){
    //now we can setup multiple other QTWidgets here
    setWindowTitle(tr("Shooter"));

    //GL Setup with buttons on bottom, will be easy to put the start game here
    setupGLWidget();
}


void Window::setupGLWidget(){
    glWidget = new GLWidget;

    //sets keyboard input onto glWindow
    glWidget->setFocusPolicy(Qt::StrongFocus);

    //setup our text
    healthText = new QLabel(tr("Health: 5"));
    healthText->setAlignment(Qt::AlignHCenter);

    ammoText = new QLabel(tr("Ammo: 6"));
    ammoText->setAlignment(Qt::AlignHCenter);

    pointText = new QLabel(tr("Points: 0"));
    pointText->setAlignment(Qt::AlignCenter);


    //This will update the Labels during gameplay
    connect(glWidget, &GLWidget::pointsChanged, this, &Window::updatePointsLabel);
    connect(glWidget, &GLWidget::bulletsChanged, this, &Window::updateAmmoLabel);
    //connect(glWidget, &GLWidget::healthChanged, this, &Window::updateHealthLabel);

    QPushButton *reloadButton = new QPushButton("Reload", this);
    QPushButton *healButton = new QPushButton("Heal", this);
    //connect the clicked signal of the reloadButton to the reload() function
    connect(reloadButton, &QPushButton::clicked, glWidget, &GLWidget::reload);
    connect(healButton, &QPushButton::clicked, glWidget, &GLWidget::heal);

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


void Window::updatePointsLabel(int newPoints){
    QString pointsString = QString::number(newPoints);
    pointText->setText(tr("Points: ") + pointsString);
}

void Window::updateAmmoLabel(int newAmmo){
    if(!glWidget->isReloading){
        QString ammoString = QString::number(newAmmo);
        ammoText->setText(tr("Ammo: ") + ammoString);
    } else {
        ammoText->setText(tr("RELOADING"));
    }
}

void Window::updateHealthLabel(int newHealth){
    QString healthString = QString::number(newHealth);
    //qDebug() << ammoString;
    ammoText->setText(tr("Health: ") + healthString);
}
