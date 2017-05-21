#ifndef BOARDITEM_H
#define BOARDITEM_H

#include "board.h"

#include <QColor>
#include <QGraphicsItem>


class BoardItem : public QGraphicsItem
{
public:
    BoardItem();
    ~BoardItem();

    void start();
    void stop();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);


    void updateScale(double newScale);
    void updateTime(double newTime);

    void setStyle(bool a, bool b, bool c, bool d);


    Board *m_board;

private:

    bool showCol;
    bool showProb;
    bool showMaxProb;
    bool showPivots;

    double m_scale;

};

#endif // BOARDITEM_H
