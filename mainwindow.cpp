#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
 //   QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(shootScreen()));
//    timer->start(30);
    worker = new Worker();
    shootScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onWorkerDone() {
    qDebug() << "thread done !!!!";
}

void MainWindow::getPixelsImage() {

}


void MainWindow::shootScreen()
{
    QScreen *screen = QGuiApplication::screens().first();
    if (const QWindow *window = windowHandle())
        screen = window->screen();
    if (!screen)
        return;

    originalPixmap = screen->grabWindow(0);
    originalPixmap = originalPixmap.scaled(1920, 1080);
    worker->start(originalPixmap);
    connect(worker, SIGNAL(finished()), this, SLOT(onWorkerDone()));
    updateScreenshotLabel();
}

void MainWindow::updateScreenshotLabel()
{
    ui->screenshotLabel->setPixmap(originalPixmap.scaled(ui->screenshotLabel->size(),
                                                     Qt::KeepAspectRatio,
                                                     Qt::SmoothTransformation));
}
