#ifndef NETWORK_H
#define NETWORK_H

#include <QTcpServer>
#include <QTcpSocket>

#include <QObject>


class Network : public QObject {
    Q_OBJECT
public:
    Network(QString separator);
    ~Network();

    void send(QString sendData);
    QString getRecvData();

    bool setPort(quint16 port);

    void close();

protected:
    QTcpSocket *socket = nullptr;
    QByteArray recvData;
    QByteArray incomingData;
    QByteArray separator;
    quint16 PORT;

    QByteArray rmvSeparator(QByteArray arr);

signals:
    void connected();
    void dataRecieved();

public slots:
    void recv();
};

#endif // NETWORK_H
