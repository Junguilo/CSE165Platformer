#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>
//testing
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Set OpenGL Information
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);

    //OpenGLWindow Setup
    MainWindow w;
    w.resize(800,600);

    //layout for MainWindow
    auto layout = new QVBoxLayout;
    w.setLayout(layout);


    //testing widgets for qt function
    auto bottomWidget = new QWidget;
    auto bottomLayout = new QHBoxLayout(bottomWidget);
    bottomWidget->setLayout(bottomLayout);
   layout->addWidget(bottomWidget);


    auto button = new QPushButton("click");
    button->setGeometry(10,10,10,10);
    button->move(10,10);
    bottomLayout->addWidget(button);
    auto button1 = new QPushButton("clicky");
    bottomLayout->addWidget(button1);

    layout->addLayout(bottomLayout);

    w.show();
    return app.exec();
}
