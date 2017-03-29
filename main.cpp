#include "mainwindow.h"
#include "screenshot.h"
#include <QApplication>
#include "worker.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
//    QApplication app(argc, argv);

//        Screenshot screenshot;
//        screenshot.move(QApplication::desktop()->availableGeometry(&screenshot).topLeft() + QPoint(20, 20));
//        screenshot.show();
//        return app.exec();
}
