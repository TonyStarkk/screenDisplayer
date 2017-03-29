#ifndef WORKER_H
#define WORKER_H

#include <QtCore>
#include <QThread>
#include <QtWidgets>
#include "socket.h"

class Worker : public QObject {
    Q_OBJECT

public:
    Worker();
    ~Worker();
    void start(const QPixmap &pixmap);

public slots:
    void process();

signals:
    void finished();
    void sendToSocket(QByteArray);
    void error(QString err);

private:
    // add your variables here
    QThread cThread;
    QPixmap originalPixmap;
    Socket  *socket;
};
#endif // WORKER_H
