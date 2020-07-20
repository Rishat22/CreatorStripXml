#include "CWdgScene.h"
#include <QHBoxLayout>
#include <CGraphicsItem.h>
#include <QEvent>
#include <QDebug>

CWdgScene::CWdgScene(QWidget* parent)
	: QWidget(parent)
{
	QHBoxLayout* hBoxLayout = new QHBoxLayout;
	m_view = new QGraphicsView();
	hBoxLayout->addWidget(m_view);
	m_scene = new QGraphicsScene(this);
	m_scene->setBackgroundBrush(QBrush(Qt::gray));
	m_view->setScene(m_scene);
	m_view->setSceneRect(0, 0, 650, 650);
	m_view->setContentsMargins(0, 0, 0, 0);
	hBoxLayout->setContentsMargins(0, 0, 0, 0);
	setContentsMargins(0, 0, 0, 0);
	setFixedSize(660, 660);
	setLayout(hBoxLayout);
	AddGridToScene();
}

void CWdgScene::AddElementToScene()
{
	auto recIntem = m_scene->addRect(0, 0, gridStep, gridStep,QPen(Qt::black), QBrush(Qt::red));
	recIntem->setFlag(QGraphicsItem::ItemIsMovable);
}

bool CWdgScene::eventFilter(QObject *watched, QEvent *event)
{
	if ((watched == m_view) && (event->type() == QEvent::Resize))
		m_item->setRect(m_view->viewport()->rect().adjusted(5, 5, -5, -5));

	return QWidget::eventFilter(watched, event);
}

void CWdgScene::AddGridToScene()
{
	const auto viewWidth = m_view->sceneRect().width();
	// Add the vertical lines first, paint them red
	for (int posXLine = 0; posXLine <= viewWidth; posXLine += gridStep)
		m_scene->addLine(posXLine, 0, posXLine, viewWidth, QPen(Qt::black));

	const auto viewHeight = m_view->sceneRect().width();
	// Now add the horizontal lines, paint them green
	for (int posYLine = 0; posYLine <= viewHeight; posYLine += gridStep)
		m_scene->addLine(0, posYLine, viewHeight, posYLine, QPen(Qt::black));

}

