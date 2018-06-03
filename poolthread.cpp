#include "poolthread.h"

PoolThread::PoolThread()
{   
}

void PoolThread::startSocket() {
    socket = new Socket(HOST, PORT);
    socket->start();
}

void PoolThread::startScreenShot(QScreen *screen) {
    worker = new Worker();
    worker->start(screen);
    connect(worker, SIGNAL(sendToSocket(QByteArray)), socket, SLOT(writeData(QByteArray)));
}
