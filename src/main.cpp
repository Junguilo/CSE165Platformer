#include "window.h"

#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Set OpenGL Information
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);

    //OpenGLWindow Setup
    Window w;


    //resize basic Qt Window, not the OpenGLView
    w.resize(1080,940);
    w.show();
    return app.exec();
}
