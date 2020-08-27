#include <QHBoxLayout>
#include <CGraphicsItem.h>
#include <CStripItemConfig.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "GlobalSettings.h"
#include "CWdgScene.h"

CWdgScene::CWdgScene(QWidget* parent)
	: QWidget(parent)
{
	QHBoxLayout* hBoxLayout = new QHBoxLayout;
	m_view = new QGraphicsView();
	hBoxLayout->addWidget(m_view);
	m_scene = new CGraphicsScene(this);
	connect(m_scene, &CGraphicsScene::itemMouseReleased, this, &CWdgScene::itemMouseReleased);
	m_scene->setBackgroundBrush(QBrush(Qt::gray));
	m_view->setScene(m_scene);
	m_view->setContentsMargins(0, 0, 0, 0);
	m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	hBoxLayout->setContentsMargins(0, 0, 0, 0);
	setContentsMargins(0, 0, 0, 0);
	setLayout(hBoxLayout);
	addGridToScene();
	fillMatrixItemPos();

}

void CWdgScene::addGridToScene()
{
	auto& globalSettings = GlobalSettings::get();
	// Add the vertical lines
	const auto viewSize = globalSettings.maxItemsSize() * globalSettings.itemStep();
	for (size_t posXLine = 0; posXLine <= viewSize; posXLine += globalSettings.itemStep())
	{
		m_scene->addLine(posXLine, 0, posXLine, viewSize, QPen(Qt::black));
	}
	// Add the horizontal lines
	for (size_t posYLine = 0; posYLine <= viewSize; posYLine += globalSettings.itemStep())
	{
		m_scene->addLine(0, posYLine, viewSize, posYLine, QPen(Qt::black));
	}

}

void CWdgScene::fillMatrixItemPos()
{
	auto& globalSettings = GlobalSettings::get();
	m_matrixPosOfItem.reserve(globalSettings.maxItemsSize());
	auto posYOfItem = 0;
	auto rowIndex = 0;
	while(posYOfItem < m_view->sceneRect().width())
	{
		auto posXOfItem = 0;
		std::vector<QPoint> columns;
		columns.reserve(globalSettings.maxItemsSize());
		m_matrixPosOfItem.push_back(std::move(columns));
		while(posXOfItem < m_view->sceneRect().width())
		{
			m_matrixPosOfItem[rowIndex].push_back(QPoint(posXOfItem, posYOfItem));
			posXOfItem += globalSettings.itemStep();
		}
		posYOfItem += globalSettings.itemStep();
		rowIndex++;
	}
}

void CWdgScene::addItemToScene(const CStripItemConfig& stripItem)
{
	const auto centerPoint = getCenterPoint();
	auto graphicsItem = new CGraphicsItem(QRect(centerPoint.x(), centerPoint.y(),
												GlobalSettings::get().itemStep(), GlobalSettings::get().itemStep()), GlobalSettings::get().itemColor());
	graphicsItem->setText(QString::fromStdString(stripItem.Item().GetData()));
	m_stripItems[graphicsItem] = std::move(stripItem);
	m_scene->addItem(graphicsItem);
}

void CWdgScene::overwriteItemFromScene(const CStripItemConfig& stripItem)
{
	for(auto& mapStripItem : m_stripItems)
	{
		auto& mapStripItemconfig = mapStripItem.second;
		if(mapStripItemconfig.Item().Id() == stripItem.Item().Id())
		{
			mapStripItemconfig = stripItem;
		}
	}
}

void CWdgScene::deleteItemFromScene(const CStripItemConfig& stripItem)
{
	for (auto itStripItem = m_stripItems.begin(); itStripItem != m_stripItems.end(); ++itStripItem)
	{
		auto& mapStripItemconfig = itStripItem->second;
		if(mapStripItemconfig.Item().Id() == stripItem.Item().Id())
		{
			m_scene->removeItem(itStripItem->first);
			m_stripItems.erase(itStripItem);
		}
	}
}

void CWdgScene::itemMouseReleased(CGraphicsItem* graphicsItem)
{
	if(graphicsItem)
	{
		auto itemConfig = *m_stripItems.find(graphicsItem);
		selectedItemConfig(itemConfig.second);
	}
	else
	{
		selectedItemConfig(CStripItemConfig());
	}

}

QPoint CWdgScene::getCenterPoint()
{
	const auto centerRowIndex = this->width() / GlobalSettings::get().itemStep();
	const auto centerColumnIndex = this->height() / GlobalSettings::get().itemStep();
	try
	{
		const auto& centerRow = m_matrixPosOfItem[centerColumnIndex/2];
		return centerRow[centerRowIndex/2];
	}
	catch(const std::out_of_range& oor)
	{
		return m_matrixPosOfItem[0][0];
	}
}

std::list<CStripItemConfig> CWdgScene::GetStripItemsParams()
{
	std::list<CStripItemConfig> stripItemsList;
	const auto itemStep = GlobalSettings::get().itemStep();
	for (auto& relatedItem : m_stripItems)
	{
		auto& itemConfig = relatedItem.second;
		itemConfig.SetX(relatedItem.first->getRect().x() / itemStep);
		itemConfig.SetY(relatedItem.first->getRect().y() / itemStep);
		itemConfig.SetCustomWidth(relatedItem.first->getRect().width() / itemStep);
		itemConfig.SetCustomHeight(relatedItem.first->getRect().height() / itemStep);
		stripItemsList.push_back(itemConfig);
	}
	stripItemsList.sort();
	return stripItemsList;
}

void CWdgScene::setElementsToScene(std::list<UUserPolicies::CStripItemConfig>& stripItemsConfigs)
{
	clearScene();
	const auto itemStep = GlobalSettings::get().itemStep();
	for(auto& stripItemConfig : stripItemsConfigs)
	{
		auto itemRect = QRect(
					stripItemConfig.X() * itemStep,
					stripItemConfig.Y() * itemStep,
					stripItemConfig.CustomWidth() * itemStep,
					stripItemConfig.CustomHeight() * itemStep);
		auto graphicsItem = new CGraphicsItem(itemRect, GlobalSettings::get().itemColor());
		graphicsItem->setText(QString::fromStdString(stripItemConfig.Item().GetData()));
		m_stripItems[graphicsItem] = std::move(stripItemConfig);
		m_scene->addItem(graphicsItem);
	}

}

void CWdgScene::clearScene()
{
	m_scene->clear();
	addGridToScene();
}
