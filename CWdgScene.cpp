#include <QHBoxLayout>
#include <CGraphicsItem.h>
#include <QGraphicsView>
#include <QGraphicsScene>
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
	addGridToScene();
	fillMatrixItemPos();

}

void CWdgScene::addGridToScene()
{
	// Add the vertical lines
	const auto viewWidth = m_view->sceneRect().width();
	for (int posXLine = 0; posXLine <= viewWidth; posXLine += GlobalSettings::itemStep())
	{
		m_scene->addLine(posXLine, 0, posXLine, viewWidth, QPen(Qt::black));
	}
	// Add the horizontal lines
	const auto viewHeight = m_view->sceneRect().height();
	for (int posYLine = 0; posYLine <= viewHeight; posYLine += GlobalSettings::itemStep())
	{
		m_scene->addLine(0, posYLine, viewHeight, posYLine, QPen(Qt::black));
	}

}

void CWdgScene::fillMatrixItemPos()
{
	m_matrixPosOfItem.reserve(maxItemCount);
	auto posYOfItem = 0;
	auto rowIndex = 0;
	while(posYOfItem < m_view->sceneRect().width())
	{
		auto posXOfItem = 0;
		std::vector<QPoint> columns;
		columns.reserve(maxItemCount);
		m_matrixPosOfItem.push_back(std::move(columns));
		while(posXOfItem < m_view->sceneRect().width())
		{
			m_matrixPosOfItem[rowIndex].push_back(QPoint(posXOfItem, posYOfItem));
			posXOfItem += GlobalSettings::itemStep();
		}
		posYOfItem += GlobalSettings::itemStep();
		rowIndex ++;
	}
}

void CWdgScene::addElementToScene()
{
	const auto centerPoint = getCenterPoint();
	m_scene->addItem(new CGraphicsItem(QRect(centerPoint.x(), centerPoint.y(),
											 GlobalSettings::itemStep(), GlobalSettings::itemStep()), Qt::red));
}

QPoint CWdgScene::getCenterPoint()
{
	const auto& centerRow = m_matrixPosOfItem[m_matrixPosOfItem.size()/2];
	return centerRow[centerRow.size()/2];
}
