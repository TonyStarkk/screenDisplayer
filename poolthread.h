#ifndef POOLTHREAD_H
#define POOLTHREAD_H

#include <QObject>
#include <QtCore>
#include "socket.h"
#include "worker.h"
#define HOST "192.168.0.22"
#define PORT 5009

class PoolThread: public QObject {
    Q_OBJECT

public:
    PoolThread();

    void startSocket();
    void startScreenShot(QScreen *screen);

private:
    Socket  *socket;
    Worker  *worker;
};

#endif // POOLTHREAD_H
