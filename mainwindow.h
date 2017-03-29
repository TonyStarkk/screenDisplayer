#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtWidgets>
#include "socket.h"
#include "worker.h"


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
    Socket *socket;
    Worker *worker;
};

#endif // MAINWINDOW_H
