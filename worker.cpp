#include "worker.h"
#include <QtCore>

// --- CONSTRUCTOR ---
Worker::Worker() {
    // you could copy data from constructor arguments to internal variables here.
}

// --- DECONSTRUCTOR ---
Worker::~Worker() {
    // free resources
}

void Worker::start(const QPixmap &pixmap) {
    moveToThread(&cThread);
    connect(&cThread, SIGNAL(started()), this, SLOT(process()));
    connect(this, SIGNAL(finished()), &cThread, SLOT(quit()));
//    connect(this, SIGNAL(sendToSocket(QByteArray)), socket, SLOT(writeData(QByteArray)));
//    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
//    connect(&cThread, SIGNAL(finished()), &cThread, SLOT(deleteLater()));
    originalPixmap = pixmap;
    cThread.start();
}


// --- PROCESS ---
// Start processing data.
void Worker::process() {
    qDebug() << "start ";
    socket = new Socket("192.168.0.22", 5009);
    socket->createSocket();
    connect(this, SIGNAL(sendToSocket(QByteArray)), socket, SLOT(writeData(QByteArray)));

    unsigned char *buffer = (unsigned char*) malloc(sizeof(char) * SIZE_BUFFER);
    int x = 0;
    int y = 0;
    int i = 2;

   while(y < originalPixmap.size().height()) {
        x = 0;
        while (x < originalPixmap.size().width()) {
            QRgb pixelValue = originalPixmap.toImage().pixel(x, y);
            QColor *color = new QColor(pixelValue);
            buffer[i] = ((unsigned short) x >> 8) & 0xff;
            buffer[i + 1] = ((unsigned short) x) & 0xff;
            buffer[i + 2] = ((unsigned short) y >> 8) & 0xff;
            buffer[i + 3] = ((unsigned short) y) & 0xff;
            buffer[i + 4] = (unsigned char) color->red();
            buffer[i + 5] = (unsigned char) color->green();
            buffer[i + 6] = (unsigned char) color->blue();
            i += 7;
            if (i >= SIZE_BUFFER) {
                buffer[0] = ((unsigned short) i >> 8) & 0xff;
                buffer[1] = ((unsigned short) i) & 0xff;
                QByteArray outArray = QByteArray::fromRawData((char *)buffer, i);
                emit sendToSocket(outArray);
                bzero(buffer, i);
                i = 2;
            }
            x++;
        }
        y++;
    }
   buffer[0] = ((unsigned short) i >> 8) & 0xff;
   buffer[1] = ((unsigned short) i) & 0xff;
   QByteArray outArray = QByteArray::fromRawData((char *)buffer, i);
   emit sendToSocket(outArray);
   bzero(buffer, i);
   free(buffer);
   qDebug() << "end ";
    emit finished();
}

