#ifndef DATARECIEVEDEVENT_H
#define DATARECIEVEDEVENT_H

#include <QEvent>

class DataRecievedEvent : public QEvent
{
public:
    DataRecievedEvent(int action);
    DataRecievedEvent(int x, int y);
    static QEvent::Type getEventType();
    static constexpr int ACTION_ERROR = -1;
    static constexpr int ACTION_TURN = 0;
    static constexpr int ACTION_RESET = 1;
    static constexpr int ACTION_EXIT = 2;

    int getX();
    int getY();
    int getAction();
private:
    static const QEvent::Type eventType;
    int action, x, y;


};

#endif // DATARECIEVEDEVENT_H
