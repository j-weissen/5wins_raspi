#include "Network.h"
using namespace std;
#include <QTimer>

Network::Network(QString separator, int port) {
    this->setPort(port);
    this->separator = separator.toUtf8().toBase64();
    incomingData.clear();
}

Network::~Network() {
    delete socket;
}

bool Network::setPort(quint16 port) {
    bool rv = false;
    QTcpServer portTestServer;
    if (portTestServer.listen(QHostAddress::Any, port)) {
        portTestServer.close();
        PORT = port;
        rv = true;
    }
    return rv;
}



QString Network::getRecvData() {
    return QString::fromUtf8(QByteArray::fromBase64(recvData));
}

void Network::send(QString sendData) {
    QByteArray data = sendData.toUtf8().toBase64();
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(data.append(separator));
    }
}

QByteArray Network::rmvSeparator(QByteArray arr) {
    QString str = QString::fromUtf8(QByteArray::fromBase64(arr));
    str.remove(QString::fromUtf8(QByteArray::fromBase64(separator)));
    return QByteArray(str.toUtf8().toBase64());
}

void Network::recv() {
    incomingData += socket->readAll();
    if (!incomingData.isEmpty()) {
        if(!incomingData.contains(separator)) {
            recv();
        } else {
            int bytes = incomingData.indexOf(separator);               // Find the end of message
            recvData = incomingData.left(bytes);
            incomingData = rmvSeparator(incomingData.mid(bytes));                    // Keep the data read too early
            emit dataRecieved();
        }
    }
}

