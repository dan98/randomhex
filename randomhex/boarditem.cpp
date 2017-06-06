#include "boarditem.h"

#include <QPainter>
#include <iostream>
#include <utility>

#include <cmath>

BoardItem::BoardItem()
    : m_board(0)
{
    this->showCol = 0;
    this->showProb = 0;
    this->showMaxProb = 0;
    this->showPivots = 0;
}

BoardItem::~BoardItem()
{
    if (m_board)
    {
        stop();
    }
}

void BoardItem::start()
{
}

void BoardItem::stop()
{
    delete m_board;
    m_board = 0;
}

void BoardItem::setStyle(bool a, bool b, bool c, bool d)
{
  showCol = a;
  showPivots = b;
  showProb = c;
  showMaxProb = d;
}

QRectF BoardItem::boundingRect() const
{
    if (!m_board)
    {
        return QRectF(0.0, 0.0, 0.0, 0.0);
    }
    else
    {
        const double max = (2*m_board->boardSize())
                          * m_scale;

        return QRectF(QPointF(-max, -max), QPointF(max, max));
    }
}

void BoardItem::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *,
                               QWidget *)
{
    if (!m_board)
    {
        return;
    }

    int n = m_board->boardSize() +2;

    double sq3 = sqrt(3.0L);

    double l = n*(sq3) + (n-1)*sq3/2;
    double xs = -l/2.0 + 1;
    double xc = xs;
    double yc = -(1.5 * (n) + 0.5)/2 + 1;

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));

    double mx = 0.00001;
    std::pair<int, int> maxProb = {-1, -1};
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            if(m_board->getProb(i,j) > mx){
              mx = m_board->getProb(i,j);
              maxProb = std::make_pair(i,j);
            }
        }
    }
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            QPolygonF hex;
            for(int k=0; k<6; ++k){
                hex<<QPointF(xc + cos(acos(-1.0) / 180 * (60*k + 30)),
                             yc + sin(acos(-1.0) / 180 * (60*k + 30)))*m_scale;
            }

            if((showCol || m_board->isFixed(i, j)) && m_board->getColor(i, j) >= 0 ){
                if(m_board->getColor(i, j))
                    painter->setBrush(Qt::darkGray);
                else
                    painter->setBrush(Qt::white);
            }
            if(m_board->getColor(i, j) == -1)
              painter->setBrush(QColor(242, 142, 174));


            if(showProb && !m_board->isFixed(i, j)){
                QColor col;
                col.setHsl(240*(mx-m_board->getProb(i,j))/mx, 170, 150);
                painter->setBrush(col);
            }

            if(m_board->getColor(i, j) != -2)
              painter->drawConvexPolygon(hex);



            if(showPivots){
                if(m_board->isBridge(i, j)){
                    painter->setBrush(Qt::yellow);
                    painter->drawEllipse(QPointF(xc, yc)*m_scale, 0.5*m_scale, 0.5*m_scale);
                }
            }

            if(showMaxProb){
              if(std::make_pair(i,j) == maxProb){
                    painter->setBrush(Qt::magenta);
                    painter->drawEllipse(QPointF(xc, yc)*m_scale, 0.5*m_scale, 0.5*m_scale);
              }
            }

            xc += sq3;
        }
        yc = yc + 1.5;
        xs += sq3/2;
        xc = xs;
    }
}

void BoardItem::updateScale(double newScale)
{
    m_scale = newScale;

    // Recompute our bounding box
    prepareGeometryChange();
}
