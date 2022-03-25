#include "dataRecievedEvent.h"

const QEvent::Type DataRecievedEvent::eventType = static_cast<QEvent::Type>(QEvent::registerEventType());

DataRecievedEvent::DataRecievedEvent(int x, int y) : QEvent(eventType) {
    this->action = ACTION_TURN;
    this->x = x;
    this->y = y;
}

DataRecievedEvent::DataRecievedEvent(int action) : QEvent(eventType) {
    if (action == ACTION_TURN) {
        action = ACTION_ERROR;
    }
    this->action = action;
    this->x = NULL;
    this->y = NULL;
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

int DataRecievedEvent::getAction() {
    return action;
}
