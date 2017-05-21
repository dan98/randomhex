#include "boardwidget.h"
#include "boarditem.h"

#include <QGraphicsScene>

BoardWidget::BoardWidget(QWidget *parent)
    : QGraphicsView(parent)
{

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(scene);
    setBackgroundBrush(QBrush(QColor(255, 235, 230)));
    m_bitem = new BoardItem();
    scene->addItem(m_bitem);
}

BoardWidget::~BoardWidget()
{
  delete m_bitem;
}


BoardItem* BoardWidget::getItem(){
  return m_bitem;
}

void BoardWidget::setBoard(Board* board)
{
    m_bitem->m_board = board;
    m_bitem->setPos(0.0, 0.0);
    m_bitem->updateScale(m_bScaleFactor);
    setScaleFactor(board->boardSize()*3);
    scene()->update();
}

Board* BoardWidget::getBoard()
{
    return m_bitem->m_board;
}

double BoardWidget::boardScaleFactor()
{
    return m_bScaleFactor;
}

double BoardWidget::scaleFactor()
{
    return m_scale;
}

void BoardWidget::setScaleFactor(double sf)
{
    m_scale = sf;

    m_bScaleFactor = qMin(sceneRect().width(), sceneRect().height()) / m_scale;

    m_bitem->updateScale(m_bScaleFactor);

    update();
}

void BoardWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    QRectF newSceneRect(-width() / 2.0, -height() / 2.0, width(), height());
    newSceneRect.adjust(0.0, 0.0, 0.0, 0.0);

    m_bScaleFactor = qMin(newSceneRect.width(), newSceneRect.height()) / m_scale;

    m_bitem->updateScale(m_bScaleFactor);

    setSceneRect(newSceneRect);
}
