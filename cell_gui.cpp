#include "cell_gui.h"
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QCoreApplication>

int CellGUI::curr = 0;
int CellGUI::size;

CellGUI::CellGUI(int x, int y) : Cell(SYMBOL_FREE)
{
    setObjectName("CellGUI");
    this->x = x;
    this->y = y;
    pressed = false;
}

QRectF CellGUI::boundingRect() const
{
    return QRectF(x*size,y*size, size, size);
}

void CellGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QRectF rec = boundingRect();
    QColor colors[2] = {Qt::green, QColor(255,20,147)};

    if(color == Qt::transparent && pressed){
        color = colors[curr%2];
        curr++;
    }
    QBrush brush = (pressed) ? color : (Qt::transparent);
    painter->fillRect(rec, brush);
    painter->drawRect(rec);


}

void CellGUI::clicked()
{
    if(!pressed){
        pressed = true;
        update();
    }
}

int CellGUI::getSize()
{
    return size;
}

void CellGUI::setSize(int newSize)
{
    size = newSize;
}
