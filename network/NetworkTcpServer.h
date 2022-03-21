#ifndef NETWORKTCPSERVER_H
#define NETWORKTCPSERVER_H
#include "Network.h"
#include <QTcpServer>

class NetworkTcpServer : public Network
{
    Q_OBJECT
public:
    NetworkTcpServer(QString separator);
    ~NetworkTcpServer();

    QString startListening();
    bool isListening();

protected:
    QTcpServer *server = nullptr;

public slots:
    void acceptConnection();
};

#endif // NETWORKTCPSERVER_H
