#include "window.h"
#include "glwidget.h"
#include <QtWidgets>
#include <QGridLayout>


Window::Window(){
    //now we can setup multiple other QTWidgets here
    setWindowTitle(tr("Maybe a Platformer"));

    //GL Setup with buttons on bottom
    setupGLWidget();
}


void Window::setupGLWidget(){
    glWidget = new GLWidget;

    //sets keyboard input onto glWindow
    glWidget->setFocusPolicy(Qt::StrongFocus);

    //setup our text
    QLabel *test = new QLabel(tr("testin"));
    test->setAlignment(Qt::AlignHCenter);
    QLabel *testTwo = new QLabel(tr("testinTwo"));
    testTwo->setAlignment(Qt::AlignHCenter);

    //We don't use QMainWindow because that already sets up our layout for us
    //we want to use QGridLayout
    //Grid layout to have our window separate to buttons on the bottom
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(glWidget, 0,0, 1, 2); //last two digits, rowspan, colspan
    layout->addWidget(test, 1, 0);
    layout->addWidget(testTwo, 1, 1);
    setLayout(layout);

}
