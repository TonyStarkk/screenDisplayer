#include "socket.h"

Socket::Socket(QString ip, int port) : networkSession(Q_NULLPTR), _ip(ip), _port(port)
{

}

void Socket::createSocket()
{
    tcpSocket = new QTcpSocket();
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    connect(tcpSocket, &QIODevice::readyRead, this, &Socket::createSocket);

    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &Socket::displayError);
    tcpSocket->connectToHost(_ip, _port);
    tcpSocket->waitForConnected();
}

void Socket::readFortune()
{
    in.startTransaction();

    QString nextFortune;
    in >> nextFortune;

    if (!in.commitTransaction())
        return;

    if (nextFortune == currentFortune) {
        QTimer::singleShot(0, this, &Socket::createSocket);
        return;
    }

    currentFortune = nextFortune;
}

void Socket::start() {
    moveToThread(&cThread);
    connect(&cThread, SIGNAL(started()), this, SLOT(createSocket()));
//    connect(this, SIGNAL(finished()), &cThread, SLOT(quit()));
    cThread.start();
}


void Socket::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            qDebug() << "Host not found";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            qDebug() << "Connection refused";
            break;
        default:
            qDebug() << "Error : " << tcpSocket->errorString();
    }
}

QByteArray Socket::IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}

bool Socket::writeData(QByteArray data)
{
    qDebug("send sockettttt");
    if(tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
//        tcpSocket->write(IntToArray(data.size())); //write size of data
        tcpSocket->write(data); //write the data itself
//        tcpSocket->write("bonjour", strlen("bonjour"));
        tcpSocket->flush();
        return tcpSocket->waitForBytesWritten();
    }
    else
        return false;
}

Socket::~Socket()
{

}
