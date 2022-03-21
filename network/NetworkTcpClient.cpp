#include "NetworkTcpClient.h"

NetworkTcpClient::NetworkTcpClient(QString separator) : Network(separator) {
    socket = new QTcpSocket;
    _addr = new QHostAddress;
    QObject::connect(socket, &QAbstractSocket::readyRead, this, &Network::recv);
    QObject::connect(socket, &QTcpSocket::errorOccurred, this, &NetworkTcpClient::displayError);
    QObject::connect(socket, &QTcpSocket::connected, this, &NetworkTcpClient::onSocketConnected);
}

NetworkTcpClient::~NetworkTcpClient() {
    delete _addr;
}

void NetworkTcpClient::setAddr(QHostAddress addr) {
    *_addr = addr;
    return;
}

QHostAddress NetworkTcpClient::getAddr() {
    return *_addr;
}

void NetworkTcpClient::connectToServer() {
    socket->connectToHost(*_addr, PORT);
}

void NetworkTcpClient::onSocketConnected() {
    emit connected();
}

void NetworkTcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "Remote host closed";
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found. Please check the host name and port settings.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct.";
        break;
    default:
        qDebug() << socket->errorString();
    }
}



