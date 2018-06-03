#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtWidgets>
#include "socket.h"
#include "worker.h"
#include "poolthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onWorkerDone();

private slots:
    void shootScreen();
    void getPixelsImage();
    void updateScreenshotLabel();

private:
    Ui::MainWindow *ui;
    QPixmap originalPixmap;
    PoolThread *poolThread;
};

#endif // MAINWINDOW_H
