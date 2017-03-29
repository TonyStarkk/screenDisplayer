#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
// divisible par 7 (size of one pixel) + 2 (size of chunck)
#define SIZE_BUFFER 4090

QT_BEGIN_NAMESPACE
    class QTcpSocket;
    class QNetworkSession;
QT_END_NAMESPACE

class Socket : public QObject
{
    Q_OBJECT

public:
    Socket(QString ip, int port);
    ~Socket();

public slots:
    void createSocket();
    bool writeData(QByteArray data);


private slots:
    void readFortune();
    QByteArray IntToArray(qint32 source);
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket              *tcpSocket;
    QDataStream             in;
    QString                 currentFortune;
    QNetworkSession         *networkSession;

    Socket                  *socket;
    QString                 _ip;
    int                     _port;
};

#endif // SOCKET_H
