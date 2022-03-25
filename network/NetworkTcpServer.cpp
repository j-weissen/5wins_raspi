#include "NetworkTcpServer.h"
#include <iostream>
using namespace std;


NetworkTcpServer::NetworkTcpServer(QString separator) : Network(separator) {
    server = new QTcpServer(this);
    QObject::connect(server, &QTcpServer::newConnection, this, &NetworkTcpServer::acceptConnection);
}

QString NetworkTcpServer::startListening() {
    server->listen(QHostAddress::Any, PORT);
    return server->serverAddress().toString() + ":" + QString::number(server->serverPort());
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

NetworkTcpServer::~NetworkTcpServer() {
    delete server;
}



