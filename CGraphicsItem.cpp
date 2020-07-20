#include "CGraphicsItem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

CGraphicsItem::CGraphicsItem(const QRect& size, const QColor color)
	: m_itemRect(size),
	  m_itemBrush(color)
{
	itemStep = size.width();
	m_mousePressed = false;
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
	m_mousePressed = true;
	update();
	QGraphicsItem::mousePressEvent(event);
}

void CGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	m_mousePressed = false;
	update();
	QGraphicsItem::mouseReleaseEvent(event);
	size_t newX = (event->scenePos().x() / itemStep) ;
	size_t newY = (event->scenePos().y() / itemStep);
	setPos(newX * itemStep, newY * itemStep);
}
