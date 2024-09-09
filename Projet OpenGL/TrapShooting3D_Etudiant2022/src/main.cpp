#include <QApplication>
#include <QGuiApplication>
#include <cstdlib>
#include <ctime>
#include "Viewer.h"
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    //Q_INIT_RESOURCE(resources_dataQGLShaderViewer);

    // Set OpenGL Version information
    // Note: This format must be set before show() is called.
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setSamples(1);       // 16 avant z-fight
    format.setDepthBufferSize(32);
    format.setMajorVersion(4);
    format.setMinorVersion(5);

  // Prise en charge de la stéréo
    format.setStereo(true);

qDebug() << " avant constructeur";
 // Set the window up
    QMap<QString, QString> params;
    Viewer window('A', params);
    window.setFormat(format);
    window.resize(QSize(800, 600));
    window.show();
 
    return app.exec();
}
