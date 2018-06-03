#include "worker.h"
#include <QtCore>
#include <stdio.h>

// --- CONSTRUCTOR ---
Worker::Worker() {
    // you could copy data from constructor arguments to internal variables here.
}

// --- DECONSTRUCTOR ---
Worker::~Worker() {
    // free resources
}

void Worker::start(QScreen *screen) {
    moveToThread(&cThread);
    connect(&cThread, SIGNAL(started()), this, SLOT(process()));
    connect(this, SIGNAL(finished()), &cThread, SLOT(quit()));
    this->screen = screen;
    cThread.start();
}
// START PROCESS
void Worker::process() {
    qDebug() << "start ";

    originalPixmap = screen->grabWindow(0);
    originalPixmap = originalPixmap.scaled(1920, 1080);
//    socket = new Socket("192.168.0.22", 5009);
    QRgb savePixel;

    char *buffer = new char[SIZE_BUFFER];

    int x = 0;
    int y = 0;
    int i = -10;
    int count = 0;

   while(y < originalPixmap.size().height()) {
        x = 0;
        while (x < originalPixmap.size().width()) {
            count++;
            QRgb pixelValue = originalPixmap.toImage().pixel(x, y);
            QColor *color = new QColor(pixelValue);
            if (savePixel != pixelValue || x == 0) {
                i += 10;
                count = 1;
                // X Value
                buffer[i] = ((unsigned short) x >> 8) & 0xff;
                buffer[i + 1] = ((unsigned short) x) & 0xff;
                // Y Value
                buffer[i + 2] = ((unsigned short) y >> 8) & 0xff;
                buffer[i + 3] = ((unsigned short) y) & 0xff;
                // COLOR Value
                buffer[i + 6] = (unsigned char) color->red();
                buffer[i + 7] = (unsigned char) color->green();
                buffer[i + 8] = (unsigned char) color->blue();
                buffer[i + 9] = (unsigned char) color->alpha();
            }
            // Count Value
            buffer[i + 4] = ((unsigned short) count >> 8) & 0xff;
            buffer[i + 5] = ((unsigned short) count) & 0xff;
            savePixel = pixelValue;
            if (i >= SIZE_BUFFER) {
                QByteArray outArray = QByteArray::fromRawData(buffer, i);
                emit sendToSocket(outArray);
                bzero(buffer, i);
                i = 0;
            }
            x++;
        }
        y++;
    }
   QByteArray outArray = QByteArray::fromRawData(buffer, i);
   emit sendToSocket(outArray);
   bzero(buffer, i);
   qDebug() << "end ";
   emit finished();
   delete buffer;
}

//             qDebug("x %d / y %d -> count %d   (red: %d green: %d blue: %d)\n",
//                    (int)x, (int)y, (int)count, (int)color->red(), (int)color->green(), (int)color->blue());


//            qDebug("x %x%x / y %xx -> count %x%x   (red: %x green: %x blue: %x)\n",
//                   buffer[i], buffer[i + 1], buffer[i + 2 ], buffer[i + 3], buffer[i + 4], buffer[i + 5], buffer[i + 6], buffer[i + 7], buffer[i + 8]);
