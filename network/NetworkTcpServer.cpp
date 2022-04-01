#include "NetworkTcpServer.h"
#include <iostream>
using namespace std;


NetworkTcpServer::NetworkTcpServer(QString separator) : Network(separator) {
    server = new QTcpServer(this);
    QObject::connect(server, &QTcpServer::newConnection, this, &NetworkTcpServer::acceptConnection);
}

QString NetworkTcpServer::startListening() {
    server->listen(QHostAddress::Any, PORT);

    QTcpSocket socket;
    socket.connectToHost("8.8.8.8", 53); // google DNS, or something else reliable

    socket.waitForConnected();

    return socket.localAddress().toString() + ":" + QString::number(server->serverPort());
}

bool NetworkTcpServer::isListening() {
    return server->isListening();
}

void NetworkTcpServer::acceptConnection() {
    socket = server->nextPendingConnection();
    QObject::connect(socket, &QAbstractSocket::readyRead, this, &Network::recv);
    emit connected();
    server->close();
}

void NetworkTcpServer::close() {
    if (socket != nullptr) Network::close();
    server->close();
}

NetworkTcpServer::~NetworkTcpServer() {
    delete server;
}



