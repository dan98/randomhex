#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include "boarditem.h"

#include <QGraphicsView>

class BoardWidget : public QGraphicsView
{
    Q_OBJECT

public:
    BoardWidget(QWidget *parent);
    ~BoardWidget();

    Board* getBoard();
    void setBoard(Board *board);

    BoardItem* getItem();

    double boardScaleFactor();
    double scaleFactor();
    void setScaleFactor(double sf);

protected slots:
    void resizeEvent(QResizeEvent *event);

private:
    double m_bScaleFactor;
    double m_scale;

    BoardItem *m_bitem;
};

#endif
