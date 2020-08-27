#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
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
	const auto adjustItemRect =	QRectF(m_itemRect.x() + adjustMouseResize/4,
									   m_itemRect.y() + adjustMouseResize/4,
									   m_itemRect.width() - adjustMouseResize/2,
									   m_itemRect.height() - adjustMouseResize/2);
	painter->fillRect(adjustItemRect, m_itemBrush);
	painter->drawText(adjustItemRect, Qt::AlignVCenter, m_itemText);
	painter->drawRect(adjustItemRect);
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
	else if(isPosAtTopSide(event->pos()))
	{
		m_isMoveMode = false;
		m_resizeMode = ResizeMode::top;
		setCursor(QCursor(Qt::SizeVerCursor));

	}
	else if(isPosAtLeftSide(event->pos()))
	{
		m_isMoveMode = false;
		m_resizeMode = ResizeMode::left;
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

bool CGraphicsItem::isPosAtTopSide(const QPointF& posToCheck)
{
	if((posToCheck.x() > boundingRect().left() + adjustMouseResize)
			&& (posToCheck.x() < boundingRect().right() - adjustMouseResize)
			&& (posToCheck.y() < boundingRect().top() + adjustMouseResize)
			&& (posToCheck.y() > boundingRect().top() - adjustMouseResize))
	{
		return true;
	}
	return false;
}

bool CGraphicsItem::isPosAtLeftSide(const QPointF& posToCheck)
{
	if((posToCheck.x() > boundingRect().left() - adjustMouseResize)
			&& (posToCheck.x() < boundingRect().left() + adjustMouseResize)
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
	auto& globalSettings = GlobalSettings::get();
	if(m_resizeMode == ResizeMode::bottom)
	{
		prepareGeometryChange();
		const auto newHeight = boundingRect().height() + event->scenePos().y() - m_initPos.y();
		m_itemRect.setHeight(globalSettings.modulusOfStep(newHeight));
	}
	else if(m_resizeMode == ResizeMode::right)
	{
		prepareGeometryChange();
		const auto newWidth = boundingRect().width() + event->scenePos().x() - m_initPos.x();
		m_itemRect.setWidth(globalSettings.modulusOfStep(newWidth));
	}
	else if(m_resizeMode == ResizeMode::top)
	{
		prepareGeometryChange();
		const auto newYPos = m_initPos.y() - event->scenePos().y();
		m_itemRect.setY(m_itemRect.y() - globalSettings.modulusOfStep(newYPos));
	}
	else if(m_resizeMode == ResizeMode::left)
	{
		prepareGeometryChange();
		const auto newXPos =  m_initPos.x() - event->scenePos().x();
		m_itemRect.setX(m_itemRect.x() - globalSettings.modulusOfStep(newXPos));
	}
	setCursor(QCursor(Qt::ArrowCursor));
}

void CGraphicsItem::moveItem(QGraphicsSceneMouseEvent* event)
{
	auto& globalSettings = GlobalSettings::get();
	setPos(globalSettings.modulusOfStep(event->scenePos().x()) - globalSettings.modulusOfStep(event->pos().x()),
		   globalSettings.modulusOfStep(event->scenePos().y()) - globalSettings.modulusOfStep(event->pos().y()));
}

void CGraphicsItem::setText(const QString& itemText)
{
	m_itemText = itemText;
}

QRect CGraphicsItem::getRect() const
{
	return mapRectToScene(boundingRect()).toRect();
}

void CGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if(m_isMoveMode)
	{
		update();
		QGraphicsItem::mouseMoveEvent(event);
	}

}

