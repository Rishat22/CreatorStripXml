#include <QHBoxLayout>
#include <CGraphicsItem.h>
#include <QEvent>
#include <QDebug>
#include "GlobalSettings.h"
#include "CWdgScene.h"

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
	m_scene->addItem(new CGraphicsItem(QRect(0, 0, GlobalSettings::itemStep(), GlobalSettings::itemStep()), Qt::red));
}

void CWdgScene::AddGridToScene()
{
	const auto viewWidth = m_view->sceneRect().width();
	// Add the vertical lines first, paint them red
	for (int posXLine = 0; posXLine <= viewWidth; posXLine += GlobalSettings::itemStep())
		m_scene->addLine(posXLine, 0, posXLine, viewWidth, QPen(Qt::black));

	const auto viewHeight = m_view->sceneRect().width();
	// Now add the horizontal lines, paint them green
	for (int posYLine = 0; posYLine <= viewHeight; posYLine += GlobalSettings::itemStep())
		m_scene->addLine(0, posYLine, viewHeight, posYLine, QPen(Qt::black));

}

