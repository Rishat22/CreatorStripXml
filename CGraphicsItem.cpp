#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QDebug>
#include "GlobalSettings.h"
#include "CGraphicsItem.h"

CGraphicsItem::CGraphicsItem(const QRect& size, const QColor color)
    : m_itemRect(size),
      m_itemBrush(color)
{
    setFlag(QGraphicsItem::ItemIsMovable);
}

QRectF CGraphicsItem::boundingRect() const
{
    return m_itemRect;
}

void CGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->fillRect(m_itemRect, m_itemBrush);
    painter->drawRect(m_itemRect);
}

void CGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(isPosAtBottomSide(event->pos()))
    {
        m_isMoveMode = false;
        m_resizeMode = ResizeMode::bottom;
        setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if(isPosAtRightSide(event->pos()))
    {
        m_isMoveMode = false;
        m_resizeMode = ResizeMode::right;
        setCursor(QCursor(Qt::SizeHorCursor));

    }
    else
    {
        m_isMoveMode = true;
    }
    m_initPos = event->scenePos();
    update();
    QGraphicsItem::mousePressEvent(event);
}

bool CGraphicsItem::isPosAtBottomSide(const QPointF& posToCheck)
{
    if((posToCheck.x() > boundingRect().left() + adjustMouseResize)
            && (posToCheck.x() < boundingRect().right() - adjustMouseResize)
            && (posToCheck.y() < boundingRect().bottom() + adjustMouseResize)
            && (posToCheck.y() > boundingRect().bottom() - adjustMouseResize) )
    {
        return true;
    }
    return false;
}

bool CGraphicsItem::isPosAtRightSide(const QPointF& posToCheck)
{
    if((posToCheck.x() > boundingRect().right() - adjustMouseResize)
            && (posToCheck.x() < boundingRect().right() + adjustMouseResize)
            && (posToCheck.y() < boundingRect().bottom() - adjustMouseResize)
            && (posToCheck.y() > boundingRect().top() + adjustMouseResize))
    {
        return true;
    }
    return false;
}


void CGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_isMoveMode)
    {
        moveItem(event);
    }
    else
    {
        resizeItem(event);
    }
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void CGraphicsItem::resizeItem(QGraphicsSceneMouseEvent* event)
{
    if(m_resizeMode == ResizeMode::bottom)
    {
        prepareGeometryChange();
        const auto newHeight = boundingRect().height() + event->scenePos().y() - m_initPos.y();
        m_itemRect.setHeight(GlobalSettings::modulusOfStep(newHeight));
    }
    else if(m_resizeMode == ResizeMode::right)
    {
        prepareGeometryChange();
        const auto newWidth = boundingRect().width() + event->scenePos().x() - m_initPos.x();
        m_itemRect.setWidth(GlobalSettings::modulusOfStep(newWidth));
    }
    setCursor(QCursor(Qt::ArrowCursor));
}

void CGraphicsItem::moveItem(QGraphicsSceneMouseEvent* event)
{
    setPos(GlobalSettings::modulusOfStep(event->scenePos().x()) - GlobalSettings::modulusOfStep(event->pos().x()),
           GlobalSettings::modulusOfStep(event->scenePos().y()) - GlobalSettings::modulusOfStep(event->pos().y()));
}

void CGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_isMoveMode)
    {
        update();
        QGraphicsItem::mouseMoveEvent(event);
    }

}

