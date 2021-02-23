#include "cell_gui.h"
#include <QGraphicsSceneMouseEvent>
#include <QString>

int CellGUI::curr = 0;
bool CellGUI::clickable = false;

CellGUI::CellGUI(int x, int y) : Cell(SYMBOL_FREE)
{
    this->x = x*SIZE;
    this->y = y*SIZE;
    pressed = false;
}

QRectF CellGUI::boundingRect() const
{
    return QRectF(x,y, SIZE, SIZE);
}

void CellGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QRectF rec = boundingRect();
    QColor colors[2] = {Qt::blue, Qt::black};

    if(color == Qt::transparent && pressed){
        color = colors[curr%2];
        curr++;
        CellGUI::clickable = false;
    }
    QBrush brush = (pressed) ? color : (Qt::transparent);
    painter->fillRect(rec, brush);
    painter->drawRect(rec);


}

void CellGUI::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!pressed){
        QString temp;
        qDebug() << "Pressed cell X: " << QString::number(x/SIZE) << " Y: " + QString::number(y/SIZE);
        qDebug() << event->pos() << QString("%1").arg((unsigned long long int)this);
        pressed = true;
        update();
        QGraphicsItem::mousePressEvent(event);

    }
}

