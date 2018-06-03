#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QDataStream>
#include <QThread>
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
    void start(const QPixmap &pixmap);

public slots:
    void createSocket();
    bool writeData(QByteArray data);
    void start();

private slots:
    void readFortune();
    QByteArray IntToArray(qint32 source);
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket              *tcpSocket;
    QThread                 cThread;
    QDataStream             in;
    QString                 currentFortune;
    QNetworkSession         *networkSession;

    Socket                  *socket;
    QString                 _ip;
    int                     _port;
};

#endif // SOCKET_H
