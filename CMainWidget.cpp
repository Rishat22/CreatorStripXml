#include <QHBoxLayout>
#include <CWdgScene.h>
#include <CWdgSelectionMenu.h>
#include <CStripLoader.h>
#include "CMainWidget.h"

CMainWidget::CMainWidget(QWidget *parent)
	: QWidget(parent)
{
	auto mainLayout = new QHBoxLayout(this);

	m_wdgScene = new CWdgScene;
	mainLayout->addWidget(m_wdgScene);
	auto wdgSelectionMenu = new CWdgSelectionMenu;
	mainLayout->addWidget(wdgSelectionMenu);

	connect(wdgSelectionMenu, &CWdgSelectionMenu::addElementToScene, m_wdgScene, &CWdgScene::addElementToScene);
	connect(wdgSelectionMenu, &CWdgSelectionMenu::saveData, this, &CMainWidget::saveData);
	setLayout(mainLayout);
}

CMainWidget::~CMainWidget()
{
}

void CMainWidget::saveData(const std::string& strFileName)
{
	CStripLoader stripLoader;
//	stripLoader.save(strFileName);
	auto stripItemsList = std::move(m_wdgScene->GetStripItemsList());
	for(StripItem& stripItem : stripItemsList)
	{
		qDebug() << QString::fromStdString(stripItem.name) << stripItem.rect << QString::fromStdString(stripItem.interaction.action);
	}
}


