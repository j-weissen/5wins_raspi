#ifndef DATARECIEVEDEVENT_H
#define DATARECIEVEDEVENT_H

#include <QEvent>

class DataRecievedEvent : public QEvent
{
public:
    DataRecievedEvent(int x, int y);
    static QEvent::Type getEventType();
    int getX();
    int getY();
private:
    static const QEvent::Type eventType;
    int x, y;


};

#endif // DATARECIEVEDEVENT_H
