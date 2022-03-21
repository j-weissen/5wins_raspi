#ifndef NETWORKTCPCLIENT_H
#define NETWORKTCPCLIENT_H
#include "Network.h"
#include <QTcpSocket>

class NetworkTcpClient : public Network
{
    Q_OBJECT
public:
    NetworkTcpClient(QString separator);
    ~NetworkTcpClient();

    void connectToServer();
    void setAddr(QHostAddress addr);
    QHostAddress getAddr();

protected:
    QHostAddress *_addr = nullptr;

public slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void onSocketConnected();

};

#endif // NETWORKTCPCLIENT_H
