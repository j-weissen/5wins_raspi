#include "cell_gui.h"

CellGUI::CellGUI(int x, int y)
{
    this->x = x*SIZE;
    this->y = y*SIZE;
    pressed = false;
}

QRectF CellGUI::boundingRect() const
{
    return QRectF(x,y, 100, 100);
}

void CellGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush = (pressed) ? (Qt::blue) : (Qt::transparent);
    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}

void CellGUI::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!pressed){
        qDebug("Press");
        pressed = true;
        update();
        QGraphicsItem::mousePressEvent(event);

    }
}

