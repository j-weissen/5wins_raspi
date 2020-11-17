#ifndef CellGUI_H
#define CellGUI_H

#include <QPainter>
#include <QGraphicsItem>
#include <QtDebug>

class CellGUI : public QGraphicsItem
{
public:
    CellGUI(int x, int y);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    bool pressed;
protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    const int SIZE = 50;
    int x,y;

};

#endif // CellGUI_H
