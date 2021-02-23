#ifndef CellGUI_H
#define CellGUI_H

#include <QPainter>
#include <QGraphicsItem>
#include <QtDebug>
#include "cell.h"

class CellGUI : public QGraphicsItem, public Cell
{
public:
    static const int SIZE = 50;
    static int curr;
    static bool clickable;
    bool pressed;

    CellGUI(int x, int y);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int x,y;
    QColor color = Qt::transparent;

};

#endif // CellGUI_H
