#include "CGraphicsItem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QDebug>

CGraphicsItem::CGraphicsItem(const QRect& size, const QColor color)
	: m_itemRect(size),
	  m_itemBrush(color)
{
	itemStep = size.width();
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
	if((event->pos().x() > boundingRect().left() + adjustMouseResize)
			&& (event->pos().x() < boundingRect().right() - adjustMouseResize)
			&& (event->pos().y() < boundingRect().bottom() + adjustMouseResize)
			&& (event->pos().y() > boundingRect().bottom() - adjustMouseResize) )
	{
		m_initPos = event->scenePos().y();
		m_resizeMode = ResizeMode::bottom;
		m_isMoveMode = false;
		setCursor(QCursor(Qt::SizeVerCursor));
	}
	else
	{
		m_isMoveMode = true;
	}
	update();
	QGraphicsItem::mousePressEvent(event);
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
		const auto newHeight = boundingRect().height() + event->scenePos().y() - m_initPos;
		m_itemRect.setHeight(modulusOfStep(newHeight));
		setCursor(QCursor(Qt::ArrowCursor));
	}
}

void CGraphicsItem::moveItem(QGraphicsSceneMouseEvent* event)
{
	setPos(modulusOfStep(event->scenePos().x()),
		   modulusOfStep(event->scenePos().y()));
}

size_t CGraphicsItem::modulusOfStep(const size_t value)
{
	return static_cast<size_t>(value / itemStep) * itemStep;
}

void CGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if(m_isMoveMode)
	{
		update();
		QGraphicsItem::mouseMoveEvent(event);
	}

}

