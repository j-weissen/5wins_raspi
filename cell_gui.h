#ifndef CellGUI_H
#define CellGUI_H

#include <QPainter>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QtDebug>
#include "cell.h"

class CellGUI : public QGraphicsItem, public Cell, public QObject
{
public:
    static int curr;
    bool pressed;

    int getX(){return x;};
    int getY(){return y;};


    CellGUI(int x, int y);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void clicked();

    static int getSize();
    static void setSize(int newSize);

protected:



private:

    static int size;
    int x,y;
    QColor color = Qt::transparent;

};

#endif // CellGUI_H
