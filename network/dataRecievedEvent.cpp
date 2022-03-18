#include "dataRecievedEvent.h"

const QEvent::Type DataRecievedEvent::eventType = static_cast<QEvent::Type>(QEvent::registerEventType());

DataRecievedEvent::DataRecievedEvent(int x, int y) : QEvent(eventType) {
    this->x = x;
    this->y = y;
}

QEvent::Type DataRecievedEvent::getEventType() {
    return eventType;
}

int DataRecievedEvent::getX() {
    return x;
}

int DataRecievedEvent::getY() {
    return y;
}
